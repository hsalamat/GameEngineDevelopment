/** @file Week6-9-ShaderDemo4.cpp
 *  @brief Using NVIDIA cg - Textures
 *
 *  @attention For cg, you will have to use the GL rendering (Do not use GL3+ or DirectX11)
 * Step 1: we just added a texture unit with the rock texture, nothing fancy.
 * Step 2: we added a float2 for saving the texture coordinates; also we are using sampler2D for the first time.
 * sampler2D is just the name for a two - dimensional texture lookup function, and because
 * it doesn't change per fragment and comes from outside the CG program, we declared it uniform.
 * Step 3: we used the tex2D function, which takes a sampler2D and float2 as the
 * input parameterand returns a color as float4.This function uses the float2 as the
 * position to retrieve a color from the sampler2D objectand returns this color.Basically, it's
 * just a lookup in the texture for the given coordinates.
 * Step 4: we added two texture coordinates to the vertex shader�one as incoming and one as outgoing.
 * Step 5: assigned the incoming to the outgoing parameter.The magic happens in the render pipeline.
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
    SceneManager* scnMgr;
    Root* root;
public:
    Game();
    virtual ~Game() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    Ogre::SceneNode* TriangleNode;
};


Game::Game()
    : ApplicationContext("Week6-10-ShaderDemo5")
{
}


void Game::setup()
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

void Game::createScene()
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



    Ogre::ManualObject* manual = NULL;
    manual = scnMgr->createManualObject("Quad");
    manual->setDynamic(false);
    //Change the material name in the application from BaseWhiteNoLighting to remove material
    manual->begin("MyMaterial14", RenderOperation::OT_TRIANGLE_LIST);

    manual->position(5.0, 0.0, 0.0);
    manual->textureCoord(0.0, 1.0);
    manual->position(-5.0, 10.0, 0.0);
    manual->textureCoord(1.0, 0.0);
    manual->position(-5.0, 0.0, 0.0);
    manual->textureCoord(1.0, 1.0);
    manual->position(5.0, 10.0, 0.0);
    manual->textureCoord(0.0, 0.0);

    manual->index(0);
    manual->index(1);
    manual->index(2);

    manual->index(0);
    manual->index(3);
    manual->index(1);


    manual->end();

    manual->convertToMesh("Quad");

    Ogre::Entity* ent = scnMgr->createEntity("Quad");

    TriangleNode = scnMgr->getRootSceneNode()->createChildSceneNode("TriangleNode");
    TriangleNode->attachObject(ent);


    // -- tutorial section end --
}

void Game::createCamera()
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

bool Game::keyPressed(const KeyboardEvent& evt)
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

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(TriangleNode);
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










