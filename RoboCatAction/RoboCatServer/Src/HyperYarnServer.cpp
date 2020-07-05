
#include <RoboCatServerPCH.h>
HyperYarnServer::HyperYarnServer():mDoesGiveDamage(false)
{
	//yarn lives a second...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 2.f;
}

void HyperYarnServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
  mDoesGiveDamage = false;
}


void HyperYarnServer::Update()
{
  HyperYarn::Update();

  if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
  {
    SetDoesWantToDie(true);
  }
  NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EYRS_Pose);
}

bool HyperYarnServer::HandleCollisionWithCat(RoboCat* inCat)
{
  if (inCat->GetPlayerId() != GetPlayerId())
  {
    //kill yourself!
    if (HyperYarn::HandleCollisionWithCat(inCat)) {
      //SetDoesWantToDie(true);

      SetColor(Vector3(1, 1, 1));
      if (mDoesGiveDamage == false) {
        static_cast<RoboCatServer*>(inCat)->TakeDamage(GetPlayerId());
        mDoesGiveDamage = true;
      }
    }
    else {
      SetColor(Vector3(0, 0, 0));
    }
    NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EYRS_Color);
  }
  return false;
}

