//Week3-6-FrameIndependentDemo
//Modifying the code to be time based rather than frame based
//Ogre 3D passes a FrameEvent when calling the frameStarted() method.This class holds the time since the last frame was rendered in seconds :
//_node->translate(Ogre::Vector3(10, 0, 0) * evt.timeSinceLastFrame);
//Let's say we render with 10 frames per second; then for each frame, evt.timeSinceLastFrame would be 0.1f
//In each frame we multiply evt.timeSinceLastFrame by the vector (10,0,0), which results in the vector (1,0,0). 
//This result is applied to the scene node of each frame. With 10 frames per second, this will add up to a movement of (10,0,0) per second, which is exactly the value we wanted our model to move by per second. 

//Hooman Salamat


#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;


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
        //_node->translate(Ogre::Vector3(0.1, 0, 0));
        _node->translate(Ogre::Vector3(10, 0, 0) * evt.timeSinceLastFrame);
        return true;
    }
};

class OgreTutorial
    : public ApplicationContext
    , public InputListener
{
private:
    SceneNode* SinbadNode;
    SceneManager* scnMgr;
    Root* root;
public:
    OgreTutorial();
    virtual ~OgreTutorial() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
    void createFrameListener();
};


OgreTutorial::OgreTutorial()
    : ApplicationContext("week3-6-FrameIndependentDemo")
{
}


void OgreTutorial::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    root = getRoot();
    scnMgr = root->createSceneManager();


    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    createScene();
    createCamera();
    createFrameListener();

}


bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}

void OgreTutorial::createScene()
{
    // -- tutorial section start --

    Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
    scnMgr->getRootSceneNode()->addChild(node);

    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
       //! [turnlights]

    //! [newlight]
    //

    Ogre::Light* light = scnMgr->createLight("Light1");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(1, -1, 0));

    // Set Light Color
    light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light->setSpecularColour(1.0f, 1.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    //light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = node->createChildSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light);
    lightNode->setScale(0.01f, 0.01f, 0.01f);

    //! [newlight]
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
    Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //And finally we need to give our ground a material.
    groundEntity->setMaterialName("Examples/BeachStones");


    Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    ent->setCastShadows(true);
    SinbadNode = scnMgr->createSceneNode("Character");
    SinbadNode->attachObject(ent);
    scnMgr->getRootSceneNode()->addChild(SinbadNode);
    SinbadNode->setPosition(Ogre::Vector3(0.0f, 4.0f, 0.0f));
    SinbadNode->setScale(3.0f, 3.0f, 3.0f);
}

void OgreTutorial::createCamera()
{
    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 100, 200);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    //! [camera]


}

void OgreTutorial::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode);
    mRoot->addFrameListener(FrameListener);
}

int main(int argc, char** argv)
{
    try
    {
        OgreTutorial app;
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

