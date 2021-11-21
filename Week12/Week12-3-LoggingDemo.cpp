/** @file Week12-3-LoggingDemo
 *  @brief Logging Demo: to mirror all debug output to one or more log files 
 *  @note this program create a custom log called mylog.log under the project folder (logginDebuggingProject)
 *  Ogre provides diagnostic and exception logging facilities using its log management classes. 
 *  This is useful for obtaining details about a crash on a client machine without having to ask users technical details about their setup. 
 *  The log output that Ogre generates contains all events and system initialization, state, and capabilities information from each run of the Ogre-based program.
    Log* Ogre::LogManager::createLog	(	const String & 	name,
                                        bool 	defaultLog = false,
                                        bool 	debuggerOutput = true,
                                        bool 	suppressFileOutput = false 
                                    )	
                                    Parameters
    name:	The name to give the log e.g. 'Ogre.log'
    defaultLog:	If true, this is the default log output will be sent to if the generic logging methods on this class are used. The first log created is always the default log unless this parameter is set.
    debuggerOutput:	If true, output to this log will also be routed to the debugger's output window.
    suppressFileOutput:	If true, this is a logical rather than a physical log and no file output will be written. If you do this you should register a LogListener so log output is not lost.

 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreLogManager.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class Game
    : public ApplicationContext
    , public InputListener
{
public:
    Game();
    virtual ~Game() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};


Game::Game()
    : ApplicationContext("Week12-3-LoggingDemo")
{
}


void Game::setup()
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

    //!Logging
    Ogre::LogManager::getSingletonPtr()->getDefaultLog()->setDebugOutputEnabled(true);
    Log* log = LogManager::getSingleton().createLog("mylog.log", true, true, false);
    //  void logMessage(  const String& message, LogMessageLevel lml, bool maskDebug = false)
    log->logMessage("this is my log", LML_NORMAL , false);
    ///

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

    //! [entity1]
    Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");
    //! [entity1]

    //! [entity1node]
    SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //! [entity1node]

    //! [entity1nodeattach]
    ogreNode->attachObject(ogreEntity);
    //! [entity1nodeattach]

    //! [cameramove]
    camNode->setPosition(0, 47, 222);
    //! [cameramove]

    //! [entity2]
    Entity* ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");
    SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
    ogreNode2->attachObject(ogreEntity2);
    //! [entity2]

    //! [entity3]
    Entity* ogreEntity3 = scnMgr->createEntity("ogrehead.mesh");
    SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode3->setPosition(0, 104, 0);
    ogreNode3->setScale(2, 1.2, 1);
    ogreNode3->attachObject(ogreEntity3);
    //! [entity3]

    //! [entity4]
    Entity* ogreEntity4 = scnMgr->createEntity("ogrehead.mesh");
    SceneNode* ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode4->setPosition(-84, 48, 0);
    ogreNode4->roll(Degree(-90));
    ogreNode4->attachObject(ogreEntity4);
    //! [entity4]

    // -- tutorial section end --
}


bool Game::keyPressed(const KeyboardEvent& evt)
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
