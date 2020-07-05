#ifdef _WIN32
	#include <SDL_events.h>
#endif


class Engine
{
public:

	virtual ~Engine();
	static std::unique_ptr< Engine >	sInstance;

	void			SetShouldKeepRunning( bool inShouldKeepRunning ) { mShouldKeepRunning = inShouldKeepRunning; }
#ifdef _WIN32
	virtual void	HandleEvent( SDL_Event* inEvent );
#endif
	virtual int		Run();

protected:

	Engine();

	virtual void	DoFrame();

private:


			
			int		DoRunLoop();

			bool	mShouldKeepRunning;



};