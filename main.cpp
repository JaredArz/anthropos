#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define WIDTH  600
#define HEIGHT 600
#define P_WIDTH 150
#define P_HEIGHT 100
#define PI 3.14159265358979323846264
#define CENTER_X 960
#define CENTER_Y 540

int main( int argc, char* args[] ){
    printf("entry");
    SDL_Window  *window = NULL;
    SDL_Surface *screenSurface = NULL;

    printf("starting init");
    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else{
        printf("creating window");
		//Create window
		window = SDL_CreateWindow( "anthropos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
            printf("creating surface");
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );
		}
	}
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    printf("creating renderer");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    printf("starting texture");
    SDL_Surface* player = NULL;
    player = SDL_LoadBMP("ship.bmp");
    SDL_Texture  *sdlTexture = NULL;
    sdlTexture = SDL_CreateTextureFromSurface(renderer,player);
    SDL_FreeSurface( player );
    
    printf("starting logic");
    int i = 1000;
    float x_pos, y_pos, x_i, y_i;
    float r = 125;
    SDL_Rect hitbox;
    x_pos = x_i = WIDTH/2 - P_WIDTH/2;
    y_pos = y_i = HEIGHT/2; 
    hitbox.x = x_i;
    hitbox.y = y_i;
    hitbox.w = P_WIDTH;
    hitbox.h = P_HEIGHT;

    while( i > 0 ){
        SDL_Event e;
        // Communicate with operating systems
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                break;
            }
            // Handle events
        }

        // "Frame" logic
        hitbox.x = (r * -1 * cos(2 * PI * x_pos)) + 300;
        hitbox.y = (r * -1 * sin(2 * PI * y_pos)) + 250;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, sdlTexture, NULL, &hitbox);
        SDL_RenderPresent(renderer);
        SDL_Delay(175);
        --i, x_pos += PI/48, y_pos += PI/48;
    }

    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
