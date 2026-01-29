# pragma once
# include "Game.hpp"



enum class AnimationState {
    Standing,
    Running,
    Stopping,
    Jumping,
    Exiting
};



class GameObject{

    public:
        GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y, int owidth, int oheight, int newwidth, int newheight);


        ~GameObject();

        void Update();
        void Render(SDL_Rect& camera);  // ✅ takes camera now
        void jump();
        void setMoveUp(bool value1);
        void setMoveDown(bool value2);
        void setMoveRight(bool value3);
        void setMoveLeft(bool value4);   
        
        
        int getX() const;
        int getWidth() const;

        

    private:

        bool previousWasMoving = false;
        float velocityY = 0.0f; 
        float gravity = 1.0f; 
        float jumpStrength = 30.0f;
        int frameWidth = 16;
        int frameHeight = 32;

        // int animationFrame = 0;
        // int frameCounter = 0;
        // int frameDelay = 10; // Tune for frame speed

        // int totalWalkFrames = 3;

        // int standFrameX = 0;
        // int crouchFrameX = 2;
        // int jumpFrameX = 1;

        int walkRowY = 0;
        int jumpRowY = 32;
        int crouchRowY = 64;

        // Add movement state booleans if not already present
        bool isJumping = false;
        bool isCrouching = false;

        int jumpTime = 0;
        bool moveUp = false;
        bool moveDown = false;
        bool moveRight = false;
        bool moveLeft = false;
        int xpos;
        int ypos;
        int yGround = 755;



        


        int frame;
        int frameCounter;
        int frameDelay; // 10 frames between each sprite update (~6 updates/sec at 60 fps)
        int frameCount;  // total frames in animation
        int animTimer;
        Uint32 lastFrameTime;      // Time when last frame was updated
        

        AnimationState animState = AnimationState::Standing;

        // New fields for current animation range
        int animStart = 0, animEnd = 0;


        int width, height, nwidth, nheight;  // Add this line

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;
};
