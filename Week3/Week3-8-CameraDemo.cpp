//Week3-8-CameraDemo
//We used our created camera in combination with user input.To be able to manipulate the
//camera, we needed to pass it to our FrameListener.This was done in ExampleFrameListener using
//the constructor.To control our camera, we wanted to use the mouse.So first we had to
//override mouseMoved interface.
//Mouse movement can happen on two axes, namely, the x - axis and the y - axis.Both axes'
//movements are saved separately in the X and Y variable of the mouse state.We then have
//the possibility to get the relative or absolute values.Because we are only interested in
//mouse movement and not the position of the mouse, we are using the relative values.
//Hooman Salamat


#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;

class ExampleFrameListener : public Ogre::FrameListener
{
private:
	Ogre::SceneNode* _sceneNode;
	Ogre::SceneNode* _camNode;
	float _movementspeed;
	float _mousespeed;
public:

	ExampleFrameListener(Ogre::SceneNode* sceneNode, Ogre::SceneNode* camNode)
	{
		_sceneNode = sceneNode;
		_camNode = camNode;
		_movementspeed = 200.0f;
		_mousespeed = 0.002f;
	}

	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		_camNode->yaw(Ogre::Radian(rotX * _mousespeed));
		_camNode->pitch(Ogre::Radian(rotY * _mousespeed));
		//_camNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);
		_sceneNode->translate(translate * evt.timeSinceLastFrame * _movementspeed);
		translate = Ogre::Vector3(0, 0, 0);
		rotX = 0.0f;
		rotY = 0.0f;
		return true;
	}
};

class OgreTutorial
	: public ApplicationContext
	, public InputListener
{
private:
	SceneNode* SinbadNode;
	SceneNode* camNode;
	SceneManager* scnMgr;
	Camera* cam;
	Root* root;
public:
	OgreTutorial();
	virtual ~OgreTutorial() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
	void createScene();
	void createCamera();
	void createFrameListener();
};


OgreTutorial::OgreTutorial()
	: ApplicationContext("week3-8-CameraDemo")
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

bool OgreTutorial::mouseMoved(const MouseMotionEvent& evt)
{
	 rotX = evt.xrel;
	 rotY = evt.yrel;	 
	return true;
}

bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'w':
		translate = Ogre::Vector3(0, 0, -10);
		break;
	case 's':
		translate = Ogre::Vector3(0, 0, 10);
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

void OgreTutorial::createScene()
{
	// -- tutorial section start --

	Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
	scnMgr->getRootSceneNode()->addChild(node);

	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
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
	lightNode->setScale(0.01f, 0.01f, 0.01f);

	//! [newlight]
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
}

void OgreTutorial::createCamera()
{
	//! [camera]
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 100, 200);
	camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
	
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);

	//! [camera]


}

void OgreTutorial::createFrameListener()
{
	Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, camNode);
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

