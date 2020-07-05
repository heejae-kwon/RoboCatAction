
#include <RoboCatPCH.h>

HyperYarn::HyperYarn() : mYarnLocationOffset(0.55f),
mYarnLength(5.f)
{
}



uint32_t HyperYarn::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
{
	uint32_t writtenState = 0;

	if( inDirtyState & EYRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		Vector3 velocity = GetVelocity();
		inOutputStream.Write( velocity.mX );
		inOutputStream.Write( velocity.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= EYRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EYRS_Color )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( GetColor() );

		writtenState |= EYRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EYRS_PlayerId )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( mPlayerId, 8 );

		writtenState |= EYRS_PlayerId;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}




	return writtenState;
}



bool HyperYarn::HandleCollisionWithCat(RoboCat* inCat)
{
  (void)inCat;

  //you hit a cat, so look like you hit a cat
  auto& catLocation = inCat->GetLocation();
  auto catRadius = inCat->GetCollisionRadius();
  auto& forwardVector = GetVelocity();
  auto startToCat = catLocation - mStartPoint;
  auto dotAngle = Dot2D(forwardVector, startToCat);
  Vector3 nearestPoint;
  if (dotAngle > 0) {
    //projection startToCat onto ray
    auto ray = mEndPoint - mStartPoint;
    auto projection = (Dot2D(ray, startToCat) / ray.LengthSq2D()) * ray;
    nearestPoint = projection + mStartPoint;
  }
  else {
    nearestPoint = mStartPoint;
  }

  if ((catLocation - nearestPoint).LengthSq2D() <= catRadius*catRadius) {
    return true;
  }

  return false;
}

 void HyperYarn::UpdateFromShooter()
{
   if (mInShooter) {
     Vector3 forward = mInShooter->GetForwardVector();
     forward.Normalize();
     SetVelocity(forward);
     SetLocation(mInShooter->GetLocation() + forward * mYarnLocationOffset);
   }
}


 void HyperYarn::Update()
 {

   float deltaTime = Timing::sInstance.GetDeltaTime();

   UpdateFromShooter();
   mStartPoint = GetLocation();
   mEndPoint = GetLocation() + GetVelocity() * mYarnLength;

   //	SetLocation( GetLocation() + mVelocity * deltaTime );


     //we'll let the cats handle the collisions
 }



void HyperYarn::InitFromShooter( RoboCat* inShooter )
{
  mInShooter = inShooter;
	SetPlayerId( inShooter->GetPlayerId() );
}

