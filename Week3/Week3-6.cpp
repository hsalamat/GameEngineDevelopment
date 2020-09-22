//How to Draw a Simple Triangle
// Rendering operation using vertex buffers
//  OT_POINT_LIST = 1, OT_LINE_LIST = 2, OT_LINE_STRIP = 3, OT_TRIANGLE_LIST = 4,
//  OT_TRIANGLE_STRIP = 5, OT_TRIANGLE_FAN = 6,...

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Real m_Angle = 0.0;

class BasicTutorial1
    : public ApplicationContext
    , public InputListener
{
public:
    BasicTutorial1();
    virtual ~BasicTutorial1() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    bool frameStarted(const FrameEvent& evt);
    bool frameEnded(const FrameEvent& evt);
    bool frameRenderingQueued(const FrameEvent& evt);
    ManualObject* createCubeMesh(Ogre::String name, Ogre::String matName);

    Ogre::SceneNode* CubeNode;
};


BasicTutorial1::BasicTutorial1()
    : ApplicationContext("OgreTemplate-week3-5")
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


    //Ogre::ManualObject* ManualObject = NULL;
    //ManualObject = scnMgr->createManualObject("Triangle");
    //ManualObject->setDynamic(false);
    //ManualObject->begin("BaseWhiteNoLighting",
    //    Ogre::RenderOperation::OT_TRIANGLE_LIST);
    //ManualObject->position(0, 0, 0);
    //ManualObject->position(1, 0, 0);
    //ManualObject->position(1, 1, 0);
    //ManualObject->position(0, 1, 0);
    //ManualObject->triangle(0, 1, 2);
    //ManualObject->end();

    Ogre::ManualObject* ManualObject = createCubeMesh("Cube", "FlatVertexColour");
    CubeNode = scnMgr->getRootSceneNode()->createChildSceneNode("CubeNode");
    CubeNode->attachObject(ManualObject);

    CubeNode->setScale(2.0, 2.0, 2.0);
    CubeNode->rotate(Ogre::Vector3(0, 1, 1), Radian(45), Node::TS_WORLD);

    // -- tutorial section end --
}


//ManualObject* BasicTutorial1::createCubeMesh(Ogre::String name, Ogre::String matName) {
//
//    ManualObject* cube = new ManualObject(name);
//    cube->begin(matName);
//
//    cube->position(0.5, -0.5, 1.0); cube->colour(0.408248, -0.816497, 0.408248); cube->textureCoord(1, 0);
//    cube->position(-0.5, -0.5, 0.0); cube->colour(-0.408248, -0.816497, -0.408248); cube->textureCoord(0, 1);
//    cube->position(0.5, -0.5, 0.0); cube->colour(0.666667, -0.333333, -0.666667); cube->textureCoord(1, 1);
//    cube->position(-0.5, -0.5, 1.0); cube->colour(-0.666667, -0.333333, 0.666667); cube->textureCoord(0, 0);
//    cube->position(0.5, 0.5, 1.0); cube->colour(0.666667, 0.333333, 0.666667); cube->textureCoord(1, 0);
//    cube->position(-0.5, -0.5, 1.0); cube->colour(-0.666667, -0.333333, 0.666667); cube->textureCoord(0, 1);
//    cube->position(0.5, -0.5, 1.0); cube->colour(0.408248, -0.816497, 0.408248); cube->textureCoord(1, 1);
//    cube->position(-0.5, 0.5, 1.0); cube->colour(-0.408248, 0.816497, 0.408248); cube->textureCoord(0, 0);
//    cube->position(-0.5, 0.5, 0.0); cube->colour(-0.666667, 0.333333, -0.666667); cube->textureCoord(0, 1);
//    cube->position(-0.5, -0.5, 0.0); cube->colour(-0.408248, -0.816497, -0.408248); cube->textureCoord(1, 1);
//    cube->position(-0.5, -0.5, 1.0); cube->colour(-0.666667, -0.333333, 0.666667); cube->textureCoord(1, 0);
//    cube->position(0.5, -0.5, 0.0); cube->colour(0.666667, -0.333333, -0.666667); cube->textureCoord(0, 1);
//    cube->position(0.5, 0.5, 0.0); cube->colour(0.408248, 0.816497, -0.408248); cube->textureCoord(1, 1);
//    cube->position(0.5, -0.5, 1.0); cube->colour(0.408248, -0.816497, 0.408248); cube->textureCoord(0, 0);
//    cube->position(0.5, -0.5, 0.0); cube->colour(0.666667, -0.333333, -0.666667); cube->textureCoord(1, 0);
//    cube->position(-0.5, -0.5, 0.0); cube->colour(-0.408248, -0.816497, -0.408248); cube->textureCoord(0, 0);
//    cube->position(-0.5, 0.5, 1.0); cube->colour(-0.408248, 0.816497, 0.408248); cube->textureCoord(1, 0);
//    cube->position(0.5, 0.5, 0.0); cube->colour(0.408248, 0.816497, -0.408248); cube->textureCoord(0, 1);
//    cube->position(-0.5, 0.5, 0.0); cube->colour(-0.666667, 0.333333, -0.666667); cube->textureCoord(1, 1);
//    cube->position(0.5, 0.5, 1.0); cube->colour(0.666667, 0.333333, 0.666667); cube->textureCoord(0, 0);
//
//    cube->triangle(0, 1, 2);		cube->triangle(3, 1, 0);
//    cube->triangle(4, 5, 6);		cube->triangle(4, 7, 5);
//    cube->triangle(8, 9, 10);		cube->triangle(10, 7, 8);
//    cube->triangle(4, 11, 12);	cube->triangle(4, 13, 11);
//    cube->triangle(14, 8, 12);	cube->triangle(14, 15, 8);
//    cube->triangle(16, 17, 18);	cube->triangle(16, 19, 17);
//    cube->end();
//
//    return cube;
//
//}

ManualObject* BasicTutorial1::createCubeMesh(Ogre::String name, Ogre::String matName) {

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



bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }

    return true;
}

bool BasicTutorial1::frameStarted(const FrameEvent& evt) {
    std::cout << "Frame Started" << std::endl;
    return true;
}

//
bool BasicTutorial1::frameEnded(const FrameEvent& evt) {
    std::cout << "Frame Ended" << std::endl;
    return true;
}

//
bool BasicTutorial1::frameRenderingQueued(const FrameEvent& evt) {
    std::cout << "Frame Queued" << std::endl;
   /* const Ogre::Real Radius = 1.0;
    Ogre::Real x = Radius * Ogre::Math::Cos(m_Angle);
    Ogre::Real y = Radius * Ogre::Math::Sin(m_Angle);
    m_Angle += 0.01;
    TriangleNode->setPosition(x, y, 0);*/
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
