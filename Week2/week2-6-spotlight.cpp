/*-------------------------------------------------------------------------
You should see the shadowy blue figure of a ninja.

Ogre provides three types of lighting.

Ogre::Light::LT_POINT - This Light speads out equally in all directions from a point.
Ogre::Light::LT_SPOTLIGHT - This Light works like a flashlight. It produces a solid cylinder of light that is brighter at the center and fades off.
Ogre::Light::LT_DIRECTIONAL - This Light simulates a huge source that is very far away - like daylight. Light hits the entire scene at the same angle everywhere.

The Ogre::Light class has a wide range of properties. Two of the most important are the diffuse and specular color.
-------------------------------------------------------------------------*/

//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class BasicTutorial1
    : public ApplicationContext
    , public InputListener
{
public:
    BasicTutorial1();
    virtual ~BasicTutorial1() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};


BasicTutorial1::BasicTutorial1()
    : ApplicationContext("SpotLight")
{
}


void BasicTutorial1::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //Let's turn off the ambient light so we can see the full effect of our lights. 
    scnMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0));
    //whenever we create an Entity, we call Ogre::Entity::setCastShadows to choose which ones will cast shadows.
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
    //! [turnlights]

    //! [newlight]
    Light* spotLight = scnMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(1, 1, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Light::LT_SPOTLIGHT);
    SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    spotLightNode->attachObject(spotLight);
    //! [newlight]

    //! [lightpos]
    spotLightNode->setDirection(-1, -1, 0);
    spotLightNode->setPosition(Vector3(250, 250, 0));
    //Finally, we set what is called the spotlight range.These are the angles that determine where the light fades from bright in the middle to dimmer on the outside edges.
    spotLight->setSpotlightRange(Degree(35), Degree(50));
    //! [lightpos]



    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
 
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(200, 300, 400);
    camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);

    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    //let's set the background color of the Viewport.
    vp->setBackgroundColour(ColourValue(0, 0, 0));
    //! [camera]



    Entity* ninjaEntity = scnMgr->createEntity("ninja.mesh");
    //This setting simply allows you to turn on/off shadows for a given object.
    ninjaEntity->setCastShadows(true);
    SceneNode* ninjaNode1 = scnMgr->getRootSceneNode()->createChildSceneNode();
    ninjaNode1->setPosition(0, -0, 0);
    ninjaNode1->setScale(0.4, 0.4, 0.4);
    ninjaNode1->yaw(Degree(180));
    ninjaNode1->attachObject(ninjaEntity);


    //The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Plane plane(Vector3::UNIT_Y, 0);
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
    groundEntity->setMaterialName("Examples/Rockwall");

    // -- tutorial section end --
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char** argv)
{
    try
    {
        BasicTutorial1 app;
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
