#include "Sprite.h"



Sprite::Sprite(const char* texturePath, bool filtering, float animationFPS, int animationCols,
 int animationRows ) : frameWidth(1),
frameHeight(1), totalFrames(1), animationRows(1), animationCols(1),
currentFrame(1), isAnimated(false), positionX(0.f), positionY(0.f),
scaleX(1.f),scaleY(1.f),currentFrameTime(0.f),animationTimerPerFrame(1.f)
{
    scaleX = 1.0f;
    scaleY = 1.0f;
    
    currentFrame = 0;
    positionX = 0;
    positionY = 0;
    
    this->animationCols = animationCols;
    this->animationRows = animationRows;
    if(animationCols < 1)
        animationCols = 1;
    if(animationRows < 1)
        animationRows = 1;
    if(animationCols == 1 && animationRows == 1)
        isAnimated = false;
    else
        isAnimated = true;
    
    animationTimePerFrame = 1.f/animationFPS;
    
    totalFrames = animationCols * animationRows;
    
    batch = SpriteBatch::create(texturePath); 
    
    frameWidth = batch->getSampler()->getTexture()->getWidth() / animationCols ;
    frameHeight = batch->getSampler()->getTexture()->getHeight() / animationRows;
    
    for(int i=0; i < animationRows  ; i++)
    {
        for(int j=0; j < animationCols; j++)
        {
            Rectangle* frameRect = new Rectangle(j * frameWidth, i * frameHeight, frameWidth, frameHeight);
            frameRectangles.push_back(frameRect);
        }
    }
    
    batch->getSampler()->setWrapMode(Texture::CLAMP, Texture::CLAMP);

    
    if(filtering)
        batch->getSampler()->getTexture()->setFilterMode(Texture::LINEAR,Texture::LINEAR);
    else
        batch->getSampler()->getTexture()->setFilterMode(Texture::NEAREST,Texture::NEAREST);
    
    
}


Sprite::~Sprite()
{
    SAFE_DELETE(batch);
    
    //delete rectangle objects
    std::vector<Rectangle*>::iterator iter;    
    for (iter = frameRectangles.begin(); iter <  frameRectangles.end(); iter++ ) {
        delete *iter;
    }
}

void Sprite::Update(float deltaTime)
{
    currentFrameTime += deltaTime;
    if(currentFrameTime > animationTimePerFrame )
    {
        currentFrameTime = 0;
        currentFrame++;
        if(currentFrame >= totalFrames)
            currentFrame = 0;
    }
}

void Sprite::setFrame(int frameNum)
{
    currentFrame = frameNum;
    if(currentFrame < 0)
        currentFrame = 0;
    else if(currentFrame >= totalFrames)
        currentFrame = 0;
}

void Sprite::setPosition(float x, float y)
{
    positionX = x;
    positionY = y;
}


void Sprite::setProjectionMatrix(Matrix pvmatrix)
{
    batch->setProjectionMatrix(pvmatrix);
}


void Sprite::Draw()
{
    //draw sprite at current position, scale, with current animation frame 
    batch->start();
    batch->draw(Rectangle( positionX, positionY,(float) frameWidth * scaleX,
     (float) frameHeight * scaleY), *frameRectangles[currentFrame], Vector4::one());
    batch->finish();
   
}


