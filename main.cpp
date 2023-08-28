#include <stdio.h>
#include <math.h>
#include "SDL.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WIDTH 600
#define HEIGHT 600
#define P_WIDTH 100
#define P_HEIGHT 50
#define PI 3.14159

int main( int argc, char* args[] ){

    //SDL_Surface* screen = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );
    /*
    SDL_Window *screen = SDL_CreateWindow("anthropos",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

    */
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
    float x_pos, y_pos,x_i,y_i;
    float r = 25;
    SDL_Rect hitbox;
    hitbox.x = x_pos = x_i = WIDTH/2 - P_WIDTH/2;
    hitbox.y = y_pos = y_i = HEIGHT/2; 
    hitbox.w = P_WIDTH;
    hitbox.h = P_HEIGHT;



    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &hitbox);
    SDL_RenderPresent(sdlRenderer);
    SDL_Delay(100);


    while( i > 0 ){
        hitbox.x = (r * -1 * cos(x_pos) ) + x_i;
        hitbox.y = (r * -1 * sin(y_pos)) + y_i;
        x_pos += PI/4;
        y_pos += PI/4;
        
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &hitbox);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(75);
        --i;//, x_pos += PI/10, y_pos += PI/10;// r += i/10;

    }

    /*
    while( i > 0 )
        //SDL_Rect src;
        //src.x = 0;
        //src.y = 0;
        //src.w = P_WIDTH;
        //src.w = P_HEIGHT;
        //hitbox.x = r * cos(x_pos);
        //hitbox.x = r * cos(x_pos);
        hitbox.y += 1;
        hitbox.y += 1;
        
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &hitbox);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000);
        --i;//, x_pos += PI/10, y_pos += PI/10;// r += i/10;
    */

    
    SDL_Quit();
    return 0;
}
