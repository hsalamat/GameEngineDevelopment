/** @file Week7-12-splitScreenDemo
 *  @brief Adding a split screen
 *  @attention: Run with OpenGL 3+ 
 *  We created an application with two viewports; each has a camera that looks at our model
 *  instance from a different direction. Because we want to view our model from different
 *  directions, each viewport needs its own camera. Therefore, we created our first camera,
 *  which was created at position (0,10,20) and looks at (0,0,0). This means this camera looks
 *  along the z-axis, for example, at the front of the model. We also created another camera at (20,10,0),
 *  which looks along the x-axis. We created the first viewport and added the first camera to the
 *  RenderWindow. This was done using the addViewport() function. As the first parameter,
 *  this function takes the camera that will deliver the image to be displayed. The second
 *  number defines which viewport has higher priority, should two viewports overlap. The
 *  viewport with the highest number is rendered if two viewports overlap. The third and fourth
 *  parameters define the beginning point of the viewport and the fifth and sixth parameters
 *  define the height and width. Each is in the range 0 to 1. 
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
    /// <summary>
    /// We need a second camera, so create a pointer to hold it:
    /// </summary>
    Ogre::Camera* mCamera2;
    SceneNode* mCamNode2;
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
    : ApplicationContext("Week7-12-splitScreenDemo")
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


    // Now we need a createCamera() function in which we create a camera that
    // looks at our model at(0, 0, 0) from(0, 10, 20) :
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();
    mCamera = mScnMgr->createCamera("myCam1");
    mCamera->setNearClipDistance(5); 
    mCamera->setAutoAspectRatio(true);
    mCamNode->attachObject(mCamera);
    mCamNode->setPosition(0, 10, 20);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    //Now use the new camera pointer to store another camera, which looks at the
    //same point but now from the position(20, 10, 0) :
    mCamNode2 = mScnMgr->getRootSceneNode()->createChildSceneNode();
    mCamera2 = mScnMgr->createCamera("myCam2");
    mCamera2->setNearClipDistance(5); 
    mCamera2->setAutoAspectRatio(true);
    mCamNode2->attachObject(mCamera2);
    mCamNode2->setPosition(20, 10, 0);
    mCamNode2->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
}

void Game::createViewports()
{
    ///Create a viewport that covers the left half of the render window using the first camera :
    Ogre::Viewport* vp = getRenderWindow()->addViewport(mCamera, 0, 0.0, 0.0, 0.5, 1.0);
    vp->setBackgroundColour(ColourValue(0.0f, 1.0f, 0.0f));

    ///Then create a second viewport that covers the right half of the render window using the second camera :
    Ogre::Viewport* vp2 = getRenderWindow()->addViewport(mCamera2, 1, 0.5, 0.0, 0.5, 1.0);
    vp2->setBackgroundColour(ColourValue(0.0f, 0.0f, 1.0f));

    ///Both cameras need the correct aspect ratio; otherwise the image would look strange :
    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    mCamera2->setAspectRatio(Real(vp2->getActualWidth()) / Real(vp2->getActualHeight()));
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










