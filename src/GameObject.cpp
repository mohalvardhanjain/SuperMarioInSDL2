#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int ow, int oh, int nw, int nh){

    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);


    xpos = x;
    ypos = y;
    width = ow;
    height = oh;
    nwidth = nw;
    nheight = nh;

    srcRect = { 0, 0, ow, oh }; // You might adjust this based on the sprite sheet 
    destRect = { x, y, nw, nh };



    // Animation setup
        frame = 0;
        frameCount = 7;         // Number of frames in sprite
        frameDelay = 100;       // 100 ms between frames = 10 fps
        animTimer = 0.0f;
        lastFrameTime = SDL_GetTicks();
 
}

int GameObject::getX() const {
    return xpos; // xpos is your internal variable tracking the X-position
}

int GameObject::getWidth() const {
    return destRect.w; // width of the object being rendered
}



    void GameObject::setMoveUp(bool value1) {
    moveUp = value1;
}
void GameObject::setMoveDown(bool value2) {
    moveDown = value2;
}
void GameObject::setMoveRight(bool value3) {
    moveRight = value3;
}
void GameObject::setMoveLeft(bool value4) {
    moveLeft = value4;
}


const int frameDelay = 100; // 100ms = 10 FPS animation


void GameObject::Update() {

    // Determine animation state
if (isJumping) {
    animState = AnimationState::Jumping;
} else if (moveRight || moveLeft) {
    animState = AnimationState::Running;
} else if (!moveRight && !moveLeft && !moveUp && !moveDown && !isJumping) {
    animState = AnimationState::Standing;
}

// Set frame ranges based on state
switch (animState) {
    case AnimationState::Standing:
        animStart = 0; animEnd = 0;
        break;
    case AnimationState::Running:
        animStart = 1; animEnd = 3;
        break;
    case AnimationState::Stopping:
        animStart = 4; animEnd = 4;
        break;
    case AnimationState::Jumping:
        animStart = 5; animEnd = 5;
        break;
    case AnimationState::Exiting:
        animStart = 6; animEnd = 6;
        break;
}
if (moveRight || moveLeft) {
    previousWasMoving = true;
}
if (isJumping) {
    animState = AnimationState::Jumping;
} else if (moveRight || moveLeft) {
    animState = AnimationState::Running;
} else if (!moveRight && !moveLeft && previousWasMoving) {
    animState = AnimationState::Stopping;
    previousWasMoving = false;
} else {
    animState = AnimationState::Standing;
}




    // Handle jumping
    if (isJumping) {
        ypos -= velocityY;
        velocityY -= gravity;
        if (ypos >= yGround) {
            ypos = yGround;
            isJumping = false;
            velocityY = 0.0f;
        }
    }

    if (moveUp && !isJumping) {
        isJumping = true;
        velocityY = jumpStrength;
    }

    if (moveRight) {
        xpos += 8;
    }

    // if (moveLeft) {
    //     xpos -= 4;
    // }

    // Update destination rectangle
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = nwidth;
    destRect.h = nheight;

    Uint32 currentTime = SDL_GetTicks();
float deltaTime = currentTime - lastFrameTime;
lastFrameTime = currentTime;
animTimer += deltaTime;

while (animTimer >= frameDelay) {
    frame++;
    if (frame > animEnd) frame = animStart; // loop within range
    srcRect.x = frame * width;              // or 18 if fixed
    animTimer -= frameDelay;
}


    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;
}



void GameObject::Render(SDL_Rect& camera) {
    SDL_Rect renderQuad = {
        destRect.x - camera.x,
        destRect.y - camera.y,
        destRect.w,
        destRect.h
    };

    SDL_RenderCopy(renderer, objTexture, &srcRect, &renderQuad);
}
