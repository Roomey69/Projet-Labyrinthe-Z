#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

// gcc src/testsdl2.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2

void clean(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
    
    if(t)
        SDL_DestroyTexture(t);
    if(r)
        SDL_DestroyRenderer(r);
    if(w)
        SDL_DestroyWindow(w);
    SDL_Quit();
}

int main(int argc, char **argv)
{
    
    SDL_Window *window = NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *plateau = NULL;
    SDL_Rect rect_plateau = {(1920-522)/2, (1080-522)/2, 522, 522};
    SDL_Rect rect_plateau2 = {771, 297 , 18, 486};
    SDL_Rect rect_plateau3 = {717, 351 , 486, 18};

    if(SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Erreur init > %s\n",SDL_GetError());
        clean(NULL,NULL,NULL);
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Labyrinthe-Z", 0, 0, 1980, 1080, SDL_WINDOW_FULLSCREEN);
    if( window == NULL ){
        SDL_Log("Erreur create_window > %s\n",SDL_GetError());
        clean(NULL,NULL,NULL);
        exit(EXIT_FAILURE);        
    }

    rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if( rendu == NULL ){
        SDL_Log("Erreur render > %s\n",SDL_GetError());
        clean(window,NULL,NULL);
        exit(EXIT_FAILURE);        
    }     

    SDL_SetRenderDrawColor(rendu, 255, 233, 210, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawColor(rendu, 229, 204, 178, 255);
    for( int i=0 ; i<18 ; i++){
        SDL_RenderDrawRect(rendu,&rect_plateau);
        rect_plateau.h -= 2;
        rect_plateau.w -= 2;
        rect_plateau.x = (1920-(rect_plateau.w))/2;
        rect_plateau.y = (1080-(rect_plateau.h))/2;
    }

    for( int i=0 ; i<6 ; i++){
        SDL_RenderFillRect(rendu,&rect_plateau2);
        rect_plateau2.x += 4*18;
    }

    for( int i=0 ; i<6 ; i++){
        SDL_RenderFillRect(rendu,&rect_plateau3);
        rect_plateau3.y += 4*18;
    }

    SDL_RenderPresent(rendu);

    SDL_bool launched = SDL_TRUE;

    while( launched ){

        SDL_Event event;

        while( SDL_PollEvent(&event) ){

            switch( event.type ){
            case SDL_KEYDOWN:
                
                switch ( event.key.keysym.sym ){
                case SDLK_ESCAPE:
                    launched = SDL_FALSE;
                    break;
                }

            case SDL_QUIT:
                launched = SDL_FALSE;
                break;

            default:
                break;
            }

        }

    }

    SDL_DestroyTexture(plateau);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



    /*rendu_image = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if( rendu_image == NULL ){
        SDL_Log("Erreur render_image > %s\n",SDL_GetError());
        clean(window,NULL,NULL);
        exit(EXIT_FAILURE);        
    }   

    image = SDL_LoadBMP("src/test.bmp");
    if( image == NULL ){
        SDL_Log("Erreur load_image > %s\n",SDL_GetError());
        clean(window,rendu_image,NULL);
        exit(EXIT_FAILURE);
    }

    texture_image = SDL_CreateTextureFromSurface(rendu_image,image);
    SDL_FreeSurface(image);
    if( texture_image == NULL ){
        SDL_Log("Erreur creation texture > %s\n",SDL_GetError());
        clean(window,rendu_image,NULL);
        exit(EXIT_FAILURE);        
    }

    if( SDL_QueryTexture(texture_image, NULL, NULL, &rect_image.w, &rect_image.h) ){
        SDL_Log("Erreur querytexture > %s\n",SDL_GetError());
        clean(window, rendu_image, texture_image);
        exit(EXIT_FAILURE);         
    }

    rect_image.x = (1920 - rect_image.w) / 2;       // REVOIR POUR CENTRER
    rect_image.y = (1080 - rect_image.h) / 2; 


    if( SDL_RenderCopy(rendu_image, texture_image, NULL, &rect_image) ){
        SDL_Log("Erreur rendercopy > %s\n",SDL_GetError());
        clean(window, rendu_image, texture_image);
        exit(EXIT_FAILURE); 
    }*/