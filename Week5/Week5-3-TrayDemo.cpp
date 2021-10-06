/** @file Week5-3-TrayDemo.cpp
 *  @brief Using Tray Manager
 *
 * To use Trays, you have to create an TrayManager. This is the class through which you will create and
 * manage all your widgets, manipulate the cursor, change the backdrop image, adjust tray properties,
 * pop up dialogs, show/hide the loading bar, etc. You can have multiple tray managers in one application.
 *
 *
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class Game
    : public ApplicationContext
    , public InputListener
{
public:

    Game();
    virtual ~Game() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;
};


Game::Game()
    : ApplicationContext("TrayDemo")
{
}

/// Initialize the game
void Game::setup()
{
    //! do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    //! get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    //! register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);    

    //! turnlights
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    //! newlight
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);

    //! lightpos
    lightNode->setPosition(20, 80, 50);

    //! camera
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    //! create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    //! and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    //! cameramove
    camNode->setPosition(0, 47, 222);

    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    
    /// @attention you must add mOverlaySystem to Render Queue Listener in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);

    /// @note Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "My Game Engine", 350);

}


bool Game::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]
