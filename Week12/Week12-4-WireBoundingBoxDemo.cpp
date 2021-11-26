/** @file Week12-4-WireBoundingBoxDemo
 *  @brief OgreWireBoundingBox demo
 *  This class builds a wireframe renderable from a given aabb
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <OgreCompositorManager.h>
#include "OgreWireBoundingBox.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;
float _movementspeed;
bool walked = false;
Ogre::Vector3 SinbadTranslate(0, 0, 0);
//we want to move at 50 units per second 
float WalkingSpeed = 10.0f;
float SinbadRotation = 0.0f;

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
        _movementspeed = 200.0f;
        _mousespeed = 0.02f;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        //std::cout << "Frame started" << std::endl;

        //_camNode->yaw(Ogre::Radian(rotX * _mousespeed * evt.timeSinceLastFrame));
        //_camNode->pitch(Ogre::Radian(rotY * _mousespeed * evt.timeSinceLastFrame));
        rotX = 0.0f;
        rotY = 0.0f;

        _sceneNode->translate(SinbadTranslate * evt.timeSinceLastFrame * WalkingSpeed);
        _sceneNode->resetOrientation();
        _sceneNode->yaw(Ogre::Radian(SinbadRotation));

        translate = Ogre::Vector3(0, 0, 0);

        return true;
    }

    bool frameEnded(const Ogre::FrameEvent& evt)
    {

        //std::cout << "Frame ended" << std::endl;
        return true;
    }

    bool frameRenderingQueued(const Ogre::FrameEvent& evt)
    {
       // std::cout << "Frame queued" << std::endl;
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
    Ogre::Viewport* mViewport;
    SceneNode* mCamNode;
    Ogre::PolygonMode mPolyMode;
    bool _keepRunning;
    bool comp1, comp2, comp3;
    bool down1, down2, down3;
public:

    Game();
    virtual ~Game() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    bool mouseMoved(const MouseMotionEvent& e);
    void createFrameListener();
    void renderOneFrame();
    bool keepRunning();
    Ogre::SceneNode* SinbadNode;
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;
};


Game::Game()
    : ApplicationContext("Week10-5")
{
    _keepRunning = true;
    _movementspeed = 50.0f;
    comp1 = false;
    comp2 = false;
    comp3 = false;

    down1 = false;
    down2 = false;
    down3 = false;
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
    createCamera();
    createScene();
    createFrameListener();

    Ogre::CompositorManager::getSingleton().addCompositor(mViewport, "Compositor2");
    Ogre::CompositorManager::getSingleton().addCompositor(mViewport, "Compositor3");
    Ogre::CompositorManager::getSingleton().addCompositor(mViewport, "Compositor7");
}

void Game::createScene()
{

    // -- tutorial section start --
    //! [turnlights]
    mScnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));


    //! [newlight]
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
    lightNode->setPosition(0, 4, 10);



    SinbadNode = mScnMgr->getRootSceneNode()->createChildSceneNode("Node1");
    Ogre::Entity* ent = mScnMgr->createEntity("Entity1", "Sinbad.mesh");
    //ent->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial18"));
    SinbadNode->attachObject(ent);


    //The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Plane plane(Vector3::UNIT_Y, -10);
    //Now we'll ask the MeshManager to create us a mesh using our Plane blueprint. The MeshManager is already keeping track of the resources we loaded when initializing our application. On top of this, it can create new meshes for us.
    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);

    //Now we will create a new Entity using this mesh.
    //We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
    Entity* groundEntity = mScnMgr->createEntity("ground");
    mScnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //And finally we need to give our ground a material.
    groundEntity->setMaterialName("Examples/Rockwall");

    // create a new wire bounding box
    Ogre::WireBoundingBox* wireBoundingBox = new Ogre::WireBoundingBox();

    // get the bounding box from the entity
    const Ogre::AxisAlignedBox& axisAlignedBox = ent->getBoundingBox();

    // set the bounding boxs box to the axis aligned box
    wireBoundingBox->setupBoundingBox(axisAlignedBox);

    // attach the bounding box to the scene node (to an indivudual node)
    SinbadNode->attachObject(wireBoundingBox);

    mScnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);



    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //you must add this in order to add a tray
    mScnMgr->addRenderQueueListener(mOverlaySystem);
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

    mTrayMgr->hideCursor();
    mTrayMgr->showLogo(TL_TOPRIGHT);
    mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
    //mTrayMgr->toggleAdvancedFrameStats();

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "My Game Engine", 350);

    // a friendly reminder
    StringVector names;
    names.push_back("Help");
    mTrayMgr->createParamsPanel(TL_TOPLEFT, "Help", 100, names)->setParamValue(0, "H/F1");


    Ogre::Entity* ballEntity = mScnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
    Ogre::SceneNode* ballNode = mScnMgr->getRootSceneNode()->createChildSceneNode();
    ballNode->setPosition(8, 5, 0);
    ballNode->setScale(0.02f, 0.02f, 0.02f);
    ballNode->attachObject(ballEntity);

    Ogre::Entity* paddleEntity = mScnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);
    Ogre::SceneNode* paddleNode = mScnMgr->getRootSceneNode()->createChildSceneNode();
    paddleNode->setPosition(-8, 5, 0);
    paddleNode->setScale(0.02f, 0.02f, 0.02f);
    paddleNode->attachObject(paddleEntity);

    //mScnMgr->showBoundingBoxes(true);


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
    mViewport = getRenderWindow()->addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
}

bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    rotX = evt.xrel;
    rotY = evt.yrel;
    return true;
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    translate = Ogre::Vector3(0, 0, 0);
    SinbadTranslate = Ogre::Vector3(0, 0, 0);
    walked = false;
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        _keepRunning = false;
        break;
    case SDLK_UP:
        SinbadTranslate += Ogre::Vector3(0, 0, -1);
        SinbadRotation = 3.14f;
        walked = true;
        break;
    case SDLK_DOWN:
        SinbadTranslate += Ogre::Vector3(0, 0, 1);
        SinbadRotation = 0.0f;
        walked = true;
        break;
    case SDLK_LEFT:
        SinbadTranslate += Ogre::Vector3(-1, 0, 0);
        SinbadRotation = -1.57f;
        walked = true;
        break;
    case SDLK_RIGHT:
        SinbadTranslate += Ogre::Vector3(1, 0, 0);
        SinbadRotation = 1.57f;
        walked = true;
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
    case 'p':
        translate = Ogre::Vector3(0, 0, 0);
        break;
    case ' ':
        if (mPolyMode == Ogre::PolygonMode::PM_SOLID)
            mPolyMode = Ogre::PolygonMode::PM_WIREFRAME;
        else
            mPolyMode = Ogre::PolygonMode::PM_SOLID;
        mCamera->setPolygonMode(mPolyMode);
        break;
    case '1':
        down1 = true;
        down2 = false;
        down3 = false;
        comp1 = !comp1;
        Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, "Compositor2", comp1);
        break;
    case '2':
        down2 = true;
        down1 = false;
        down3 = false;
        comp2 = !comp2;
        Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, "Compositor3", comp2);
        break;
    case '3':
        down3 = true;
        down1 = false;
        down2 = false;
        comp3 = !comp3;
        Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, "Compositor7", comp3);
        break;
    default:
        break;
    }
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, mCamNode);
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
















