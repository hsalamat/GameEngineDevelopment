//Week4-12-Material8Demo.cpp
//We are only seeing a part of the texture because our quad only has a texture coordinate
//that is going up to 0.2; this means four - fifths of the texture isn't rendered onto our quad.
//Hooman Salamat

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

class OgreTutorial
    : public ApplicationContext
    , public InputListener
{
private:
    SceneManager* scnMgr;
    Root* root;
public:
    OgreTutorial();
    virtual ~OgreTutorial() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    Ogre::SceneNode* TriangleNode;
};


OgreTutorial::OgreTutorial()
    : ApplicationContext("week4-11-Material5Demo")
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

void OgreTutorial::createScene()
{

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = scnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = scnMgr->createSceneNode("LightNode");
    //lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);


    scnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]



    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]



    Ogre::ManualObject* ManualObject = NULL;
    ManualObject = scnMgr->createManualObject("Quad");
    ManualObject->setDynamic(false);
    //Change the material name in the application from BaseWhiteNoLighting to MyMaterial1 :
    ManualObject->begin("MyMaterial8", RenderOperation::OT_TRIANGLE_LIST);


    //ManualObject->position(5.0, 0.0, 0.0);
    //ManualObject->textureCoord(0, 1);

    //ManualObject->position(-5.0, 10.0, 0.0);
    //ManualObject->textureCoord(1, 0);

    //ManualObject->position(-5.0, 0.0, 0.0);
    //ManualObject->textureCoord(1, 1);

    //ManualObject->position(5.0, 10.0, 0.0);
    //ManualObject->textureCoord(0, 0);

    ManualObject->position(5.0, 0.0, 0.0);
    ManualObject->textureCoord(0, 0.2);
    ManualObject->position(-5.0, 10.0, 0.0);
    ManualObject->textureCoord(0.2, 0);
    ManualObject->position(-5.0, 0.0, 0.0);
    ManualObject->textureCoord(0.2, 0.2);
    ManualObject->position(5.0, 10.0, 0.0);
    ManualObject->textureCoord(0, 0);


    ManualObject->index(0);
    ManualObject->index(1);
    ManualObject->index(2);
    ManualObject->index(0);
    ManualObject->index(3);
    ManualObject->index(1);

    ManualObject->end();

    ManualObject->convertToMesh("Quad");

    Ogre::Entity* ent = scnMgr->createEntity("Quad");
    TriangleNode = scnMgr->getRootSceneNode()->createChildSceneNode("TriangleNode");
    TriangleNode->attachObject(ent);

    // -- tutorial section end --
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
    camNode->setPosition(0, 0, 25);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_LOCAL);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    //! [camera]
}

bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
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

void OgreTutorial::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(TriangleNode);
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

//! [fullsource]









	
