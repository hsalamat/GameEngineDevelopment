//Week4-1-ManualObjectDemo
// Create our own model
//How to Draw a Simple Triangle
// Rendering operation using vertex buffers
//  OT_POINT_LIST = 1, OT_LINE_LIST = 2, OT_LINE_STRIP = 3, OT_TRIANGLE_LIST = 4,
//  OT_TRIANGLE_STRIP = 5, OT_TRIANGLE_FAN = 6,...
//Hooman Salamat


#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);

class OgreTutorial
	: public ApplicationContext
	, public InputListener
{
private:
	SceneNode* TriangleNode;
	SceneManager* scnMgr;
	Root* root;
	Ogre::ManualObject* ManualObject;
public:
	OgreTutorial();
	virtual ~OgreTutorial() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	void createScene();
	void createCamera();
	bool frameStarted(const FrameEvent& evt);

};


OgreTutorial::OgreTutorial()
	: ApplicationContext("4-1-ManualObjectDemo")
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

	std::cout << scnMgr->getTypeName() << "::" << scnMgr->getName() << std::endl;

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	createScene();
	createCamera();
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

	//! [newlight]
	ManualObject = NULL;
	ManualObject = scnMgr->createManualObject("Triangle");
	ManualObject->setDynamic(false);
	ManualObject->begin("BaseWhiteNoLighting",
		Ogre::RenderOperation::OT_TRIANGLE_LIST);
	ManualObject->position(0, 0, 0);
	ManualObject->position(3, 0, 0);
	ManualObject->position(3, 3, 0);
	ManualObject->position(0, 3, 0);
	ManualObject->triangle(0, 1, 2);
	ManualObject->triangle(0, 2, 3);
	ManualObject->end();

	Ogre::SceneNode* TriangleNode = scnMgr->getRootSceneNode()->
		createChildSceneNode("TriangleNode");
	TriangleNode->attachObject(ManualObject);
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

/// frameStarted Gets called for every frame
bool OgreTutorial::frameStarted(const FrameEvent& evt) {
	//std::cout << "Frame Started" << std::endl;
	return true;
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



	

