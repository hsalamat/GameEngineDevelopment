/** @file CreateParticleSystemDemo
 *  @brief we have created MySmoke1 particle system (MyParticles.particle under media/particle folder)
    particle_system MySmoke1
    {
        material        	Examples/Smoke
        particle_width  	10
        particle_height 	10
        quota           	500  --> We want a maximum of 500 particles at the same time
        billboard_type  	point --> each particle should be a point that always faces the camera

        emitter Point
        {
            emission_rate 3  --> emits the particles from a single point at a rate of 3 particles per second
            direction 1 0 0  --> emitted in the direction (1,0,0)
            velocity 20  --> 20 units per second
        }
    }
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
    : ApplicationContext("Wee11-2-CreateParticleSystemDemo")
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

    Ogre::ParticleSystem* partSystem = mScnMgr->createParticleSystem("Smoke", "MySmoke1");

    SinbadNode->attachObject(partSystem);


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
    camNode->setPosition(0, 0, 25);
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









