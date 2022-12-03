#include <iostream>
#include <SDL.h>
#include <time.h>
using namespace std;
const int size_array = 100;

class tPoint {
private:
	const char* title = "Lab_3";
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int DOT_WIDTH = 20;
	const int DOT_HEIGHT = 20;
	const int DOT_VEL = 10;
	int mPosX=0, mPosY=0, mVelX=0, mVelY=0;
	SDL_Window* win = NULL;
	SDL_Renderer* ren = NULL;
	SDL_Surface* bmp = NULL;
	SDL_Texture* tex = NULL;
public:
	void Create_RenderWindow() {
		win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}
	void SetBackground() {
		bmp = SDL_LoadBMP("background.bmp");
		tex = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
	}
	void Destroy_Everything() {
		SDL_DestroyTexture(tex);
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}
	void Dots_Move()
	{
		mPosX += mVelX;

		if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
		{
			mPosX -= mVelX;
		}
	}
	//void Dots_Render()
	//	{
	//		//Show the dot
	//		gDotTexture.Dots_Render(mPosX, mPosY);
	//	}
};
int SDL_main(int argc, char* argv[]) 
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	bool quit = false;
	SDL_Event event;
	tPoint arr[size_array],open;
	int show_time = 10000;
	
	open.Create_RenderWindow();
	open.SetBackground();

	SDL_Delay(show_time);
	
	return 0;
}