/** @file Week7-13-splitScreenDemo2
 *  @brief Create 4 viewports
 *  @attention: Run with OpenGL 3+ 
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
        const Ogre::Real Radius = 1.0;
        Ogre::Real x = Radius * Ogre::Math::Cos(m_Angle);
        Ogre::Real y = Radius * Ogre::Math::Sin(m_Angle);
        m_Angle += 0.01;
        //_node->setPosition(x, y, 0);
        //_node->translate(translate * evt.timeSinceLastFrame);
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
    Camera* mCamera;
    SceneNode* mCamNode;
    Ogre::Camera* mCamera2;
    SceneNode* mCamNode2;
    Ogre::Camera* mCamera3;
    SceneNode* mCamNode3;
    Ogre::Camera* mCamera4;
    SceneNode* mCamNode4;
public:
    Game();
    ~Game();

    void setup();
    void createScene();
    void createCamera();
    void createViewports();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    Ogre::SceneNode* SinbadNode;
};


Game::Game()
    : ApplicationContext("Week7-13-splitScreenDemo2")
{

}

Game::~Game()
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
    createCamera();
    createViewports();
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



    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();
    mCamera = mScnMgr->createCamera("myCam1");
    mCamera->setNearClipDistance(5); 
    mCamera->setAutoAspectRatio(true);
    mCamNode->attachObject(mCamera);
    mCamNode->setPosition(0, 10, 20);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);


    mCamNode2 = mScnMgr->getRootSceneNode()->createChildSceneNode();
    mCamera2 = mScnMgr->createCamera("myCam2");
    mCamera2->setNearClipDistance(5); 
    mCamera2->setAutoAspectRatio(true);
    mCamNode2->attachObject(mCamera2);
    mCamNode2->setPosition(0, 10, -20);
    mCamNode2->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    mCamNode3 = mScnMgr->getRootSceneNode()->createChildSceneNode();
    mCamera3 = mScnMgr->createCamera("myCam3");
    mCamera3->setNearClipDistance(5);
    mCamera3->setAutoAspectRatio(true);
    mCamNode3->attachObject(mCamera3);
    mCamNode3->setPosition(-20, 10, 0);
    mCamNode3->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    mCamNode4 = mScnMgr->getRootSceneNode()->createChildSceneNode();
    mCamera4 = mScnMgr->createCamera("myCam4");
    mCamera4->setNearClipDistance(5);
    mCamera4->setAutoAspectRatio(true);
    mCamNode4->attachObject(mCamera4);
    mCamNode4->setPosition(20, 10, 0);
    mCamNode4->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
}

void Game::createViewports()
{
    Ogre::Viewport* vp = getRenderWindow()->addViewport(mCamera, 0, 0.0, 0.0, 0.5, 0.5);
    vp->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    Ogre::Viewport* vp2 = getRenderWindow()->addViewport(mCamera2, 1, 0.5, 0.0, 0.5, 0.5);
    vp2->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    Ogre::Viewport* vp3 = getRenderWindow()->addViewport(mCamera3, 2, 0.0, 0.5, 0.5, 0.5);
    vp3->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    Ogre::Viewport* vp4 = getRenderWindow()->addViewport(mCamera4, 3, 0.5, 0.5, 0.5, 0.5);
    vp4->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    mCamera2->setAspectRatio(Real(vp2->getActualWidth()) / Real(vp2->getActualHeight()));
    mCamera3->setAspectRatio(Real(vp2->getActualWidth()) / Real(vp3->getActualHeight()));
    mCamera4->setAspectRatio(Real(vp2->getActualWidth()) / Real(vp4->getActualHeight()));

}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case SDLK_UP:
        break;
    case SDLK_DOWN:
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










