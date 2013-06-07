#ifndef MAINGAME_H_
#define MAINGAME_H_

#include "gameplay.h"

#include "Sprite.h"

using namespace gameplay;

/**
 * Main game class.
 */
class MainGame: public Game
{
public:


    /**
     * Constructor.
     */
    MainGame();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);

    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    Scene* _scene;


    //world(area within letterbox) dimensions
    float worldWidth, worldHeight;
    //use fixed (letterbox capable) or stretched display
    bool fixedAspectRatio;
    


    
    SpriteBatch* batch;
    
    Sprite* testAnimatedSprite;
    
    //matrix used to transform sprite batches to fixed coordinates
    Matrix spriteMatrix;
    
};

#endif
