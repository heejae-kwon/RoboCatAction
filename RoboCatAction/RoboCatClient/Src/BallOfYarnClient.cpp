
#include <RoboCatClientPCH.h>


BallOfYarnClient::BallOfYarnClient()
{
  mSpriteComponent.reset(new SpriteComponent(this));
  mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("yarn"));
}

void BallOfYarnClient::Read(InputMemoryBitStream& inInputStream)
{
  bool stateBit;

  inInputStream.Read(stateBit);
  if (stateBit)
  {
    Vector3 location;
    inInputStream.Read(location.mX);
    inInputStream.Read(location.mY);


    Vector3 velocity;
    inInputStream.Read(velocity.mX);
    inInputStream.Read(velocity.mY);
    SetVelocity(velocity);

    //dead reckon ahead by rtt, since this was spawned a while ago!
    SetLocation(location + velocity * NetworkManagerClient::sInstance->GetRoundTripTime());


    float rotation;
    inInputStream.Read(rotation);
    SetRotation(rotation);
  }


  inInputStream.Read(stateBit);
  if (stateBit)
  {
    Vector3 color;
    inInputStream.Read(color);
    SetColor(color);
  }

  inInputStream.Read(stateBit);
  if (stateBit)
  {
    inInputStream.Read(mPlayerId, 8);
    //mInShooter = NetworkManagerClient::sInstance->GetRoboCatFromId(GetPlayerId());
  }
}

bool BallOfYarnClient::HandleCollisionWithCat(RoboCat* inCat)
{
 /* if (GetPlayerId() != inCat->GetPlayerId())
  {
    if (res) {
      Vector3 color;
      if (GetPlayerId() == NetworkManagerClient::sInstance->GetPlayerId()) {
        color = Vector3(1, 0, 0);
      }
      else {
        color = Vector3(1, 1, 1);
      }
      SetColor(color);
      mCollision = true;
    }
    return res;
  }
  return false;*/
    return false;
}

void BallOfYarnClient::Update()
{
  BallOfYarn::Update();

 /* Vector3 color;
  if (GetPlayerId() == NetworkManagerClient::sInstance->GetPlayerId()) {
    color = Vector3(0, 0, 1);
  }
  else {
    color = Vector3(0, 0, 0);
  }
  if (mCollision == false) {
    SetColor(color);
  }
  mCollision = false;*/
}
  