//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"

#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"

#include <iostream>

using namespace Ogre;
using namespace OgreBites;

#define TERRAIN_FILE_PREFIX String("testTerrain")
#define TERRAIN_FILE_SUFFIX String("dat")
#define TERRAIN_WORLD_SIZE 12000.0f
#define TERRAIN_SIZE 513
//#define PAGING

#define TERRAIN_PAGE_MIN_X 0
#define TERRAIN_PAGE_MIN_Y 0
#define TERRAIN_PAGE_MAX_X 0
#define TERRAIN_PAGE_MAX_Y 0

class Game
	: public ApplicationContext
	, public InputListener
{
public:
	Game();
	virtual ~Game() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);

	void configureTerrainDefaults(Light* l);
	void defineTerrain(long x, long y, bool flat);
	void getTerrainImage(bool flipX, bool flipY, Image& img);
	void initBlendMaps(Terrain* terrain);

	TerrainGlobalOptions* mTerrainGlobals;
	TerrainGroup* mTerrainGroup;
	Vector3 mTerrainPos;
	bool mTerrainsImported;

	SceneManager* scnMgr;
};


Game::Game()
	: ApplicationContext("Terrain")
	, mTerrainPos(1000, 0, 5000)
	, mTerrainGlobals(0)
	, mTerrainGroup(0)
	, mTerrainsImported(false)
	, scnMgr(0)
{
}


void Game::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	Root* root = getRoot();
	scnMgr = root->createSceneManager();

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
	//Light* light = scnMgr->createLight("MainLight");
	//SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	//lightNode->attachObject(light);
	//! [newlight]

	//! [lightpos]
	//lightNode->setPosition(20, 80, 50);
	//! [lightpos]

	//! [camera]
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	//cam->setNearClipDistance(5); // specific to this sample
	//cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	//camNode->setPosition(0, 0, 140);
	camNode->setPosition(mTerrainPos + Vector3(1683, 50, 2116));
	camNode->lookAt(Vector3(1963, 50, 1660), Node::TS_PARENT);
	cam->setNearClipDistance(40);
	cam->setFarClipDistance(50000);
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	//! [camera]


	if (root->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
	{
		cam->setFarClipDistance(0);   // enable infinite far clip distance if we can
	}
	//! [cameralaststep]

	Ogre::Light* l = scnMgr->createLight("tstLight");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDiffuseColour(ColourValue::White);
	l->setSpecularColour(ColourValue(0.4, 0.4, 0.4));

	Ogre::SceneNode* ln = scnMgr->getRootSceneNode()->createChildSceneNode();
	ln->setDirection(Vector3(0.55, -0.3, 0.75).normalisedCopy());
	ln->attachObject(l);

	//This is a class that holds information for all of the terrains we might create - that is why they are called ''global'' options. It also provides a few getters and setters. There are also local options for each TerrainGroup that we will see later in this tutorial.
	mTerrainGlobals = new Ogre::TerrainGlobalOptions();

	mTerrainGroup = new Ogre::TerrainGroup(scnMgr, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(TERRAIN_FILE_PREFIX, TERRAIN_FILE_SUFFIX);
	mTerrainGroup->setOrigin(mTerrainPos);

	configureTerrainDefaults(l);

	//The next thing we do is define our terrains and ask the TerrainGroup to load them all.

	for (long x = TERRAIN_PAGE_MIN_X; x <= TERRAIN_PAGE_MAX_X; ++x)
		for (long y = TERRAIN_PAGE_MIN_Y; y <= TERRAIN_PAGE_MAX_Y; ++y)
			defineTerrain(x, y, false); //hooman: I added false
// sync load since we want everything in place when we start
	mTerrainGroup->loadAllTerrains(true);

	//We will now initialize the blend maps for our terrain.

	if (mTerrainsImported)
	{
		TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		while (ti.hasMoreElements())
		{
			Terrain* t = ti.getNext()->instance;
			initBlendMaps(t);
		}
	}

	mTerrainGroup->freeTemporaryResources();

	OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

	//Once you have your tray manager, make sure you relay input events to it.
	addInputListener(mTrayMgr);

	mTrayMgr->showLogo(TL_TOPRIGHT);
	mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
	//mTrayMgr->toggleAdvancedFrameStats();

	OgreBites::Label* mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "My Game Engine", 350);

	// a friendly reminder
	StringVector names;
	names.push_back("Help");
	mTrayMgr->createParamsPanel(TL_TOPLEFT, "Help", 100, names)->setParamValue(0, "H/F1");

	if (mTerrainGroup->isDerivedDataUpdateInProgress())
	{
	    mTrayMgr->moveWidgetToTray(mInfoLabel, TL_TOP, 0);
	    mInfoLabel->show();
	    if (mTerrainsImported)
	    {
	        mInfoLabel->setCaption("Building terrain, please wait...");
	    }
	    else
	    {
	        mInfoLabel->setCaption("Updating textures, patience...");
	    }
	}
	else
	{
	    mTrayMgr->removeWidgetFromTray(mInfoLabel);
	    mInfoLabel->hide();
	    if (mTerrainsImported)
	    {
	        // FIXME does not end up in the correct resource group
	        // saveTerrains(true);
	        mTerrainsImported = false;
	    }
	}

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



void Game::configureTerrainDefaults(Light* l)
{
	//! [configure_lod]
	mTerrainGlobals->setMaxPixelError(8);
	mTerrainGlobals->setCompositeMapDistance(3000);
	//! [configure_lod]

	//mTerrainGlobals->setUseRayBoxDistanceCalculation(true);
	//mTerrainGlobals->getDefaultMaterialGenerator()->setDebugLevel(1);
	//mTerrainGlobals->setLightMapSize(256);

	// Disable the lightmap for OpenGL ES 2.0. The minimum number of samplers allowed is 8(as opposed to 16 on desktop).
	// Otherwise we will run over the limit by just one. The minimum was raised to 16 in GL ES 3.0.
	if (Ogre::Root::getSingletonPtr()->getRenderSystem()->getCapabilities()->getNumTextureUnits() < 9)
	{
		TerrainMaterialGeneratorA::SM2Profile* matProfile =
			static_cast<TerrainMaterialGeneratorA::SM2Profile*>(mTerrainGlobals->getDefaultMaterialGenerator()->getActiveProfile());
		matProfile->setLightmapEnabled(false);
	}

	//! [composite_lighting]
	// Important to set these so that the terrain knows what to use for baked (non-realtime) data

	//hooman: to fix this line - some static library link is missing
	//mTerrainGlobals->setLightMapDirection(l->getDerivedDirection());
	mTerrainGlobals->setLightMapDirection(Vector3(0.55, -0.3, 0.75).normalisedCopy());

	mTerrainGlobals->setCompositeMapAmbient(scnMgr->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(l->getDiffuseColour());
	//! [composite_lighting]
	//mTerrainGlobals->setCompositeMapAmbient(ColourValue::Red);

	// Configure default import settings for if we use imported image
	//! [import_settings]
	Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = TERRAIN_SIZE;
	defaultimp.worldSize = TERRAIN_WORLD_SIZE;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;
	//! [import_settings]

	//! [tex_from_src]
	Image combined;
	combined.loadTwoImagesAsRGBA("Ground23_col.jpg", "Ground23_spec.png", "General");
	TextureManager::getSingleton().loadImage("Ground23_diffspec", "General", combined);
	//! [tex_from_src]

	//! [textures]
	defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 200;
	defaultimp.layerList[0].textureNames.push_back("Ground37_diffspec.dds");
	defaultimp.layerList[0].textureNames.push_back("Ground37_normheight.dds");
	defaultimp.layerList[1].worldSize = 200;
	defaultimp.layerList[1].textureNames.push_back("Ground23_diffspec"); // loaded from memory
	defaultimp.layerList[1].textureNames.push_back("Ground23_normheight.dds");
	defaultimp.layerList[2].worldSize = 400;
	defaultimp.layerList[2].textureNames.push_back("Rock20_diffspec.dds");
	defaultimp.layerList[2].textureNames.push_back("Rock20_normheight.dds");
	//! [textures]
}


void Game::defineTerrain(long x, long y, bool flat = false)
{
	// if a file is available, use it
	// if not, generate file from import

	// Usually in a real project you'll know whether the compact terrain data is
	// available or not; I'm doing it this way to save distribution size

	if (flat)
	{
		mTerrainGroup->defineTerrain(x, y, 0.0f);
		return;
	}

	//! [define]
	String filename = mTerrainGroup->generateFilename(x, y);
	if (ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
	{
		mTerrainGroup->defineTerrain(x, y);
	}
	else
	{
		Image img;
		getTerrainImage(x % 2 != 0, y % 2 != 0, img);
		mTerrainGroup->defineTerrain(x, y, &img);
		mTerrainsImported = true;
	}
	//! [define]
}

void Game::getTerrainImage(bool flipX, bool flipY, Image& img)
{
	//! [heightmap]
	img.load("terrain.png", mTerrainGroup->getResourceGroup());
	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();
	//! [heightmap]
}


void Game::initBlendMaps(Terrain* terrain)
{
	//! [blendmap]
	using namespace Ogre;
	TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	float minHeight0 = 20;
	float fadeDist0 = 15;
	float minHeight1 = 70;
	float fadeDist1 = 15;
	float* pBlend0 = blendMap0->getBlendPointer();
	float* pBlend1 = blendMap1->getBlendPointer();
	for (uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
	{
		for (uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
		{
			Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			float height = terrain->getHeightAtTerrainPosition(tx, ty);

			*pBlend0++ = Math::saturate((height - minHeight0) / fadeDist0);
			*pBlend1++ = Math::saturate((height - minHeight1) / fadeDist1);
		}
	}
	blendMap0->dirty();
	blendMap1->dirty();
	blendMap0->update();
	blendMap1->update();
	//! [blendmap]
	// set up a colour map
	/*
	  if (!terrain->getGlobalColourMapEnabled())
	  {
	  terrain->setGlobalColourMapEnabled(true);
	  Image colourMap;
	  colourMap.load("testcolourmap.jpg", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	  terrain->getGlobalColourMap()->loadImage(colourMap);
	  }
	*/
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
