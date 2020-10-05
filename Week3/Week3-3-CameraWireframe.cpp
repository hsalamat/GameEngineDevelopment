//Week3-3-CameraWireFrame
//PM_POINTS
//Only the points of each polygon are rendered.

//PM_WIREFRAME
//Polygons are drawn in outline only.

//PM_SOLID
//The normal situation - polygons are filled in.
//Hooman Salamat

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class OgreTutorial
    : public ApplicationContext
    , public InputListener
{
private:
    SceneNode* SinbadNode;
    SceneManager* scnMgr;
    Root* root;
    Ogre::PolygonMode polyMode;
    Camera* cam;
public:
    OgreTutorial();
    virtual ~OgreTutorial() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
};


OgreTutorial::OgreTutorial()
    : ApplicationContext("OgreTemplate-week3-1")
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

    polyMode = Ogre::PolygonMode::PM_SOLID;

    createScene();
    createCamera();
}

void OgreTutorial::createScene()
{
    // -- tutorial section start --

    Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
    scnMgr->getRootSceneNode()->addChild(node);

    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = scnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_POINT);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 1.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    //light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = node->createChildSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);

    //! [newlight]



    //! [lightpos]
    lightNode->setPosition(3, 3, 4);
    //! [lightpos]




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
    groundEntity->setMaterialName("Examples/Rockwall");


    Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    ent->setCastShadows(true);
    SceneNode* entNode = scnMgr->createSceneNode("Character");
    entNode->attachObject(ent);
    scnMgr->getRootSceneNode()->addChild(entNode);
    entNode->setPosition(0, 0, 0);

    // -- tutorial section end --
}

void OgreTutorial::createCamera()
{
//! [camera]
SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

// create the camera
cam = scnMgr->createCamera("myCam");
cam->setNearClipDistance(5); // specific to this sample
cam->setAutoAspectRatio(true);
camNode->attachObject(cam);
camNode->setPosition(0, 3, 15);
camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
//cam->setPolygonMode(Ogre::PM_WIREFRAME);

// and tell it to render into the main window
getRenderWindow()->addViewport(cam);
}

//! [camera]

bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }


    if (evt.keysym.sym == 'r')
    {
        if (polyMode == PM_SOLID)
        {
            polyMode = Ogre::PolygonMode::PM_WIREFRAME;
        }
        else if (polyMode == PM_WIREFRAME)
        {
            polyMode = Ogre::PolygonMode::PM_POINTS;
        }
        else if (polyMode == PM_POINTS)
        {
            polyMode = Ogre::PolygonMode::PM_SOLID;
        }
        cam->setPolygonMode(polyMode);
    }

    return true;
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

//! [fullsource]
