class HyperYarnServer : public HyperYarn
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new HyperYarnServer() ); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;


	virtual void Update() override;

protected:
	HyperYarnServer();

private:

	float mTimeToDie;
  bool mDoesGiveDamage;
};
