/*-------------------------------------------------------------------------
Welcome to OGRE Object-Oriented Graphics Rendering Engine
Minimum code

xcopy /y $(ogre_home_v2)\build\bin\debug\*.* $(ProjectDir)x64\debug\
copy /y "C:\Hooman\GBC\GAME3121\Course Materials\GameEngineDevelopment\ogre-sdk-v2.1\build\bin\debug\*.*" "C:\Hooman\GBC\GAME3121\Week1\Week1\$(projectname)\x64\debug\"
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
    : ApplicationContext("OgreTemplate-V2")
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

    //// without light we would just get a black screen    
    //Ogre::Light* light = scnMgr->createLight("MainLight");
    //Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //lightNode->setPosition(0, 10, 15);
    //lightNode->attachObject(light);

    //scnMgr->setAmbientLight(ColourValue(1.0, 0.0, 0.0));

    //// also need to tell where we are
    //Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //camNode->setPosition(0, 0, 15);
    //camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    //// create the camera
    //Ogre::Camera* cam = scnMgr->createCamera("myCam");
    //cam->setNearClipDistance(5); // specific to this sample
    //cam->setAutoAspectRatio(true);
    //camNode->attachObject(cam);

    //// and tell it to render into the main window
    //getRenderWindow()->addViewport(cam);

    //// finally something to render
    //Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    //Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    //node->attachObject(ent);
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
