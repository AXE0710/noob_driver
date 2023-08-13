#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ctime>
#include <time.h>

// creating window and renderer
SDL_Window *window = SDL_CreateWindow("GAME",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 650, 0);
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);



int main () 
{
    // initializing SDL
    TTF_Init();
    SDL_Init(SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_WEBP);
    int x1 = 0;
    int y1 = 0;
    int score = 0;
    bool quit = false;
    bool game_over = false;
    bool start_game = true;
    SDL_Event event;
    int counter = 0;
    int counter2 = 0;
    int speed = 10;
    int enemy_speed = 0;
    int counter3 = 0;   
    int counter4 = 0;
    
    // random number seed
    srand(time(0));
     
    // loading assets
    SDL_Surface* start = IMG_Load("start.png");
    SDL_Texture* start_tex = SDL_CreateTextureFromSurface(renderer,start);
    SDL_Surface* game_over_text = IMG_Load("over_text.png");
    SDL_Texture* game_over_text_tex = SDL_CreateTextureFromSurface(renderer,game_over_text);
    SDL_Surface* game_over_surface = IMG_Load("gamer.png");
    SDL_Texture* game_over_tex = SDL_CreateTextureFromSurface(renderer,game_over_surface);
    SDL_Surface* enemy_two = IMG_Load("car2.png");
    SDL_Texture* enemy_two_tex = SDL_CreateTextureFromSurface(renderer,enemy_two);
    SDL_Surface* starship = IMG_Load("starship.png");
    SDL_Texture* starship_tex = SDL_CreateTextureFromSurface(renderer,starship);
    SDL_Surface* enemy = IMG_Load("enemy.png");
    SDL_Texture* enemy_tex = SDL_CreateTextureFromSurface(renderer,enemy);
    SDL_Surface* car = IMG_Load("car.webp");
    SDL_Texture* car_tex = SDL_CreateTextureFromSurface(renderer,car);
    SDL_Surface* fuel = IMG_Load("fuel.png");
    SDL_Texture* fuel_tex = SDL_CreateTextureFromSurface(renderer,fuel);
    SDL_Surface* background = IMG_Load("wall.jpeg");
    SDL_Texture* background_tex = SDL_CreateTextureFromSurface(renderer,background);

    // placing assets
    SDL_Rect fuel_rect;
    fuel_rect.x = rand() % 1200;
    fuel_rect.y = rand() % 650;
    fuel_rect.w = 70;
    fuel_rect.h = 70;

    SDL_Rect car_rect;
    car_rect.x = 0;
    car_rect.y = 0;
    car_rect.w = 150;
    car_rect.h = 70;
    float angle = 0;

    SDL_Rect score_box;
    score_box.x = 600;
    score_box.y = 0;
    score_box.h = 30;
    score_box.w = 100;

    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.h = 650;
    background_rect.w = 1200;

    SDL_Rect enemy_rect;
    enemy_rect.x = 0;
    enemy_rect.y = 300;
    enemy_rect.h = 70;
    enemy_rect.w = 150;

    SDL_Rect starship_rect;
    starship_rect.x = 0;
    starship_rect.y = 150;
    starship_rect.h = 70;
    starship_rect.w = 150;

    SDL_Rect enemy_two_rect;
    enemy_two_rect.x = 0;
    enemy_two_rect.y = 450;
    enemy_two_rect.h = 70;
    enemy_two_rect.w = 150;

    SDL_Rect game_over_rect;
    game_over_rect.x = 100;
    game_over_rect.y = 100;
    game_over_rect.h = 500;
    game_over_rect.w = 500;

    SDL_Rect game_over_text_rect;
    game_over_text_rect.x = 600;
    game_over_text_rect.y = 300;
    game_over_text_rect.h = 200;
    game_over_text_rect.w = 300;

    // scoreboard
    char score_text[100];
    sprintf(score_text, "Score: %d", score);
    TTF_Font* font = TTF_OpenFont("font.ttf", 32);
    SDL_Color t = {255, 255, 255};
    SDL_Surface* text = TTF_RenderText_Solid(font, score_text, t);
    SDL_Texture* text_tex = SDL_CreateTextureFromSurface(renderer, text);

    // game condtions
    auto check = [&] () {
        if (fuel_rect.x - 120 < car_rect.x && car_rect.x < fuel_rect.x + 70 && fuel_rect.y - 120 < car_rect.y && car_rect.y < fuel_rect.y + 120) {
            fuel_rect.x = rand() % 1100;
            if (fuel_rect.x < 100) {
                fuel_rect.x += 100;
            }
            fuel_rect.y = rand() % 550;
            if (fuel_rect.y < 100) {
                fuel_rect.y += 100;
            }
            score++;
            SDL_DestroyTexture(text_tex);
            SDL_FreeSurface(text);
            sprintf(score_text, "Score: %d", score);
            text = TTF_RenderText_Solid(font, score_text, t);
            text_tex = SDL_CreateTextureFromSurface(renderer, text);
        }
        if (counter > 10) {
            if (enemy_rect.x<1200) {
                enemy_rect.x += (1 + enemy_speed);
                counter = 0;
            }  
            else if (enemy_rect.x>=1200) {
                counter2++;
                if (counter2 == 5000) {
                    enemy_rect.x = 0;
                    enemy_rect.y = rand() % 550;
                    if (enemy_rect.y < 300)
                    {
                        enemy_rect.y += 100;
                    }
                    counter2 = rand() % 5000;
                }
            }
            if (starship_rect.x<1200) {
                starship_rect.x += (5 + enemy_speed);
                counter = 0;
            }  
            else if (starship_rect.x>=1200) {
                counter3++;
                if (counter3 == 15000) {
                    starship_rect.x = 0;
                    starship_rect.y = rand() % 550;
                    if (starship_rect.y < 300)
                    {
                        starship_rect.y += 100;
                    }
                    counter3 = rand() % 15000;
                }
            }
            if (enemy_two_rect.x<1200) {
                enemy_two_rect.x+= (2 + enemy_speed);
                counter = 0;
            }  
            else if (enemy_two_rect.x>=1200) {
                counter4++;
                if (counter4 == 5000) {
                    enemy_two_rect.x = 0;
                    enemy_two_rect.y = rand() % 550;
                    if (enemy_two_rect.y < 300)
                    {
                        enemy_two_rect.y += 100;
                    }
                    counter4 = rand() % 5000;
                }
            }
        }
        if (car_rect.x < enemy_rect.x + 120 && car_rect.x + 150 > enemy_rect.x && car_rect.y < enemy_rect.y + 70 && car_rect.y + 70 > enemy_rect.y) {
            game_over = true;
        }
        if (car_rect.x < starship_rect.x + 120 && car_rect.x + 150 > starship_rect.x && car_rect.y < starship_rect.y + 70 && car_rect.y + 70 > starship_rect.y) {
            game_over = true;
        }
        if (car_rect.x < enemy_two_rect.x + 120 && car_rect.x + 150 > enemy_two_rect.x && car_rect.y < enemy_two_rect.y + 70 && car_rect.y + 70 > enemy_two_rect.y) {
            game_over = true;
        }        

    };

    // displaying assets
    auto draw = [&] () {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_tex, NULL, &background_rect); // keep this first
        if (fuel_tex != NULL) {
            SDL_RenderCopy(renderer, fuel_tex, NULL, &fuel_rect);
        }
        if (text_tex != NULL) {
            SDL_RenderCopy(renderer, text_tex, NULL, &score_box);  
        }
        SDL_RenderCopy(renderer, enemy_two_tex, NULL, &enemy_two_rect);
        SDL_RenderCopy(renderer, starship_tex, NULL, &starship_rect);
        SDL_RenderCopy(renderer, enemy_tex, NULL, &enemy_rect);
        SDL_RenderCopyEx(renderer, car_tex, NULL, &car_rect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    };

    // game loop
    while (!quit) {
        // SDL_Delay(10);
        while(start_game){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background_tex, NULL, &background_rect);
            SDL_RenderCopy(renderer, game_over_tex, NULL, &game_over_rect);
            SDL_RenderCopy(renderer, start_tex, NULL, &game_over_text_rect);
            SDL_RenderPresent(renderer);
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x1 = event.button.x;
                y1 = event.button.y;
                if (x1 > 500 && x1 < 700 && y1 > 300 && y1 < 400) {
                    start_game = false;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    start_game = false;
                    break;
                
                default:
                    break;
                }
            }
        }
        counter++;

        SDL_PollEvent(&event);

        // controls
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            x1 = event.button.x;
            y1 = event.button.y;
            while
             (car_rect.x != (x1 - 100))
            {
                SDL_Delay(10);
                SDL_RenderClear(renderer);
                if (car_rect.x < (x1 - 100)) {
                    car_rect.x++;
                    angle = 0;
                } else {
                    car_rect.x--;
                    angle = 180;
                }
                check();
                draw();
                
            }
            while (car_rect.y != (y1 - 100))
            {
                SDL_Delay(10);
                SDL_RenderClear(renderer);
                if (car_rect.y < (y1 - 100)) {
                    car_rect.y++;
                    angle = 90;
                } else {
                    car_rect.y--;
                    angle = 270;
                }
                check();
                draw();  
            }   
            
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                if (car_rect.y > 0){
                    car_rect.y = car_rect.y - speed;
                }            
                angle = 270;
                check();
                draw();
                break;
            case SDLK_DOWN:
                if (600 > car_rect.y){
                    car_rect.y = car_rect.y + speed;
                }
                angle = 90;
                check();
                draw();


                break;
            case SDLK_LEFT:
                if (car_rect.x > 0){
                    car_rect.x = car_rect.x - speed;
                }
                angle = 180;
                check();
                draw();

                break;
            case SDLK_RIGHT:
                if (1100 > car_rect.x){
                    car_rect.x = car_rect.x + speed;
                }
                angle = 0;
                check();
                draw();
                break;
            default:
                break;
            }
            break;
        }
        check();
        draw();

        while(game_over) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background_tex, NULL, &background_rect);
            SDL_RenderCopy(renderer, game_over_tex, NULL, &game_over_rect);
            SDL_RenderCopy(renderer, text_tex, NULL, &score_box);
            SDL_RenderCopy(renderer, game_over_text_tex, NULL, &game_over_text_rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                game_over = false;
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    game_over = false;
                    quit = false;
                    car_rect.x = 0;
                    car_rect.y = 0;
                    score = 0;
                    start_game = true;
                    draw();
                    check();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

    }

    // cleaning up
    SDL_DestroyTexture(car_tex);
    SDL_FreeSurface(car);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}