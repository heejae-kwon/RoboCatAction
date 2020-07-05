#include <RoboCatClientPCH.h>

std::unique_ptr< RenderManager >	RenderManager::sInstance;

RenderManager::RenderManager()
{
	SDL_Rect viewport = GraphicsDriver::sInstance->GetLogicalViewport();

	// The view transform stores both the scale factor and offset for rendering textures
	mViewTransform.x = viewport.w / 2;
	mViewTransform.y = viewport.h / 2;
	mViewTransform.w = 100;
	mViewTransform.h = 100;
}


void RenderManager::StaticInit()
{
	sInstance.reset( new RenderManager() );
}


void RenderManager::AddComponent( SpriteComponent* inComponent )
{
	mComponents.push_back( inComponent );
}

void RenderManager::RemoveComponent( SpriteComponent* inComponent )
{
	int index = GetComponentIndex( inComponent );

	if( index != -1 )
	{
		int lastIndex = mComponents.size() - 1;
		if( index != lastIndex )
		{
			mComponents[ index ] = mComponents[ lastIndex ];
		}
		mComponents.pop_back();
	}
}

int RenderManager::GetComponentIndex( SpriteComponent* inComponent ) const
{
	for( int i = 0, c = mComponents.size(); i < c; ++i )
	{
		if( mComponents[ i ] == inComponent )
		{
			return i;
		}
	}

	return -1;
}

void RenderManager::AddHyperYarn(HyperYarn* hyarn)
{
  mHyperYarns.push_back(hyarn);
}

void RenderManager::RemoveHyperYarn(HyperYarn* inComponent)
{
  int index = GetHyperYarnIndex(inComponent);

  if (index != -1)
  {
    int lastIndex = mHyperYarns.size() - 1;
    if (index != lastIndex)
    {
      mHyperYarns[index] = mHyperYarns[lastIndex];
    }
    mHyperYarns.pop_back();
  }
}



int RenderManager::GetHyperYarnIndex(HyperYarn* inComponent) const
{
  for (int i = 0, c = mHyperYarns.size(); i < c; ++i)
  {
    if (mHyperYarns[i] == inComponent)
    {
      return i;
    }
  }

  return -1;
}



//this part that renders the world is really a camera-
//in a more detailed engine, we'd have a list of cameras, and then render manager would
//render the cameras in order
void RenderManager::RenderComponents()
{
	//Get the logical viewport so we can pass this to the SpriteComponents when it's draw time
	SDL_Rect viewport = GraphicsDriver::sInstance->GetLogicalViewport();
	for( auto cIt = mComponents.begin(), end = mComponents.end(); cIt != end; ++cIt )
	{
		( *cIt )->Draw( mViewTransform );
	}
}

void RenderManager::RenderHyperYarns()
{

  auto renderer = GraphicsDriver::sInstance->GetRenderer();
  for (auto& hYarn : mHyperYarns) {
    auto& color = hYarn->GetColor();
    Uint8 r = static_cast<Uint8>(color.mX * 255);
    Uint8 g = static_cast<Uint8>(color.mY * 255);
    Uint8 b = static_cast<Uint8>(color.mZ * 255);
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    auto& start = hYarn->mStartPoint;
    auto& end = hYarn->mEndPoint;
    int startX = static_cast<int>(start.mX * mViewTransform.w + mViewTransform.x);
    int  startY = static_cast<int>(start.mY * mViewTransform.h + mViewTransform.y);
    int endX = static_cast<int>(end.mX * mViewTransform.w + mViewTransform.x);
    int endY = static_cast<int>(end.mY * mViewTransform.h + mViewTransform.y);


    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
  }
}

void RenderManager::Render()
{
	//
    // Clear the back buffer
    //
	SDL_SetRenderDrawColor( GraphicsDriver::sInstance->GetRenderer(), 100, 149, 237, SDL_ALPHA_OPAQUE );
	GraphicsDriver::sInstance->Clear();
	
	RenderManager::sInstance->RenderComponents();

	HUD::sInstance->Render();
  RenderHyperYarns();
	
	//
    // Present our back buffer to our front buffer
    //
	GraphicsDriver::sInstance->Present();

}