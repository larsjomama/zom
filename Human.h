#pragma once
#include "Actor.h"
#include "SDL/SDL.h"

class Human : public Actor
{
public:
	Human(class Game* game);
	void UpdateActor(float deltaTime) override;
	void Draw(SDL_Renderer* renderer);
private:
	float xVel;
	float yVel;
	SDL_Rect* dot;
	Vector2 mprevPosition;
};