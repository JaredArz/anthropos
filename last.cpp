#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <math.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define P_WIDTH 150
#define P_HEIGHT 100
#define PI 3.14159265358979323846264

bool init(void);

SDL_Window *gWindow = NULL;
SDL_Renderer *renderer = NULL;

//Key press surfaces constants
enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init(void){

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ) )
        printf( "Warning: Linear texture filtering not enabled!" );

    SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    //Create window
    gWindow = SDL_CreateWindow( "anthropos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ){
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Create renderer for window
    renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == NULL ){
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Initialize renderer color

    SDL_SetRenderDrawColor(renderer,255,0,0,255);


	return true;
}


int main( int argc, char* args[] ){
	if( !init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}

    SDL_Surface *player_s = NULL;
    player_s = SDL_LoadBMP("./reading/background.bmp");
    SDL_Texture *player = NULL;
    player = SDL_CreateTextureFromSurface(renderer,player_s);
    SDL_FreeSurface( player_s );

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit ){
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            //User presses a key
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        ;
                    break;

                    case SDLK_DOWN:
                        ;
                    break;

                    case SDLK_LEFT:
                        ;
                    break;

                    case SDLK_RIGHT:
                        ;
                    break;

                    default:
                    ;
                    break;
                }
            }
        }


        SDL_RenderClear( renderer );
        SDL_RenderCopy( renderer, player, NULL, NULL );
        SDL_RenderPresent( renderer );
        SDL_Delay(150);
    }

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( gWindow );
	gWindow   = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
    SDL_DestroyTexture( player );
    player = NULL;

	return 0;
}
