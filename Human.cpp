#include "Human.h"
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Human::Human(class Game* game) : Actor(game)
{
	SetPosition(Vector2(521.5, 477.0));
	xVel = rand() % 200 - 100;
	yVel = rand() % 200 - 100;
	dot = new SDL_Rect;
	dot->w = 5;
	dot->h = 5;
	dot->x = GetPosition().x - 2.5;
	dot->y = GetPosition().y - 2.5;
	GetGame()->AddHuman(this);
}

void Human::UpdateActor(float deltaTime) 
{
	mprevPosition = Vector2(GetPosition().x, GetPosition().y);
	float xPos = GetPosition().x;
	float yPos = GetPosition().y;
	
		SetPosition(Vector2((xPos + xVel * deltaTime), (yPos + yVel * deltaTime)));
		dot->x = GetPosition().x - 2.5;
		dot->y = GetPosition().y - 2.5;
		for (int i = 0; i < 580; i++)
		{
			if ((SDL_HasIntersection(dot, &(GetGame()->GetBorders()[i]))))
			{
				int chance = rand() % 2 + 1;
				if (chance == 1)
					xVel = -xVel;
				else
					yVel = -yVel;
				SetPosition(mprevPosition);
				break;
			}
		}
	
}

void Human::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(renderer, dot);
}