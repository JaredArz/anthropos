#include <SDL2/SDL.h>
//#include <SDL_image.h>
#include <stdio.h>
#include <string>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define P_WIDTH 150
#define P_HEIGHT 100
#define PI 3.14159265358979323846264

bool init();
void close();
SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init(){

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        printf( "Warning: Linear texture filtering not enabled!" );

    //Create window
    gWindow = SDL_CreateWindow( "anthropos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ){
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL ){
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

	return true;
}


void close(*renderer, *window ){
	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	gWindow   = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}



int main( int argc, char* args[] ){
    int i = 1000;
    float x_pos, y_pos, x_i, y_i;
    float r = 125;
    SDL_Rect hitbox;
    x_pos = x_i = SCREEN_WIDTH/2 - P_WIDTH/2;
    y_pos = y_i = SCREEN_HEIGHT/2;
    hitbox.x = x_i;
    hitbox.y = y_i;
    hitbox.w = P_WIDTH;
    hitbox.h = P_HEIGHT;
    SDL_Texture* player_texture = NULL;
    player_texture = loadTexture("./ship.bmp");

	//Start up SDL and create window
	if( !init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}

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

        hitbox.x = (r * -1 * cos(2 * PI * x_pos)) + 300;
        hitbox.y = (r * -1 * sin(2 * PI * y_pos)) + 250;
        --i, x_pos += PI/48, y_pos += PI/48;

        SDL_RenderClear( gRenderer );
        SDL_RenderCopy( gRenderer, player_texture, NULL, &hitbox );
        SDL_RenderPresent( gRenderer );
        SDL_Delay(175);
    }

	//Free resources and close SDL
	close();
    SDL_DestroyTexture( player_texture );
    player_texture = NULL;

	return 0;
}
