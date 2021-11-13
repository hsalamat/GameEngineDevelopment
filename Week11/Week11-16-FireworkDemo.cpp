/** @file FireworkDemo
 *  @brief we have created Firework particle system (MyParticles.particle under media/particle folder)
    1. Create a particle system that bursts different-colored particles in all directions
    at a steady interval:
    particle_system Firework
    {
    material Examples/Smoke
    particle_width 10
    particle_height 10
    quota 5000
    billboard_type point
    emitter Point
    {
    emission_rate 100
    direction 0 1 0
    velocity 50
    angle 360
    duration 0.1
    repeat_delay 1
    color_range_start 0 0 0
    color_range_end 1 1 1
    }
    }
    2. Create five instances of this particle system:
    Ogre::ParticleSystem* partSystem1 = _sceneManager->createParticleS
    ystem("Firework1","Firework");
    Ogre::ParticleSystem* partSystem2 = _sceneManager->createParticleS
    ystem("Firework2","Firework");
    Ogre::ParticleSystem* partSystem3 = _sceneManager->createParticleS
    ystem("Firework3","Firework");
    Ogre::ParticleSystem* partSystem4 = _sceneManager->createParticleS
    ystem("Firework4","Firework");
    Ogre::ParticleSystem* partSystem5 = _sceneManager->createParticleS
    ystem("Firework5","Firework");
    3. Then five nodes at different positions in the sky:
    Ogre::SceneNode* node1 = _sceneManager->getRootSceneNode()->create
    ChildSceneNode(Ogre::Vector3(0,10,0));
    Ogre::SceneNode* node2 = _sceneManager->getRootSceneNode()->create
    ChildSceneNode(Ogre::Vector3(10,11,0));
    Ogre::SceneNode* node3 = _sceneManager->getRootSceneNode()->create
    ChildSceneNode(Ogre::Vector3(20,9,0));
    Ogre::SceneNode* node4 = _sceneManager->getRootSceneNode()->create
    ChildSceneNode(Ogre::Vector3(-10,11,0));
    Ogre::SceneNode* node5 = _sceneManager->getRootSceneNode()->create
    ChildSceneNode(Ogre::Vector3(-20,19,0));
    4. Finally, attach the particle systems to their nodes:
    node1->attachObject(partSystem1);
    node2->attachObject(partSystem2);
    node3->attachObject(partSystem3);
    node4->attachObject(partSystem4);
    node5->attachObject(partSystem5);
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

Ogre::Real m_Angle = 0.0;
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
        _node->translate(translate * evt.timeSinceLastFrame);
        translate = Ogre::Vector3(0, 0, 0);
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
public:
    Game();
    virtual ~Game() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    Ogre::SceneNode* SinbadNode;
};


Game::Game()
    : ApplicationContext("Week9-1-OurFirstParticleSystemDemo")
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
    createScene();
    createCamera();
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

    //Ogre::ParticleSystem* partSystem = mScnMgr->createParticleSystem("Smoke", "Firework");

    //SinbadNode->attachObject(partSystem);

    Ogre::ParticleSystem* partSystem1 = mScnMgr->createParticleSystem("Firework1", "Firework");
    Ogre::ParticleSystem* partSystem2 = mScnMgr->createParticleSystem("Firework2", "Firework");
    Ogre::ParticleSystem* partSystem3 = mScnMgr->createParticleSystem("Firework3", "Firework");
    Ogre::ParticleSystem* partSystem4 = mScnMgr->createParticleSystem("Firework4", "Firework");
    Ogre::ParticleSystem* partSystem5 = mScnMgr->createParticleSystem("Firework5", "Firework");

    Ogre::SceneNode* node1 = mScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 10, 0));
    Ogre::SceneNode* node2 = mScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(10, 11, 0));
    Ogre::SceneNode* node3 = mScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(20, 9, 0));
    Ogre::SceneNode* node4 = mScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-10, 11, 0));
    Ogre::SceneNode* node5 = mScnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-20, 19, 0));

    node1->attachObject(partSystem1);
    node2->attachObject(partSystem2);
    node3->attachObject(partSystem3);
    node4->attachObject(partSystem4);
    node5->attachObject(partSystem5);
    // -- tutorial section end --
}

void Game::createCamera()
{

    //! [camera]
    SceneNode* camNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = mScnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 20, 100);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_LOCAL);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    //! [camera]
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
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










