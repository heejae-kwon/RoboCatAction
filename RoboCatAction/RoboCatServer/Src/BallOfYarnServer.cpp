#include <RoboCatServerPCH.h>
BallOfYarnServer::BallOfYarnServer() 
{
	//yarn lives a second...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 2.f;
}

void BallOfYarnServer::HandleDying()
{
  SetCollisionRadius(0);
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void BallOfYarnServer::Update()
{
    BallOfYarn::Update();
  if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
  {
    SetDoesWantToDie(true);
    SetCollisionRadius(1);
  }
  //NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EYRS_Pose);
  float radius = GetCollisionRadius();
  if (radius != 0) {
    auto& objects = World::sInstance->GetGameObjects();
    for (auto& goIt : objects)
    {
      GameObject* target = goIt.get();
      if (target->GetAsCat() != nullptr && !target->DoesWantToDie())
      {
        //you hit a cat, so look like you hit a cat
        auto& catLocation = target->GetLocation();
        float catRadius = target->GetCollisionRadius();
        auto& location = GetLocation();
        float distSq = (catLocation - location).LengthSq2D();

        if (distSq <= (catRadius + radius) * (catRadius + radius)) {
          static_cast<RoboCatServer*>(target)->TakeDamage(GetPlayerId());
        }
      }
    }
  }
}



bool BallOfYarnServer::HandleCollisionWithCat(RoboCat* inCat)
{
  //if (inCat->GetPlayerId() != GetPlayerId())
 /* {
    //kill yourself!
    if (BallOfYarn::HandleCollisionWithCat(inCat)) {
      //SetDoesWantToDie(true);

   }
    //NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EYRS_Color);
  }*/
  return false;
}


