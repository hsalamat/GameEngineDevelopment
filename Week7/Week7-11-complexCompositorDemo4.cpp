/** @file Week7-11-complexCompositorDemo4
 *  @brief Changing the number of pixels while running the application
 *  @attention: Run with OpenGL 3+ 
 *  We can already change the number of pixels in the application code; let's go one step
 *  further and make it possible to change the number of pixels using user input.
 *  @attention we didn't really use framelistener, 
 *  but we left the code as if you could have even sued frame listener to change the number of pixels 
 *  @note Use up and down arrows to increase and decrease the number of pixels
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


class CompositorListener1 : public Ogre::CompositorInstance::Listener
{
private:
    float number;

public:

    /// <summary>
    /// It needs a private variable to store the number of pixels that we want our scene to have
    /// </summary>
    CompositorListener1()
    {

        number = 125.0f;
    }

    /// <summary>
    /// use the number variable instead of a fixed value to set the number of pixels :
    /// </summary>
    /// <param name="pass_id"></param>
    /// <param name="mat"></param>
    /// @attention: notifyMaterialSetup gets called
    /// only after the material has been created, but notifyMaterialRender gets called each
    /// time the material is going to be rendered.Because we want to be able to change the number
    /// of pixels during runtime, we need to adjust the number of pixels before each draw call.
    void notifyMaterialRender(uint32 pass_id, MaterialPtr& mat)
    {
        mat->getBestTechnique()->getPass(pass_id)->getFragmentProgramParameters()->setNamedConstant("numpixels", number);
    }

    void setNumber(float num)
    {
        number = num;
    }

    float getNumber()
    {
        return number;
    }
};

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _node;
    CompositorListener1* _listener;
public:

    ExampleFrameListener(Ogre::SceneNode* node, CompositorListener1* listener)
    {
        _node = node;
        _listener = listener;
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
        /// <summary>
        /// you could change the number of pixels here as well based on some AI
        /// </summary>

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
/// We need a private variable to store the compListener instance later on
/// </summary>
    CompositorListener1* compListener;
public:
    Game();
    ~Game();

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    Ogre::SceneNode* SinbadNode;
};


Game::Game()
    : ApplicationContext("Week7-11-complexCompositorDemo4")
{
    /// <summary>
    /// When the application is created, we want the compListener pointer to be NULL
    /// </summary>
    compListener = NULL;  
}

Game::~Game()
{
    /// <summary>
    /// What we create, we also need to destroy. Add a destructor to the application,
    //  which destroys the listener instance :
    /// </summary>
    delete compListener;
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

    //Let's add our compositor to our scene
    Ogre::CompositorManager::getSingleton().addCompositor(mCamera->getViewport(), "Compositor8");
    Ogre::CompositorManager::getSingleton().setCompositorEnabled(mCamera->getViewport(), "Compositor8", true);

    //get the compositor instance 
    Ogre::CompositorInstance* comp = Ogre::CompositorManager::getSingleton().getCompositorChain(mCamera->getViewport())->getCompositor("Compositor8");
    //Now create the listener and add it to the compositor instance :
    compListener = new CompositorListener1();
    comp->addListener(compListener);


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
    getRenderWindow()->addViewport(mCamera);

    //! [camera]
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case SDLK_UP:
    {
        float num = compListener->getNumber();
        num++;
        compListener->setNumber(num);

        std::cout << num << std::endl;
    }
        break;
    case SDLK_DOWN:
    {
        float num = compListener->getNumber();
        num--;
        compListener->setNumber(num);

        std::cout << num << std::endl;
    }
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
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, compListener);
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










