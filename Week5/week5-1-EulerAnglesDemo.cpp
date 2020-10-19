/*-------------------------------------------------------------------------
* Euler Angles: Pitch Yaw Roll
Demoing PYR != YPR != RYP
Use arrow keys to translate
Use WSAD keys to rotate
-------------------------------------------------------------------------*/

//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include "OgreOverlayManager.h"
#include "OgreTextAreaOverlayElement.h"
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
	bool frameRenderingQueued(const FrameEvent& evt);
};


BasicTutorial1::BasicTutorial1()
	: ApplicationContext("Week5 Demo")
{
}

Ogre::Real x = 0.0, y = 0.0, z = 200.0;
SceneNode* ogreNode;

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
	Light* light = scnMgr->createLight("MainLight");
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	//! [newlight]

	//! [lightpos]
	lightNode->setPosition(20, 80, 500);
	//! [lightpos]

	//! [camera]
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setFarClipDistance(5000);
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
	ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	//! [entity1node]

	//! [entity1nodeattach]
	ogreNode->attachObject(ogreEntity);
	//! [entity1nodeattach]

	//! [cameramove]
	//camNode->setPosition(0, 47, 222);
	//! [cameramove]

	camNode->setPosition(Ogre::Vector3(0.0, 0.0, 500.0));

	//The x - axis starts with negative values to the left and increases to the right(passing through zero at the origin).
	//The z - axis runs forwards and backwards.The positive direction of the z - axis points "out of the screen".
	//So if a character walks towards the screen, then its z value will be increasing.

	ogreNode->setPosition(x, y, z);


	//Demoing PYR != YPR != RYP

	//ogreNode->pitch(Degree(45));
	//ogreNode->yaw(Degree(90));
	//ogreNode->roll(Degree(45));

	//ogreNode->yaw(Degree(90));
	//ogreNode->pitch(Degree(45));
	//ogreNode->roll(Degree(45));

	//ogreNode->roll(Degree(45));
	//ogreNode->yaw(Degree(90));
	//ogreNode->pitch(Degree(45));

	//To Do:

	//OverlaySystem mOverlaySystem = new Ogre::OverlaySystem("test");
	//scnMgr->addRenderQueueListener(mOverlaySystem);

	
	//Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	//Ogre::TextAreaOverlayElement* textArea =
	//	(Ogre::TextAreaOverlayElement*) om.getOverlayElement("Sample/Panel/Text");
	//textArea->setCaption("Hello Ogre!");

	// -- tutorial section end --
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)

	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case SDLK_UP:
		z -= 10;
		ogreNode->translate(x, y, z);
		break;
	case SDLK_DOWN:
		z += 10;
		ogreNode->translate(x, y, z);
		break;
	case SDLK_LEFT:
		x -= 10;
		ogreNode->translate(x, y, z);
		break;
	case SDLK_RIGHT:
		x += 10;
		ogreNode->translate(x, y, z);
		break;
	case 119: //ASCII code for "w"		
		ogreNode->pitch(Degree(-45));
	break;
	case 115: //ASCII code for "s"
		ogreNode->pitch(Degree(45));
	break;
	case 97: //ASCII code for "a"
		ogreNode->yaw(Degree(-45));
	break;
	case 100: //ASCII code for "d"
		ogreNode->yaw(Degree(45));
	break;
	case 120: //ASCII code for "x"
		ogreNode->roll(Degree(-45));
		break;
	case 122: //ASCII code for "z"
		ogreNode->roll(Degree(45));
		break;
	default:
		break;
	}
	ogreNode->setPosition(x, y, z);
	return true;
}

bool BasicTutorial1::frameRenderingQueued(const FrameEvent& evt)
{
	//mTrayMgr->frameRendered(evt);
	//mControls->frameRendered(evt);

	//if (!mTrayMgr->isDialogVisible())
	//{
	//    mCameraMan->frameRendered(evt);   // if dialog isn't up, then update the camera
	//}
	//ogreNode->setPosition(x, y, z);
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