//Week3-4-AddMovingToScene
//Adding Moving To Scene
//Now change the render mode to wireframe modus :
//cam->setPolygonMode(Ogre::PM_WIREFRAME);
//Hooman Salamat

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;


class OgreTutorial
    : public ApplicationContext
    , public InputListener
{
public:
    OgreTutorial();
    virtual ~OgreTutorial() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    bool frameStarted(const FrameEvent& evt);
    //bool frameEnded(const FrameEvent& evt);
    //bool frameRenderingQueued(const FrameEvent& evt);

    SceneNode* SinbadNode;
    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;

};

bool OgreTutorial::frameStarted(const FrameEvent& evt) {
    std::cout << "Frame Started" << std::endl;
    SinbadNode->translate(Ogre::Vector3(0.1, 0, 0));
    return true;
}


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
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();


    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --

    Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
    scnMgr->getRootSceneNode()->addChild(node);

    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
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
    lightNode->setScale(0.1f, 0.1f, 0.1f);
    
    //! [newlight]



    //! [lightpos]
    lightNode->setPosition(0, 70, 4);
    //! [lightpos]

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

    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "My Game Engine", 350);

    // -- tutorial section end --
}


bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
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
