//week13-2-SubmeshDemo 
//This time we are going to create a plane using the lower level Ogre::HardwareBuffer primitives.
//We start by creating a Mesh object.As this is a manual Mesh, we have to set the bounds of it explicitly.
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
		//_node->setPosition(x, y, 0);
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
	OgreTutorial();
	virtual ~OgreTutorial() {}

	void setup();
	void createScene();
	void createCamera();
	bool keyPressed(const KeyboardEvent& evt);
	void createFrameListener();
	Ogre::SceneNode* TriangleNode;
};


OgreTutorial::OgreTutorial()
	: ApplicationContext("week13-2-SubmeshDemo")
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



	Ogre::ManualObject* man = scnMgr->createManualObject("Quad");
	man->begin("Examples/OgreLogo", Ogre::RenderOperation::OT_TRIANGLE_LIST);


	man->position(-20, 20, 20);
	man->normal(0, 0, 1);
	man->textureCoord(0, 0);

	man->position(-20, -20, 20);
	man->normal(0, 0, 1);
	man->textureCoord(0, 1);

	man->position(20, -20, 20);
	man->normal(0, 0, 1);
	man->textureCoord(1, 1);

	man->position(20, 20, 20);
	man->normal(0, 0, 1);
	man->textureCoord(1, 0);

	man->quad(0, 1, 2, 3);

	man->end();

	man->convertToMesh("Quad");

	Ogre::Entity* ent = scnMgr->createEntity("Quad");
	TriangleNode = scnMgr->getRootSceneNode()->createChildSceneNode("TriangleNode");
	TriangleNode->attachObject(ent);

	/// <summary>
	/// We start by creating a Mesh object. As this is a manual Mesh, we have to set the bounds of it explicitly.
	/// Next we define what should end up in our vertex and index buffer. We will store all data interleaved in one buffer. This typically has some advantages due to cache coherency and also is what ManualObject does automatically for us
	/// </summary>
	MeshPtr mesh = MeshManager::getSingleton().createManual("mesh1", RGN_DEFAULT);
	mesh->_setBounds(AxisAlignedBox({ -100,-100,0 }, { 100,100,0 }));
	float vertices[32] = {
		   -100, -100, 0,  // pos
		   0,0,1,          // normal
		   0,1,            // texcoord
		   100, -100, 0,
		   0,0,1,
		   1,1,
		   100,  100, 0,
		   0,0,1,
		   1,0,
		   -100,  100, 0 ,
		   0,0,1,
		   0,0
	};

	uint16 faces[6] = { 0,1,2,
					   0,2,3 };

	//To describe the vertex sources, we have to create a Ogre::VertexData object.Notably it stores how many vertices we have.
	mesh->sharedVertexData = new VertexData();
	mesh->sharedVertexData->vertexCount = 4;
	VertexDeclaration * decl = mesh->sharedVertexData->vertexDeclaration;
	VertexBufferBinding * bind = mesh->sharedVertexData->vertexBufferBinding;

	size_t offset = 0;
	offset += decl->addElement(0, offset, VET_FLOAT3, VES_POSITION).getSize();
	offset += decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL).getSize();
	offset += decl->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0).getSize();

	HardwareVertexBufferSharedPtr vbuf =
		HardwareBufferManager::getSingleton().createVertexBuffer(offset, 4, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);
	bind->setBinding(0, vbuf);

	HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().createIndexBuffer(
		HardwareIndexBuffer::IT_16BIT, 6, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

	//Finally we create the Ogre::SubMesh that will be ultimately rendered.

	SubMesh * sub = mesh->createSubMesh();
	sub->useSharedVertices = true;
	sub->indexData->indexBuffer = ibuf;
	sub->indexData->indexCount = 6;
	sub->indexData->indexStart = 0;

	mesh->load();

	Entity* groundEntity = scnMgr->createEntity("mesh1");
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	//And finally we need to give our ground a material.
	groundEntity->setMaterialName("Examples/BeachStones");


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
	camNode->setPosition(0, 0, 200);
	camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_LOCAL);

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
	Ogre::FrameListener* FrameListener = new ExampleFrameListener(TriangleNode);
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

//! [fullsource]










