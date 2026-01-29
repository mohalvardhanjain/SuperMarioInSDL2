#ifndef Game_hpp
#define Game_hpp

#include<iostream>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class Game {

public:

    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void Render(SDL_Rect& camera);
    void clean();

    bool running(){ return isRunning;}

    SDL_Rect camera;


private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif 