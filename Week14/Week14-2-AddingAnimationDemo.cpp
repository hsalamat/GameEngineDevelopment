/** @file Week14-2-AddingAnimationDemo
 *  @brief Adding animation to our Camera Movement Demo
 *  we add two new member variables in Frame Listener for animating the model. The first member variable
 *  was simply a pointer to the entity we want to animate. The second was a pointer to
 *  Ogre::AnimationState, which is used by Ogre 3D for representing a single animation and
 *  its associated information. Each entity stores all the animations it has and 
 *  we can query them using a string identifier and getAnimationState().
 *  @note WASD to move the camera, P to stop, space bar to see in th wireframe
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

    //! step1
    //! For our animation, we need to add new member variables in the FrameListener.
    //! Add a pointer holding the entity we want to animate and a pointer to the used animation state :
    Ogre::Entity* _ent;
    Ogre::AnimationState* _aniState;

public:

    //! step2
    //! Then change the constructor of the FrameListener to get the entity pointer as a new parameter :
    ExampleFrameListener(Ogre::SceneNode* sceneNode, Ogre::Entity* ent, Ogre::SceneNode* camNode)
    {
        _sceneNode = sceneNode;
        _camNode = camNode;
        _movementspeed = 2.0f;
        _mousespeed = 0.002f;

        //! step3
        //! retrieve the animation state called Dance from the entity 
        //! and store it in the member variable we created for this purpose.
        //! Finally, set the animation to be enabled and loop it :
        _ent = ent;
        //!getAnimationState returns a pointer to this animation represented as an AnimationState or if the
        //animation doesn't exist, it will return a null pointer.
        _aniState = _ent->getAnimationState("Dance");
        _aniState->setEnabled(true);
        //play again and again
        _aniState->setLoop(true);
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {

        float rotXNew = rotX * evt.timeSinceLastFrame * -1;
        float rotYNew = rotY * evt.timeSinceLastFrame * -1;


        //_camNode->yaw(Ogre::Radian(rotXNew * _mousespeed));
        //_camNode->pitch(Ogre::Radian(rotYNew * _mousespeed));
        //_camNode->moveRelative(translate * evt.timeSinceLastFrame * _movementspeed);
        _camNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);

        //! step4
        //! Next, we need to tell the animation how much time has passed since it was last updated
        //! you can multiply 2.0 or 0.5 to the time passed since last frame and the model will be animated faster and slower
        _aniState->addTime(evt.timeSinceLastFrame * 1.0f);
                
        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneNode* mNinjaNode;
    SceneManager* mScnMgr;
    Root* mRoot;
    Ogre::PolygonMode mPolyMode;
    Camera* mCam;
    SceneNode* mCamNode;
    Entity* mNinjaEnt;
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
    : ApplicationContext("Week14-2-AnimationDemo")
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

    //Now we will create a new Entity using this mesh.
    //We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
    Entity* groundEntity = mScnMgr->createEntity("ground");
    mScnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //And finally we need to give our ground a material.
    groundEntity->setMaterialName("Examples/BeachStones");


    mNinjaEnt = mScnMgr->createEntity("Sinbad.mesh");
    mNinjaEnt->setCastShadows(true);
    mNinjaNode = mScnMgr->createSceneNode("SinbadNode");
    mNinjaNode->attachObject(mNinjaEnt);
    mScnMgr->getRootSceneNode()->addChild(mNinjaNode);
    mNinjaNode->setScale(3.0f, 3.0f, 3.0f);
    mNinjaNode->setPosition(0, 4.0, 0);

    // -- tutorial section end --
}

void Game::createCamera()
{
    //! [camera]
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    mCam = mScnMgr->createCamera("myCam");
    mCam->setNearClipDistance(5); // specific to this sample
    mCam->setAutoAspectRatio(true);
    mCamNode->attachObject(mCam);
    mCamNode->setPosition(0, 100, 200);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(mCam);
}


void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(mNinjaNode, mNinjaEnt, mCamNode);
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
         mCam->setPolygonMode(mPolyMode);
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
