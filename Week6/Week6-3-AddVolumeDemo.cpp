/** @file Week6-3-AddVolumeDemo
 *  @brief Adding volume to the blades of grass
 *
 * We have managed to render some blades of grass, but when moving the camera, it quickly
 * becomes clear that the blades are only a 2D image and don't have any volume themselves.
 * To fix this problem, we simply created two new quads, rotated
 * them, and then stuck them into each other.
 * think of it as a circle divided into six parts.Between two quads, there is an angle of 60 degrees.Three quads
 * intersecting each other at the center means we have six angles of 60 degrees, making a
 * total of 360 degree. How did we calculate the new positions of the points for the other
 * two quads ? It's simple trigonometry. To calculate the y value, we use sines and for the x
 * value, cosines.This technique that we used creates a plane and renders a texture onto it
 * to simulate a more detailed model, this is a wildly used technique in video games called billboarding.

 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

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
        _movementspeed = 2.0f;
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
    : ApplicationContext("Week6-2-ModelDemo")
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
    //lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);

    //! [newlight]



    //! [lightDirection]
    lightNode->setDirection(1, -1, 0);
    //! [lightDirection]


    //The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Plane plane(Vector3::UNIT_Y, -1);
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
    groundEntity->setMaterialName("Examples/GrassFloor");

    //Add the first polygon with the position and texture coordinates for each vertex:
    Ogre::ManualObject* manual = mScnMgr->createManualObject("grass");
    manual->begin("Examples/GrassBlades", RenderOperation::OT_TRIANGLE_LIST);
    //manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);    
    manual->position(5.0, 0.0, 0.0);
    manual->textureCoord(1, 1);
    manual->position(-5.0, 10.0, 0.0);
    manual->textureCoord(0, 0);
    manual->position(-5.0, 0.0, 0.0);
    manual->textureCoord(0, 1);
    //We also need a second triangle to make the quad complete :
    manual->position(5.0, 0.0, 0.0);
    manual->textureCoord(1, 1);
    manual->position(5.0, 10.0, 0.0);
    manual->textureCoord(1, 0);
    manual->position(-5.0, 10.0, 0.0);
    manual->textureCoord(0, 0);

    //step1. After the first two triangles, add the third and fourth triangle for the second quad :
    //third triangle
    manual->position(2.5, 0.0, 4.3);
    manual->textureCoord(1, 1);
    manual->position(-2.5, 10.0, -4.3);
    manual->textureCoord(0, 0);
    manual->position(-2.0, 0.0, -4.3);
    manual->textureCoord(0, 1);
    //fourth triangle
    manual->position(2.5, 0.0, 4.3);
    manual->textureCoord(1, 1);
    manual->position(2.5, 10.0, 4.3);
    manual->textureCoord(1, 0);
    manual->position(-2.5, 10.0, -4.3);
    manual->textureCoord(0, 0);

    //step2. Add the fifth and sixth triangle for the third quad :
    //fifth triangle
    manual->position(2.5, 0.0, -4.3);
    manual->textureCoord(1, 1);
    manual->position(-2.5, 10.0, 4.3);
    manual->textureCoord(0, 0);
    manual->position(-2.0, 0.0, 4.3);
    manual->textureCoord(0, 1);
    //sixth triangle
    manual->position(2.5, 0.0, -4.3);
    manual->textureCoord(1, 1);
    manual->position(2.5, 10.0, -4.3);
    manual->textureCoord(1, 0);
    manual->position(-2.5, 10.0, 4.3);
    manual->textureCoord(0, 0);


    //We have finished defining the quad; let's tell the manual object:
    manual->end();
    //Finally, create a new scene node and attach the manual object to it :
    Ogre::SceneNode* grassNode = mScnMgr->getRootSceneNode()->createChildSceneNode("GrassNode2");
    grassNode->attachObject(manual);

    std::cout << green << mScnMgr->getTypeName() << "::" << mScnMgr->getName() << white << std::endl;

    // -- tutorial section end --
}

void Game::createCamera()
{
    camNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = mScnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

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
