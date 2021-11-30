/** @file week13-5-SkyboxDemo2
 *  @brief Skybox Demo 2
 *  mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 300, false);
 *  The third parameter is the distance between the Camera and the SkyBox.
 *  Compile and run your application. Nothing has changed. 
 *  This is because the fourth parameter sets whether or not to render the SkyBox before the rest of the scene. If the SkyBox is rendered first, then no matter how close it is the rest of your scene objects will be rendered on top of it.
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */


#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

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

        float rotXNew = rotX * evt.timeSinceLastFrame * -1;
        float rotYNew = rotY * evt.timeSinceLastFrame * -1;


        //_camNode->yaw(Ogre::Radian(rotXNew));
        //_camNode->pitch(Ogre::Radian(rotYNew));

        _camNode->yaw(Ogre::Radian(rotXNew * _mousespeed));
        _camNode->pitch(Ogre::Radian(rotYNew * _mousespeed));

        //_camNode->moveRelative(translate * evt.timeSinceLastFrame * _movementspeed);
        _camNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);
                
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
    : ApplicationContext("Week13-5-SkyboxDemo2")
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

    createScene();
    createCamera();
    createFrameListener();
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

    //Entity* groundEntity = mScnMgr->createEntity("ground");
    //mScnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    //groundEntity->setCastShadows(false);
    //groundEntity->setMaterialName("Examples/BeachStones");


    Entity* Sinbad = mScnMgr->createEntity("Sinbad.mesh");
    Sinbad->setCastShadows(true);
    SceneNode* SinbadNode = mScnMgr->createSceneNode("SinbadNode");
    SinbadNode->attachObject(Sinbad);
    mScnMgr->getRootSceneNode()->addChild(SinbadNode);
    SinbadNode->setScale(3.0f, 3.0f, 3.0f);
    SinbadNode->setPosition(0, 4.0, 0);

    //mScnMgr->setSkyBox(true, "Examples/SpaceSkyBox");

    //The third parameter is the distance between the Camera and the SkyBox.Make this change to your call :
    //the fourth parameter sets whether or not to render the SkyBox before the rest of the scene. 
    //If the SkyBox is rendered first, then no matter how close it is the rest of your scene objects will be rendered on top of it.
    //The SkyBox is being rendered only 300 pixels away from the Camera 
    //and it is no longer being rendered before everything else.This means the SkyBox is drawn 
    //over terrain that is farther than 300 units away from the Camera.
    mScnMgr->setSkyBox(true, "Examples/SpaceSkyBox", 300, false);

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
    case 'f':
        translate = Ogre::Vector3(0, 0, -10);
        break;
    case 'b':
        translate = Ogre::Vector3(0, 0, 10);
        break;
    case 'x':
        mScnMgr->setSkyBox(false, ""); //This disables the SkyBox.
        break;
    case 'y':
        mScnMgr->setSkyBox(true, "Examples/SpaceSkyBox");
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
