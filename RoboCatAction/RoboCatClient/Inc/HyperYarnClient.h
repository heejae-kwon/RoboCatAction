class HyperYarnClient : public HyperYarn
{
public:
  	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new HyperYarnClient() ); }

	virtual void		Read( InputMemoryBitStream& inInputStream ) override;
	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;
  virtual void    Update();
  ~HyperYarnClient();


/*	HyperYarnClient(RoboCat* robo=nullptr );
//	virtual void		Read( InputMemoryBitStream& inInputStream ) override;
//	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;
  Vector3 mStartPoint;
  Vector3 mEndPoint;
  Vector3 mColor;
  bool mIsActive;
  float mLifeTime;*/
  bool mCollision;

protected:
  HyperYarnClient();

private:
};

