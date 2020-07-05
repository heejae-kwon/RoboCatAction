
class BallOfYarnServer : public BallOfYarn
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new BallOfYarnServer() ); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;


	virtual void Update() override;

protected:
	BallOfYarnServer();

private:

	float mTimeToDie;
};