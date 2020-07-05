#pragma once
class HyperYarn : public Yarn
{
public:
  CLASS_IDENTIFICATION('HYPY', GameObject)

    static	GameObject* StaticCreate() { return new HyperYarn(); }

  virtual uint32_t	GetAllStateMask()	const override { return EYRS_AllState; }

  virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

  virtual void Update() override;

  virtual void InitFromShooter(RoboCat* inShooter) override;

  virtual bool HandleCollisionWithCat(RoboCat* inCat) override;
  
  virtual void UpdateFromShooter();
  RoboCat* mInShooter;
  float mYarnLocationOffset;
  float mYarnLength;
  Vector3 mStartPoint;
  Vector3 mEndPoint;

protected:
  HyperYarn();
private:

};

using HyperYarnPtr = shared_ptr<HyperYarn>;

