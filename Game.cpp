#include "Game.h"
#include "Human.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"


Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false)
{
	borders = new SDL_Rect[580];
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize video: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Zombie Apocalypse Simulator V 0.1",
		100,
		100,
		1043,
		954,
		0);
	if (!mWindow)
	{
		SDL_Log("Failed to initialize window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to initialize renderer: %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ShutDown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0;
	if (deltaTime > 0.05)
	{
		deltaTime = 0.05;
	}
	mTicksCount = SDL_GetTicks();

	mUpdatingActors = true;

	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;

	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 1);
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	int Count = 0;

	SDL_Rect b1{
		220,
		0,
		300,
		10
	};
	borders[Count] = b1;
	Count++;
	b1.x = 520;
	b1.w = 10;
	b1.h = 310;

	borders[Count] = b1;
	Count++;
	b1.y = 300;
	b1.w = 5;
	b1.h = 5;
	borders[Count] = b1;
	Count++;
	for (int i = 0; i < 245; i++)
	{
		b1.x += 2.5;
		b1.y += 2.5;
		borders[Count] = b1;
		Count++;
	}
	b1.h = 120;
	borders[Count] = b1;
	Count++;
	b1.h = 2.5;
	b1.y += 115;
	for (int i = 0; i < 9; i++)
	{
		b1.x -= 5;
		b1.y += 2.5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 30; i++)
	{
		b1.x -= 2;
		borders[Count] = b1;
		Count++;
	}
	b1.w = 10;
	for (int i = 0; i < 9; i++)
	{
		b1.x -= 5;
		b1.y += 1;
		borders[Count] = b1;
		Count++;
	}
	b1.x -= 40;
	b1.w = 50;
	borders[Count] = b1;
	Count++;
	b1.x = 220;
	b1.y = 10;
	b1.w = 10;
	b1.h = 10;
	borders[Count] = b1;
	Count++;
	for (int i = 0; i < 8; i++)
	{
		b1.y += 10;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 33; i++)
	{
		b1.x -= 1;
		b1.y += 2.5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 17; i++)
	{
		b1.x += 2;
		b1.y += 2.5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 20; i++)
	{
		b1.y += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 25; i++)
	{
		b1.x += 2;
		b1.y += 3;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 5; i++)
	{
		b1.y += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 10; i++)
	{
		b1.x += 2;
		b1.y += 2;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 4; i++)
	{
		b1.x += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 11; i++)
	{
		b1.y += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 6; i++)
	{
		b1.x += 5;
		b1.y += 6;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 5; i++)
	{
		b1.x += 4;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 7; i++)
	{
		b1.y += 3;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 2; i++)
	{
		b1.x -= 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 9; i++)
	{
		b1.y += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 19; i++)
	{
		b1.x += 5;
		b1.y += 6;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 11; i++)
	{
		b1.y += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 4; i++)
	{
		b1.x += 5;
		b1.y += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 10; i++)
	{
		b1.x += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 5; i++)
	{
		b1.x += 5;
		b1.y += 1;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 3; i++)
	{
		b1.x += 5; 
		b1.y += 2;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 4; i++)
	{
		b1.x += 5;
		b1.y += 7;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 5; i++)
	{
		b1.x += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 4; i++)
	{
		b1.x += 3;
		b1.y += 1;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 3; i++)
	{
		b1.x += 5;
		b1.y += 1;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 4; i++)
	{
		b1.y += 7;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 5; i++)
	{
		b1.x += 5;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 12; i++)
	{
		b1.x += 5;
		b1.y += 4;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 20; i++)
	{
		b1.x += 1;
		b1.y += 3;
		borders[Count] = b1;
		Count++;
	}
	for (int i = 0; i < 10; i++)
	{
		b1.x += 10;
		b1.y -= 1;
		borders[Count] = b1;
		Count++;
	}

	for (auto person : mHumans)
	{
		person->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::AddActor(class Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(class Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture to file: %s", SDL_GetError());
			return nullptr;
		}
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture: %s", SDL_GetError());
			return nullptr;
		}
		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}

void Game::LoadData()
{
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(521.5, 477.0));
	SpriteComponent* bg = new SpriteComponent(temp);
	bg->SetTexture(GetTexture("Assets/cali.png"));

	for (int i = 0; i < 3000; i++)
		Human* patientZero = new Human(this);

}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Rect* Game::GetBorders()
{
	return borders;
}

void Game::AddHuman(class Human* human)
{
	mHumans.emplace_back(human);
}

void Game::RemoveHuman(class Human* human)
{
	auto iter = std::find(mHumans.begin(), mHumans.end(), human);
	if (iter != mHumans.end())
	{
		std::iter_swap(iter, mHumans.end() - 1);
		mHumans.pop_back();
	}
}
