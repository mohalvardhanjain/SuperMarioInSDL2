#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#define LEVEL_WIDTH 14000  // or however wide your level is



GameObject* player;
GameObject* background;
// GameObject* smallenemy;
// GameObject* browser;


SDL_Rect camera = { 0, 0, 1536, 864 };


Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscrean)
{
    int flags = 0; 
    if(fullscrean){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0){
        std::cout<< "Subsystem Initialised!..."<<std::endl;

        window = SDL_CreateWindow("Why am i doing it !!!", xpos, ypos, width, height, flags);
        if(window){
            std::cout<< "Window Created!"<<std::endl; 

        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 146, 145, 255, 255);
            std::cout<<"Renderer created!"<<std::endl;
            isRunning = true;
        }
        
        else{
            isRunning = false;  
        }

      
       background = new GameObject("World1-1.png", renderer, 0, 0, 3376, 480, 14396, 1900);
       player = new GameObject("basicmovements.png", renderer, 0, 755, 19, 17, 75 ,75);
    //    smallenemy = new GameObject("smallenemy.png", renderer, 200, 200);
    //    browser = new GameObject("browser.png",renderer, 400, 400);
        }

    camera.x = 0;
    camera.y = 0;
    camera.w = 1536;  // Width of your screen
    camera.h = 800;  // Height of your screen


    }

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
{
case SDL_QUIT:
    isRunning = false;
    break;

case SDL_KEYDOWN:
{
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_a:
        // std::cout << "A pressed" << std::endl;
        player->setMoveLeft(true);
        break;

    case SDLK_UP:
    case SDLK_w:
    case SDLK_SPACE:
        // std::cout << "W pressed" << std::endl;
        player->setMoveUp(true);
        break;

    case SDLK_DOWN:
    case SDLK_s:
        // std::cout << "S pressed" << std::endl;
        player->setMoveDown(true);
        break;

    case SDLK_RIGHT:
    case SDLK_d:
        // std::cout << "D pressed" << std::endl;
        player->setMoveRight(true);
        break;
    }
    break;
}


case SDL_KEYUP:
{
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_a:
        player->setMoveLeft(false);
        break;

    case SDLK_DOWN:
    case SDLK_s:
        player->setMoveDown(false);
        break;

    case SDLK_RIGHT:
    case SDLK_d:
        player->setMoveRight(false);
        break;

    case SDLK_UP:
    case SDLK_w:
    case SDLK_SPACE:
        player->setMoveUp(false);
        break;
    }
    break;
}



// case SDL_MOUSEBUTTONDOWN:
//     std::cout << "Mouse Clicked at " << event.button.x << ", " << event.button.y << std::endl;
//     break;

default:
    break;
}

}
void Game::update()
{
    
   player->Update();
//    background->Update();
//    smallenemy->Update();
//    browser->Update();

camera.x = player->getX() - 1536 / 2 + player->getWidth() / 2;

// Clamp camera to level bounds
if (camera.x < 0) camera.x = 0;
if (camera.x > 13000 - camera.w) camera.x = 13000 - camera.w;

    camera.x = player->getX() - camera.w / 2 + player->getWidth() / 2;

// Clamp the camera to the level bounds (so it doesn't scroll too far left/right)
if (camera.x < 0) camera.x = 0;
if (camera.x > LEVEL_WIDTH - camera.w) camera.x = LEVEL_WIDTH - camera.w;




// std::cout << "Player X: " << player->getX()<< " | Camera X: " << camera.x << std::endl;


   
}
void Game::render()
{
    SDL_RenderClear(renderer);
    //this is where we would add stuff to render

    // player->Render();
    // smallenemy->Render();
    // browser->Render();

    background->Render(camera);
    player->Render(camera);
    


    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    std::cout<<"Window Cleaned"<<std::endl;
}



