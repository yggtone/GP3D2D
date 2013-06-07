#ifndef SPRITE_H_
#define SPRITE_H_


#include "gameplay.h"
#include <vector>

using namespace gameplay;


//Animated Sprite class, defaults to non-animated Sprite if animation rows and columns are 1

class Sprite
{
public:
    Sprite(const char* texturePath, bool filtering, float animationFPS = 30.f, int animationCols = 1, int animationRows = 1);
    ~Sprite();
    
    void Draw();
    
    void Update(float deltaTime);
    
    void setProjectionMatrix(Matrix pvmatrix );
    
    void setFrame(int frameNum);
    int getFrame(){ return currentFrame; };
    void setPosition(float x, float y);
    
    float getX() { return positionX; };
    float getY() { return positionY; };
    
    float getScaleX() { return scaleX; };
    float getScaleY() { return scaleY; };
    
    void setScale(float scale) { scaleX = scale; scaleY = scale; };
    void setScale(float scaleX, float scaleY) { this->scaleX = scaleX; this->scaleY = scaleY; };
    
private:
    
    SpriteBatch* batch;
    
    int frameWidth, frameHeight;
    int totalFrames;
    int animationRows;
    int animationCols;
    int currentFrame;
    bool isAnimated;
    
    float positionX, positionY;
    
    std::vector<Rectangle*> frameRectangles;
    
    float scaleX, scaleY;
    
    float currentFrameTime;
    float animationTimePerFrame;
    
};



#endif