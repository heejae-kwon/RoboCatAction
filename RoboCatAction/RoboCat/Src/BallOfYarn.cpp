
#include <RoboCatPCH.h>

BallOfYarn::BallOfYarn() : mYarnLocationOffset(-0.55f)
{
}



uint32_t BallOfYarn::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
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



bool BallOfYarn::HandleCollisionWithCat(RoboCat* inCat)
{
  (void)inCat;

  return false;
}

void BallOfYarn::Update()
{

  float deltaTime = Timing::sInstance.GetDeltaTime();

  //	SetLocation( GetLocation() + mVelocity * deltaTime );
    //we'll let the cats handle the collisions
}



void BallOfYarn::InitFromShooter( RoboCat* inShooter )
{
	SetColor( inShooter->GetColor() );
	SetPlayerId( inShooter->GetPlayerId() );

	Vector3 forward = inShooter->GetForwardVector();
	SetLocation( inShooter->GetLocation()  + forward * mYarnLocationOffset  );

  SetCollisionRadius(0);
}

