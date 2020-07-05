//I take care of rendering things!

class RenderManager
{
public:

	static void StaticInit();
	static std::unique_ptr< RenderManager >	sInstance;

	void Render();
	void RenderComponents();
  void RenderHyperYarns();

	//vert inefficient method of tracking scene graph...
	void AddComponent( SpriteComponent* inComponent );
	void RemoveComponent( SpriteComponent* inComponent );
	int	 GetComponentIndex( SpriteComponent* inComponent ) const;

  void AddHyperYarn(HyperYarn* hyarn);
	void RemoveHyperYarn( HyperYarn* inComponent );
	int	 GetHyperYarnIndex( HyperYarn* inComponent ) const;



private:

	RenderManager();

	//this can't be only place that holds on to component- it has to live inside a GameObject in the world
	vector< SpriteComponent* >		mComponents;
  std::vector<HyperYarn*> mHyperYarns;

	SDL_Rect						mViewTransform;


};

