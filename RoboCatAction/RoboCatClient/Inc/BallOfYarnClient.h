
#pragma once

class BallOfYarnClient : public BallOfYarn
{
public:
  	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new BallOfYarnClient() ); }

	virtual void		Read( InputMemoryBitStream& inInputStream ) override;
	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;
  virtual void    Update();


/*	BallOfYarnClient(RoboCat* robo=nullptr );
//	virtual void		Read( InputMemoryBitStream& inInputStream ) override;
//	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;
  Vector3 mStartPoint;
  Vector3 mEndPoint;
  Vector3 mColor;
  bool mIsActive;
  float mLifeTime;*/

protected:
  BallOfYarnClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
