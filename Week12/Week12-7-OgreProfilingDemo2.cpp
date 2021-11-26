/** @file Week12-7-OgreProfilingDemo2
 *  @brief Profiling Demo using ogre profiling
    Analyzing Application State
    It is helpful to see the state of your application when a profile reaches a maximum level or some other condition. To check if a specific has reached a new maximum level, use:

    Ogre::Profiler.getSingleton().watchForMax("<profile name>"); // return true if it reaches a new maximum
    or to see if a profile has reached a new minimum level, use:

    Ogre::Profiler.getSingleton().watchForMin("<profile name>"); // returns true if it reaches a new minimum
    or to set an arbitrary level:

    //returns true when AI code takes over 60% of the frame time
    Ogre::Profiler.getSingleton().watchForLimit("AI code", .6, true);
    //returns true when graphics code takes less than 10% of the frame time
    Ogre::Profiler.getSingleton().watchForLimit("Graphics code", .1, false);
    These functions should be used at the end of the main game loop for more accuracy. Otherwise, it will represent the results of the previous frame.

    Logging Results
    You can log the results of the current profiler statistics like this:

    Ogre::Profiler.getSingleton().logResults();
    This is called automatically when you quit your Ogre application.
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include "ConsoleColor.h"
#include <iostream>
using namespace std;
using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _sceneNode;
    Ogre::SceneNode* _camNode;
    float _movementspeed;
    float _mousespeed;
public:

    ExampleFrameListener(Ogre::SceneNode* sceneNode, Ogre::SceneNode* camNode)
    {
        _sceneNode = sceneNode;
        _camNode = camNode;
        _movementspeed = 2.0f;
        _mousespeed = 0.002f;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {

        //!step1: The profiler will need you to specify the main program loop.To do this, you call the following at the very beginning of the 
        //frameStarted() function in your FrameListener class :
        OgreProfileBegin("Ogre Main Loop");

        float rotXNew = rotX * evt.timeSinceLastFrame * -1;
        float rotYNew = rotY * evt.timeSinceLastFrame * -1;

        //Stop camera movement
        //_camNode->yaw(Ogre::Radian(rotXNew * _mousespeed));
        //_camNode->pitch(Ogre::Radian(rotYNew * _mousespeed));
        //_camNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);

        return true;
    }

    bool frameEnded(const Ogre::FrameEvent& evt)
    {
        //returns true when the profiled code takes over 60% of the frame time
        bool result = Ogre::Profiler::getSingleton().watchForLimit("Ogre Main Loop", .60, true);
        if (result)
            cout << green << "Ogre Main Loop took over 60% of the frame time" << white << endl;

        //!step2: Add this at the very end of the frameEnded() function:
        //!Make sure the names match exactly, otherwise the profiler will fail an assert. Next you want to profile some of your code. 
        OgreProfileEnd("Ogre Main Loop");
        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneNode* SinbadNode;
    SceneManager* mScnMgr;
    Root* mRoot;
    Ogre::PolygonMode mPolyMode;
    Camera* cam;
    SceneNode* camNode;
public:
    Game();
    virtual ~Game() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
    bool mouseMoved(const MouseMotionEvent& evt);
    void createFrameListener();
};


Game::Game()
    : ApplicationContext("Week12-6-OgreProfilingDemo")
{
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

    mPolyMode = Ogre::PolygonMode::PM_SOLID;

    //!step3: you must add this in order to add a tray
    mScnMgr->addRenderQueueListener(mOverlaySystem);
    // Give the profiler a timer and enable it
    Ogre::Profiler::getSingleton().setTimer(Root::getSingleton().getTimer());
    Ogre::Profiler::getSingleton().setEnabled(true);
    //You can change how frequently the display is updated to suit your tastes like this
    Ogre::Profiler::getSingleton().setUpdateDisplayFrequency(100);
    //!You can log the results of the current profiler statistics like this
    Ogre::Profiler::getSingleton().logResults();

    //!step4: Next you want to profile some of your code. You do this by calling OgreProfile() and using braces ({}) to limit the scope.
    //!Note that OgreProfile cannot be called in the same scope as another OgreProfile().

    //you have to add this..there is a bug, so system doesn't the first profile
    {
        OgreProfile("Ogre Profile");
    }
    {
        OgreProfile("Scene Profile");
        createScene();
        //returns true when graphics code takes less than 90% of the frame time
        bool result = Ogre::Profiler::getSingleton().watchForLimit("Scene Profile", .90, false);
        if (result)
            cout << green << "Create Scene function took less than 90% of the frame time" << white << endl;
    }
    {
        OgreProfile("Camera Profile");
        createCamera();
    }
    {
        OgreProfile("Frame Profile");
        createFrameListener();
    }

    //you can enable/disable individual profiler
    //Ogre::Profiler.getSingleton().disableProfile("<profile name>");
    //and you can enable it again with this:
    //Ogre::Profiler.getSingleton().enableProfile("<profile name>");

}

void Game::createScene()
{
    // -- tutorial section start --

    Ogre::SceneNode* node = mScnMgr->createSceneNode("Node1");
    mScnMgr->getRootSceneNode()->addChild(node);

    //! [turnlights]
    mScnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    mScnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = mScnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 1.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    //light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = mScnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = node->createChildSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);

    //! [newlight]



    //! [lightDirection]
    lightNode->setDirection(1, -1, 0);
    //! [lightDirection]




    //The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Plane plane(Vector3::UNIT_Y, -10);
    //Now we'll ask the MeshManager to create us a mesh using our Plane blueprint. The MeshManager is already keeping track of the resources we loaded when initializing our application. On top of this, it can create new meshes for us.
    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 200, 200,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);

    //Now we will create a new Entity using this mesh.
    //We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
    Entity* groundEntity = mScnMgr->createEntity("ground");
    mScnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //And finally we need to give our ground a material.
    groundEntity->setMaterialName("Examples/BeachStones");


    Entity* Sinbad = mScnMgr->createEntity("Sinbad.mesh");
    Sinbad->setCastShadows(true);
    SceneNode* SinbadNode = mScnMgr->createSceneNode("SinbadNode");
    SinbadNode->attachObject(Sinbad);
    mScnMgr->getRootSceneNode()->addChild(SinbadNode);
    SinbadNode->setScale(3.0f, 3.0f, 3.0f);
    SinbadNode->setPosition(0, 4.0, 0);

    // -- tutorial section end --
}

void Game::createCamera()
{
    //! [camera]
    camNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    cam = mScnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 100, 200);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
}


void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, camNode);
    mRoot->addFrameListener(FrameListener);
}


bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    rotX = evt.xrel;
    rotY = evt.yrel;
    return true;
}

bool Game::keyPressed(const KeyboardEvent& evt)
{

    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case 'w':
        translate = Ogre::Vector3(0, 0, -1);
        break;
    case 's':
        translate = Ogre::Vector3(0, 0, 1);
        break;
    case 'a':
        translate = Ogre::Vector3(-1, 0, 0);
        break;
    case 'd':
        translate = Ogre::Vector3(1, 0, 0);
        break;
    case 'p':
        translate = Ogre::Vector3(0, 0, 0);
        break;
    case ' ':
        if (mPolyMode == Ogre::PolygonMode::PM_SOLID)
            mPolyMode = Ogre::PolygonMode::PM_WIREFRAME;
        else
            mPolyMode = Ogre::PolygonMode::PM_SOLID;
        cam->setPolygonMode(mPolyMode);
        break;
    default:
        break;
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
