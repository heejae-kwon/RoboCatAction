#pragma once
class BallOfYarn : public Yarn
{
public:
  CLASS_IDENTIFICATION('BOYN', GameObject)

    static	GameObject* StaticCreate() { return new BallOfYarn(); }

  virtual uint32_t	GetAllStateMask()	const override { return EYRS_AllState; }

  virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

  virtual void Update() override;

  virtual void InitFromShooter(RoboCat* inShooter) override;

  virtual bool HandleCollisionWithCat(RoboCat* inCat) override;
  
  float mYarnLocationOffset;

protected:
  BallOfYarn();
private:

};

using BallOfYarnPtr = shared_ptr<BallOfYarn>;


