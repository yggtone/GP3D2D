#include "MainGame.h"



// Declare our game instance
MainGame game;

MainGame::MainGame()
    : _scene(NULL), worldWidth(128.f), worldHeight(128.f), fixedAspectRatio(false),
    batch(NULL), testAnimatedSprite(NULL)
{
}







void MainGame::initialize()
{

    fixedAspectRatio = true;
    worldWidth = 600;
    worldHeight = 300;
    Rectangle worldSize(worldWidth, worldHeight);

    
    static const float screenAspectRatio = (float)getHeight() / (float)getWidth();
    static const float worldAspectRatio = worldSize.height / worldSize.width;
    

    //center viewport leaving letterbox/pillarbox space if aspect ratio is fixed
    if(fixedAspectRatio)
    {	
	    if(screenAspectRatio >= worldAspectRatio )//letterbox
	    {
	        //float letterboxedHeight = (worldSize.width * screenAspectRatio);
	        float newWorldHeight = (float)getWidth() * worldAspectRatio;	
	        float letterBoxHeight = .5f * (getHeight() - newWorldHeight );	
	        this->setViewport( Rectangle(0, letterBoxHeight, (float)getWidth(), newWorldHeight) );
	    }
	    else if(screenAspectRatio < worldAspectRatio) //pillarbox
	    {
	        float newWorldWidth = (float)getHeight() * 1.f/worldAspectRatio;
	        float pillarBoxPositionX = .5f * (getWidth() - newWorldWidth );
	        this->setViewport(Rectangle(pillarBoxPositionX, 0, newWorldWidth, (float)getHeight()) );
	
	    }
	
    }
    
    
    
    
    

    //create projection and view matrix for sprite batches,
    // so coordinates will be in world space rather than screen resolution
    Matrix projectionMatrix;
    float halfWidth = worldSize.width / 2, halfHeight = worldSize.height / 2;

    Matrix::createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight,
     0, 1, &projectionMatrix);

    // view matrix, looking down with x,y axis starting at the top left corner of the screen
    Matrix viewMatrix;
    Matrix::createLookAt(halfWidth, halfHeight , 0, halfWidth, halfHeight , 1, 0, -1, 0,
     &viewMatrix);

    Matrix::multiply(projectionMatrix, viewMatrix, &spriteMatrix);

    
    
    
    
    
    //example sprite batch, to show current world area in viewport
    batch = SpriteBatch::create("res/main.png");
    batch->setProjectionMatrix(spriteMatrix);


    
    testAnimatedSprite = new Sprite("res/testAnim.png",false,10.f, 3, 2);
    testAnimatedSprite->setProjectionMatrix(spriteMatrix);


    
    
    // Load 3D game scene from file
    Bundle* bundle = Bundle::create("res/box.gpb");
    _scene = bundle->loadScene();
    SAFE_RELEASE(bundle);
    // Get light node
    Node* lightNode = _scene->findNode("directionalLight");
    Light* light = lightNode->getLight();
    // Initialize box model
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = boxNode->getModel();
    Material* boxMaterial = boxModel->setMaterial("res/box.material");
    boxMaterial->getParameter("u_ambientColor")->setValue(_scene->getAmbientColor());
    boxMaterial->getParameter("u_lightColor")->setValue(light->getColor());
    boxMaterial->getParameter("u_lightDirection")->setValue(lightNode->getForwardVectorView());
    //configure 3D camera to match viewport aspect ratio
    if(fixedAspectRatio)
    {
	_scene->getActiveCamera()->setAspectRatio(worldSize.width / worldSize.height);
    }
    else
    {
	_scene->getActiveCamera()->setAspectRatio((float)getWidth() / (float)getHeight());
    }

}

void MainGame::finalize()
{
    SAFE_RELEASE(_scene);
    
    SAFE_DELETE(batch);
    SAFE_DELETE(testAnimatedSprite);
}

void MainGame::update(float elapsedTime)
{
    // Rotate model
    _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
    
    //update sprite animation time
    testAnimatedSprite->Update((float)elapsedTime / 1000.0f );
    //scale testing
    //testAnimatedSprite->setScale(testAnimatedSprite->getScaleX(), testAnimatedSprite->getScaleY() + (float)elapsedTime /1000.f);
}

void MainGame::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &MainGame::drawScene);


    // Draw your sprites
    batch->start();
    batch->draw(Rectangle(0, 0, worldWidth, worldHeight),
                 Rectangle(0, 0, 128, 128), Vector4::one());    
    // SpriteBatch::draw() can be called multiple times between start() and finish()
    batch->finish();

    
    testAnimatedSprite->Draw();
   
}

bool MainGame::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel();
    if (model)
    {
        model->draw();
    }
    return true;
}

void MainGame::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void MainGame::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}
