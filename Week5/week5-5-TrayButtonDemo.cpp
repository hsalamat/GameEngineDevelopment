/** @file Week5-5-TrayButtonDemo.cpp
 *  @brief Using Tray Manager with Button Demo
 *
 *  Try adding a button to the top-left tray
 * 
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
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
    OgreBites::TrayListener myTrayListener;
};


BasicTutorial1::BasicTutorial1()
    : ApplicationContext("Week4-3-Tray")
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

    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]


    //! [cameramove]
    camNode->setPosition(0, 47, 222);
    //! [cameramove]

    //! [entity2]
    //Entity* ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");
    //SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
    //ogreNode2->attachObject(ogreEntity2);
    //! [entity2]

    //! [entity3]
    //Entity* ogreEntity3 = scnMgr->createEntity("ogrehead.mesh");
    //SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
    //ogreNode3->setPosition(0, 104, 0);
    //ogreNode3->setScale(2, 1.2, 1);
    //ogreNode3->attachObject(ogreEntity3);
    //! [entity3]

    //! [entity4]
    //Entity* ogreEntity4 = scnMgr->createEntity("ogrehead.mesh");
    //SceneNode* ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();
    //ogreNode4->setPosition(-84, 48, 0);
    //ogreNode4->roll(Degree(-90));
    //ogreNode4->attachObject(ogreEntity4);
    //! [entity4]

    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);
    
    //You're now free to create widgets! Try adding a button to the top-left tray:
     Button * b = mTrayMgr->createButton(TL_TOPLEFT, "MyButton", "Click Me!");

     //mTrayMgr->showOkDialog("Error", "Failed to load mesh!");
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
