//Render a Cube using a simple material
//you have to run this with GL3+ Renderer
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
        _node->setPosition(x, y, 0);
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
    Ogre::SceneNode* CubeNode;


    OgreTutorial();
    virtual ~OgreTutorial() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    ManualObject* createCubeMesh(Ogre::String name, Ogre::String matName);
};


OgreTutorial::OgreTutorial()
    : ApplicationContext("week4-5-ManualObjectCube")
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
    light1->setType(Ogre::Light::LT_POINT);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = scnMgr->createSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);


    scnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]

    //ManualObject = scnMgr->createManualObject("Triangle");
    //ManualObject->setDynamic(false);

    Ogre::ManualObject* ManualObject = createCubeMesh("Cube", "FlatVertexColour");
    CubeNode = scnMgr->getRootSceneNode()->createChildSceneNode("CubeNode");
    CubeNode->attachObject(ManualObject);

    CubeNode->setScale(2.0, 2.0, 2.0);
    CubeNode->rotate(Ogre::Vector3(0, 1, 1), Radian(45), Node::TS_WORLD);


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
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

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
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(CubeNode);
    mRoot->addFrameListener(FrameListener);
}

ManualObject* OgreTutorial::createCubeMesh(Ogre::String name, Ogre::String matName) {

    ManualObject* cube = new ManualObject(name);
    cube->begin(matName);

    cube->position(0.5, -0.5, 1.0); cube->colour(1, 0, 0); cube->textureCoord(1, 0);   //0
    cube->position(-0.5, -0.5, 0.0); cube->colour(1, 0, 0); cube->textureCoord(0, 1);  //1
    cube->position(0.5, -0.5, 0.0); cube->colour(1, 0, 0); cube->textureCoord(1, 1);    //2
    cube->position(-0.5, -0.5, 1.0); cube->colour(1, 0, 0); cube->textureCoord(0, 0);   //3
    cube->position(0.5, 0.5, 1.0); cube->colour(0, 1, 0); cube->textureCoord(1, 0);       //4
    cube->position(-0.5, -0.5, 1.0); cube->colour(0, 1, 0); cube->textureCoord(0, 1);   //5 
    cube->position(0.5, -0.5, 1.0); cube->colour(0, 1, 0); cube->textureCoord(1, 1);     //6
    cube->position(-0.5, 0.5, 1.0); cube->colour(0, 1, 0); cube->textureCoord(0, 0);     //7
    cube->position(-0.5, 0.5, 0.0); cube->colour(0, 0, 1); cube->textureCoord(0, 1);    //8
    cube->position(-0.5, -0.5, 0.0); cube->colour(0, 0, 1); cube->textureCoord(1, 1);  //9
    cube->position(-0.5, -0.5, 1.0); cube->colour(0, 0, 1); cube->textureCoord(1, 0);    //10
    cube->position(0.5, -0.5, 0.0); cube->colour(0, 1, 1); cube->textureCoord(0, 1);    //11
    cube->position(0.5, 0.5, 0.0); cube->colour(0, 1, 1); cube->textureCoord(1, 1);      //12
    cube->position(0.5, -0.5, 1.0); cube->colour(0, 1, 1); cube->textureCoord(0, 0);    //13
    cube->position(0.5, -0.5, 0.0); cube->colour(1, 1, 0); cube->textureCoord(1, 0);   //14
    cube->position(-0.5, -0.5, 0.0); cube->colour(1, 1, 0); cube->textureCoord(0, 0);   //15
    cube->position(-0.5, 0.5, 1.0); cube->colour(1, 0, 1); cube->textureCoord(1, 0);     //16
    cube->position(0.5, 0.5, 0.0); cube->colour(1, 0, 1); cube->textureCoord(0, 1);    //17
    cube->position(-0.5, 0.5, 0.0); cube->colour(1, 0, 1); cube->textureCoord(1, 1);   //18
    cube->position(0.5, 0.5, 1.0); cube->colour(1, 0, 1); cube->textureCoord(0, 0);      //19

    cube->triangle(0, 1, 2);		cube->triangle(3, 1, 0);
    cube->triangle(4, 5, 6);		cube->triangle(4, 7, 5);
    cube->triangle(8, 9, 10);		cube->triangle(10, 7, 8);
    cube->triangle(4, 11, 12);	cube->triangle(4, 13, 11);
    cube->triangle(14, 8, 12);	cube->triangle(14, 15, 8);
    cube->triangle(16, 17, 18);	cube->triangle(16, 19, 17);
    cube->end();

    return cube;

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










    

