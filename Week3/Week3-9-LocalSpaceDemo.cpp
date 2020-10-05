//Week3-9-SapceDemo
//There are three kinds of spaces we have in a 3D scene— world space, parent space, and local space.
//The default setting of translate() is to use parent space.
//When we call the translate() function, the geometry is moved in parent space if the space to use is not defined.
//When no parent of the geometry is rotated, translate() behaves the same way with world space as it would when used with parent or local space.
//Local space is where the model itself is defined.
//Local space includes all rotations, from the scene node itself to all parents.
//You could use a new parameter in the translate() function(Ogre::Node::TS_WORLD).
//World space always has the same orientation of axis.
//When we translate, the default setting is parent
//space, meaning that all rotations, except the rotation of the scene node we translate, are
//used while translating.When using world space, no rotation is taken into consideration.
//When translating, the world coordination system is used.When translating in local space,
//every rotation, even the rotation from the node we translate, is used for the translation.
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
		//_camNode->yaw(Ogre::Radian(rotX * _mousespeed));
		//_camNode->pitch(Ogre::Radian(rotY * _mousespeed));
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
	: ApplicationContext("week3-9-SpaceDemo")
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

	Ogre::SceneNode* node = scnMgr->createSceneNode("Node0");
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


	Ogre::Entity* ent = scnMgr->createEntity("MyEntity", "Sinbad.mesh");
	SinbadNode = scnMgr->createSceneNode("SinbadNode");
	SinbadNode->setPosition(0, 0, 400);
	SinbadNode->yaw(Ogre::Degree(180.0f));
	scnMgr->getRootSceneNode()->addChild(SinbadNode);
	SinbadNode->attachObject(ent);

	Ogre::Entity* ent2 = scnMgr->createEntity("MyEntity2", "Sinbad.mesh");
	Ogre::SceneNode* node2 = SinbadNode->createChildSceneNode("node2");
	node2->yaw(Ogre::Degree(45));
	node2->translate(10, 0, 0, Ogre::Node::TS_PARENT);
	node2->attachObject(ent2);

	Ogre::Entity* ent3 = scnMgr->createEntity("MyEntity3", "Sinbad.mesh");
	Ogre::SceneNode* node3 = SinbadNode->createChildSceneNode("node3");
	node3->yaw(Ogre::Degree(45));
	node3->translate(10, 0, 0, Ogre::Node::TS_LOCAL);
	node3->attachObject(ent3);

	Ogre::Entity* ent4 = scnMgr->createEntity("MyEntity4", "Sinbad.mesh");
	Ogre::SceneNode* node4 = SinbadNode->createChildSceneNode("node4");
	node4->yaw(Ogre::Degree(45));
	node4->translate(10, 0, 0, Ogre::Node::TS_WORLD);
	node4->attachObject(ent4);

}

void OgreTutorial::createCamera()
{
	//! [camera]
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	// Look back along -Z
	cam->lookAt(Vector3(0, 0, -300));
	camNode->attachObject(cam);

	// Position it at 500 in Z direction
	camNode->setPosition(Vector3(0, 0, 450));
	
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

