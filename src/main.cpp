#include "Game.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_mixer.h>


Game *game = nullptr;

int main(int argc, const char *argv[]) {
    game = new Game();
    game->init("Why am I doing it !!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1000, false);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
}
Mix_Music* bgm = Mix_LoadMUS("background.mp3");
if (bgm == nullptr) {
    printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
}
Mix_PlayMusic(bgm, -1);


    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();   // Run every frame
        game->update();         // Run every frame
        game->render();         // Run every frame

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime); // Only delay as much as needed
        }
    }
Mix_FreeMusic(bgm);
Mix_CloseAudio();

    game->clean();
    return 0;
}
