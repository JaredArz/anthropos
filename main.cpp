#include <stdio.h>
#include <math.h>
#include "SDL.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WIDTH 600
#define HEIGHT 600
#define P_WIDTH 150
#define P_HEIGHT 100
#define PI 3.14159265358979323846264

int main( int argc, char* args[] ){
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window   *sdlWindow;
    SDL_Renderer *sdlRenderer;
    SDL_Texture  *sdlTexture;
    SDL_CreateWindowAndRenderer(0,0,SDL_WINDOW_FULLSCREEN_DESKTOP, &sdlWindow, &sdlRenderer);
    SDL_SetRenderDrawColor(sdlRenderer,0,0,0,255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    SDL_RenderSetLogicalSize(sdlRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    SDL_Surface* player = NULL;
    player = SDL_LoadBMP("ship.bmp");
    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer,player);
    SDL_FreeSurface( player );
    
    int i = 1000;
    float x_pos, y_pos, x_i, y_i;
    float r = 100;
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
        hitbox.x = (r * -1 * cos(x_pos))  + x_i/2;
        hitbox.y = (r * -1 * sin(y_pos))  + y_i/2;
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &hitbox);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(175);
        --i, x_pos += PI/24, y_pos += PI/24;
    }

    SDL_Quit();
    return 0;
}
