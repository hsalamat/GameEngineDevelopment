/** @file Week10-2-UsingOurOwnRenderingLoop
 *  @brief Using Our Own Rendering Loop
 *  Use OpenGL 3+
 *  We moved the control of the main loop from Ogre 3D to our application. Before this change,
 *  Ogre 3D used an internal main loop over which we hadn't any control and had to rely on the
 *  FrameListener to get notified if a frame was rendered.
 *  Now we have our own main loop. To get there, we needed a Boolean member variable,
 *  which signals if the application wishes to keep running or not 
 *  then we removed the startRendering function call so we wouldn't hand over the control
 *  to Ogre 3D. At the, we created a function, which first calls a helper function of Ogre 3D,
 *  which processes all window events we might have gotten from the operating system. It then
 *  sends all messages we might have created since the last frame, and therefore makes the
 *  application "well-behaved" in the context of the host windowing system.
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <OgreCompositorManager.h>
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _node;
public:

    ExampleFrameListener(Ogre::SceneNode* node)
    {
        _node = node;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        std::cout << "Frame started" << std::endl;
        _node->translate(translate * evt.timeSinceLastFrame);
        translate = Ogre::Vector3(0, 0, 0);
        return true;
    }

    bool frameEnded(const Ogre::FrameEvent& evt)
    {
        
        std::cout << "Frame ended" << std::endl;
        return true;
    }

    bool frameRenderingQueued(const Ogre::FrameEvent& evt)
    {
        std::cout << "Frame queued" << std::endl;
        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneManager* mScnMgr;
    Root* mRoot;
    Camera* mCamera;
    SceneNode* mCamNode;
    bool _keepRunning;
public:
    Game();
    virtual ~Game() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    void renderOneFrame();
    bool keepRunning();
    Ogre::SceneNode* SinbadNode;
};


Game::Game()
    : ApplicationContext("Week10-2")
{
    _keepRunning = true;
}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mScnMgr);
    createCamera();
    createScene();
    createFrameListener();
}

void Game::createScene()
{

    // -- tutorial section start --
    //! [turnlights]
    mScnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = mScnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = mScnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = mScnMgr->createSceneNode("LightNode");
    //lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);


    mScnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]



    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]


    SinbadNode = mScnMgr->getRootSceneNode()->createChildSceneNode("Node1");
    Ogre::Entity* ent = mScnMgr->createEntity("Entity1", "Sinbad.mesh");
    //ent->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial18"));
    SinbadNode->attachObject(ent);
}

void Game::createCamera()
{

    //! [camera]
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    mCamera = mScnMgr->createCamera("myCam");
    mCamera->setNearClipDistance(5); // specific to this sample
    mCamera->setAutoAspectRatio(true);
    mCamNode->attachObject(mCamera);
    mCamNode->setPosition(0, 0, 25);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_LOCAL);

    // and tell it to render into the main window
    Ogre::Viewport* viewport = getRenderWindow()->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        _keepRunning = false;
        break;
    case 'w':
        translate = Ogre::Vector3(0, 10, 0);
        break;
    case 's':
        translate = Ogre::Vector3(0, -10, 0);
        break;
    case 'a':
        translate = Ogre::Vector3(-10, 0, 0);
        break;
    case 'd':
        translate = Ogre::Vector3(10, 0, 0);
        break;
    default:
        break;
    }
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode);
    mRoot->addFrameListener(FrameListener);
}

void Game::renderOneFrame()
{
    //Ogre::WindowEventUtilities::messagePump();
    mRoot->renderOneFrame();
}

bool Game::keepRunning()
{
    return _keepRunning;
}


int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        //app.getRoot()->startRendering();
        while (app.keepRunning())
        {
            app.renderOneFrame();
        }
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}











