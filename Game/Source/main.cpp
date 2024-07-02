#include "renderer.h"
#include "vector2.h"
#include "input.h"
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

// Logical design is data types, inheritance hierarchies, classes etc...
// Physical design is how all the logical components arranged ...

// References: Show what something is dependent on (in this case, game depends on engine)

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize;

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;
	for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{rand() % 800, rand() % 600});
	}

	// Main loop
	bool quit = false;
	while (!quit)
	{
		// input
		// update
		// draw

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE
		Vector2 mousePos = input.GetMousePos();
		//std::cout << mousePos.x << " " << mousePos.y << std::endl;
		
		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
		{
			std::cout << "mouse down\n";
			points.push_back(mousePos);
		}
		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		{
			float distance = (points.back() - mousePos).Length();
			if (distance > 50)
			{
				points.push_back(mousePos);
			}
		}

		// [p, p, p, p,]
		Vector2 speed{ 0.1f, -0.1 };
		for (Vector2& point : points)
		{
			point = point + 0.002f; // Thru updating, this makes the object move to a new location
		}

		// DRAW
		//// clear screen
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		//SDL_RenderClear(renderer);
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		//// draw line
		renderer.SetColor(255, 255, 255, 0);
		

		for (int i = 0; i < points.size() - 1; i++)
		{
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		//// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//// SDL_RenderDrawLine(renderer, 0, 0, 800, 600);
		//// int value = rand() % range; // generate a number between 0-999

		///*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//SDL_RenderDrawLine(renderer, 0, 400, 400, 400);
		//SDL_RenderDrawLine(renderer, 400, 400, 200, 0);
		//SDL_RenderDrawLine(renderer, 200, 0, 0, 400);*/

		//for (int i = 0; i < 255; i++)
		//{
		//	renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0); // create random color
		//	renderer.DrawLine(rand() % 800, rand() % 600, rand() % 800, rand() % 600);
		//}

		//// show screen
		//SDL_RenderPresent(renderer);
		renderer.EndFrame();
	}

	return 0;
}
