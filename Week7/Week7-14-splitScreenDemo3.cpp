/** @file Week7-14-splitScreenDemo3
 *  @brief Create four viewports + compositor
 *  @attention: Run with OpenGL 3+ 
 *  we apply a compositor that multiplies the outgoing color with a float4 as factors,
 *  and with this as the parameter, we will create a scene where we see each color channel on
 *  its own, and then the final picture, which combines them all.
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

/// We have three color channels, so we will need three compositor listeners to
/// change the parameters accordingly.First, add the one for the red color channel.
/// Only set the color factors in the setup of the materialand we don't need them to
/// change during runtime :
class CompositorListener2 : public Ogre::CompositorInstance::Listener
{
public:

    void notifyMaterialSetup(uint32 pass_id, MaterialPtr& mat)
    {
        mat->getBestTechnique()->getPass(pass_id)->getFragmentProgramParameters()->setNamedConstant("factors", Ogre::Vector3(1, 0, 0));
    }
};

class CompositorListener3 : public Ogre::CompositorInstance::Listener
{
public:

    void notifyMaterialSetup(uint32 pass_id, MaterialPtr& mat)
    {
        mat->getBestTechnique()->getPass(pass_id)->getFragmentProgramParameters()->setNamedConstant("factors", Ogre::Vector3(0, 1, 0));
    }
};

class CompositorListener4 : public Ogre::CompositorInstance::Listener
{
public:

    void notifyMaterialSetup(uint32 pass_id, MaterialPtr& mat)
    {
        mat->getBestTechnique()->getPass(pass_id)->getFragmentProgramParameters()->setNamedConstant("factors", Ogre::Vector3(0, 0, 1));
    }
};


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
    Ogre::Viewport* vp;
    Ogre::Viewport* vp2;
    Ogre::Viewport* vp3;
    Ogre::Viewport* vp4;

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
    : ApplicationContext("Week7-14-splitScreenDemo3")
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

    Ogre::CompositorManager::getSingleton().addCompositor(vp, "Compositor9");
    Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp, "Compositor9", true);

    Ogre::CompositorInstance* comp = Ogre::CompositorManager::getSingleton().getCompositorChain(vp)->getCompositor("Compositor9");
    CompositorListener2* compListener = new CompositorListener2();
    comp->addListener(compListener);

    Ogre::CompositorManager::getSingleton().addCompositor(vp2, "Compositor9");
    Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp2, "Compositor9", true);

    Ogre::CompositorInstance* comp2 = Ogre::CompositorManager::getSingleton().getCompositorChain(vp2)->getCompositor("Compositor9");
    CompositorListener3* compListener2 = new CompositorListener3();
    comp2->addListener(compListener2);

    Ogre::CompositorManager::getSingleton().addCompositor(vp3, "Compositor9");
    Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp3, "Compositor9", true);

    Ogre::CompositorInstance* comp3 = Ogre::CompositorManager::getSingleton().getCompositorChain(vp3)->getCompositor("Compositor9");
    CompositorListener4* compListener3 = new CompositorListener4();
    comp3->addListener(compListener3);

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
}

void Game::createViewports()
{
    vp = getRenderWindow()->addViewport(mCamera, 0, 0.0, 0.0, 0.5, 0.5);
    vp->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    vp2 = getRenderWindow()->addViewport(mCamera, 1, 0.5, 0.0, 0.5, 0.5);
    vp2->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    vp3 = getRenderWindow()->addViewport(mCamera, 2, 0.0, 0.5, 0.5, 0.5);
    vp3->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    vp4 = getRenderWindow()->addViewport(mCamera, 3, 0.5, 0.5, 0.5, 0.5);
    vp4->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
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










