
#include <RoboCatClientPCH.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>                       // JSON library
bool Client::StaticInit( )
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();

	if( WindowManager::StaticInit() == false )
	{
		return false;
	}
	
	if( GraphicsDriver::StaticInit( WindowManager::sInstance->GetMainWindow() ) == false )
	{
		return false;
	}

	TextureManager::StaticInit();
	RenderManager::StaticInit();
	InputManager::StaticInit();

	HUD::StaticInit();

	sInstance.reset( client );

	return true;
}

Client::Client()
{
  using namespace web::http;
  using namespace web;

  GameObjectRegistry::sInstance->RegisterCreationFunction('RCAT', RoboCatClient::StaticCreate);
  GameObjectRegistry::sInstance->RegisterCreationFunction('MOUS', MouseClient::StaticCreate);
  GameObjectRegistry::sInstance->RegisterCreationFunction('YARN', YarnClient::StaticCreate);
  GameObjectRegistry::sInstance->RegisterCreationFunction('HYPY', HyperYarnClient::StaticCreate);
  GameObjectRegistry::sInstance->RegisterCreationFunction('BOYN', BallOfYarnClient::StaticCreate);

  // My Code Start
  string loginServerAddress = StringUtils::GetCommandLineArg(1);
  string username = StringUtils::GetCommandLineArg(2);
  string password = StringUtils::GetCommandLineArg(3);

  client::http_client client(U("http://127.0.0.1:3100"));
  // Construct login request body
  json::value loginReqBody = json::value::parse(U("{}"));
  loginReqBody[U("username")] = json::value(utility::string_t(username.begin(), username.end()));
  loginReqBody[U("password")] = json::value(utility::string_t(password.begin(), password.end()));
  // Login
  auto req = client.request(methods::POST, U("/api/v1/login"), loginReqBody).then([&](http_response loginRes) {
    auto& connectReqBody = loginRes.extract_json().get();
    // Connect
    return client.request(methods::POST, U("/api/v1/connect"), connectReqBody);
    }).then([=](http_response connectRes) {
      auto& connectResObj = connectRes.extract_json().get();
      auto& server_wstring = connectResObj[U("server")].as_string();
      auto& username_wstring = connectResObj[U("username")].as_string();
      std::string server(server_wstring.begin(), server_wstring.end());
      std::string usr(username_wstring.begin(), username_wstring.end());

      SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString(server);
      NetworkManagerClient::StaticInit(*serverAddress, usr);
      });

    try
    {
      req.wait();
    }
    catch (const std::exception & e)
    {
      printf("Error exception:%s\n", e.what());
    }
    //My Code End


    //NetworkManagerClient::sInstance->SetDropPacketChance( 0.6f );
    //NetworkManagerClient::sInstance->SetSimulatedLatency( 0.25f );
    //NetworkManagerClient::sInstance->SetSimulatedLatency( 0.5f );
    //NetworkManagerClient::sInstance->SetSimulatedLatency( 0.1f );
}



void Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	RenderManager::sInstance->Render();

	NetworkManagerClient::sInstance->SendOutgoingPackets();
}

void Client::HandleEvent( SDL_Event* inEvent )
{
	switch( inEvent->type )
	{
	case SDL_KEYDOWN:
		InputManager::sInstance->HandleInput( EIA_Pressed, inEvent->key.keysym.sym );
		break;
	case SDL_KEYUP:
		InputManager::sInstance->HandleInput( EIA_Released, inEvent->key.keysym.sym );
		break;
	default:
		break;
	}
}

