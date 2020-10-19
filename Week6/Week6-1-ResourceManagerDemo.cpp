//Week6-1-ResourceManagerDemo
//The term level is normally used to describe the interiors of building, dungeons or industrial complexes in which many games take place.Levels are different from exteriors in that they typically consist of regular geometry(hallways, staircases, etc.) rather than terrain.Level design tools typically allow the definition of the level's geometry as well as the placement of entities (furniture, monsters, etc.) and light sources.
//While levels can be displayed in any scene manager, Ogre provides the BSP scene manager which employs BSP cullingand collision management to render levels efficiently.This scene manager is no longer subject to legal restrictions since the release of GTKRadiantand q3map2 under the GNU GPL by id Software.
//BSP levels are generated from Quake .map files, created via a map editor.
//Hooman Salamat

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "ConsoleColor.h"
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
        _movementspeed = 20.0f;
        _mousespeed = 0.002f;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {

        float rotXNew = rotX * evt.timeSinceLastFrame * -1;
        float rotYNew = rotY * evt.timeSinceLastFrame * -1;


        //_camNode->yaw(Ogre::Radian(rotXNew));
        //_camNode->pitch(Ogre::Radian(rotYNew));
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
    : ApplicationContext("Week6-1-Demo")
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


    //locate a resource

    String mArchive;
    String mMap;

    //This is the group which should be used by SceneManagers implementing world geometry 
    //when looking for their resources. Defaults to the DEFAULT_RESOURCE_GROUP_NAME but this can be altered
    // Pick a new resource group so Q3Shader parser is correctly registered
    ResourceGroupManager::getSingleton().setWorldResourceGroupName("BSPWorld");

    // load the Quake archive location and map name from a config file
    ConfigFile cf;
    cf.load(mFSLayer->getConfigFilePath("quakemap.cfg"));
    mArchive = cf.getSetting("Archive");
    mMap = cf.getSetting("Map");

    mArchive = FileSystemLayer::resolveBundlePath(mArchive);

    // add the Quake archive to the world resource group
    ResourceGroupManager::getSingleton().addResourceLocation(mArchive, "Zip",
        ResourceGroupManager::getSingleton().getWorldResourceGroupName(), true);

    //load a resource
    // associate the world geometry with the world resource group, and then load the group
    ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
    rgm.linkWorldGeometryToResourceGroup(rgm.getWorldResourceGroupName(), mMap, mScnMgr);

    //The function 'initialiseResourceGroup' parses scripts if any material in the locations.
    rgm.initialiseResourceGroup(rgm.getWorldResourceGroupName());
    //Files that can be loaded are loaded
    //rgm.loadResourceGroup(rgm.getWorldResourceGroupName(), false);

    mScnMgr = mRoot->createSceneManager("BspSceneManager");
    mScnMgr->setWorldGeometry("maps/chiropteradm.bsp");

    std::cout << green << mScnMgr->getTypeName() << "::" << mScnMgr->getName() << white << std::endl;

    //Ogre::MaterialPtr lMaterial = MaterialManager.create("M_NoLighting", rgm.getWorldResourceGroupName());// this creation is not perfect (as you will see in a later tutorial about manualresourceloader).The created material has already 1 technique and 1 pass.
    //Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0); Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0); No lighting is allowed on this pass. (defaut is 'lighting enabled')
    //lFirstPass->setLightingEnabled(false);


    // -- tutorial section end --
}

void Game::createCamera()
{
    //! [camera]
    camNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    cam = mScnMgr->createCamera("myCam");
    cam->setNearClipDistance(4); // specific to this sample
    cam->setFarClipDistance(4000);
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    //camNode->setPosition(0, 100, 200);
    //camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);


    // set a random player starting point
    ViewPoint vp = mScnMgr->getSuggestedViewpoint(true);

    // Quake uses the Z axis as the up axis, so make necessary adjustments
    camNode->setFixedYawAxis(true, Vector3::UNIT_Z);
    camNode->pitch(Degree(120));
    //camNode->roll(Degree(-30));
    camNode->yaw(Degree(-140));

    camNode->setPosition(vp.position);
    camNode->rotate(vp.orientation);

    //mCameraMan->setTopSpeed(350);   // make the camera move a bit faster



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
