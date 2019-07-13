#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddHuman(class Human* human);
	void RemoveHuman(class Human* human);

	SDL_Rect* GetBorders();
	SDL_Texture* GetTexture(const std::string& filename);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;

	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	std::vector<class Human*> mHumans;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	bool mUpdatingActors;
	Uint32 mTicksCount;
	SDL_Rect* borders;
};