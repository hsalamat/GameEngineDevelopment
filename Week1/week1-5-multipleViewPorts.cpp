/*-------------------------------------------------------------------------
You may wonder why you might want to have multiple viewports for a single
render window. Consider a car racing game where you want to display the rear
view mirror in the top portion of your render window. One way to accomplish,
this would be to define a viewport that draws to the entire render window, and
gets its content from a camera facing out the front windshield of the car, and
another viewport that draws to a small subsection of the render window and
gets its content from a camera facing out the back windshield.

Ogre::Viewport::Viewport	(	Camera * 	camera,
RenderTarget * 	target,
Real 	left,
Real 	top,
Real 	width,
Real 	height,
int 	ZOrder
)


camera	Pointer to a camera to be the source for the image.
target	Pointer to the render target to be the destination for the rendering.
left,top,width,height	Dimensions of the viewport, expressed as a value between 0 and 1. 
This allows the dimensions to apply irrespective of changes in the target's size: e.g. to fill the whole area, values of 0,0,1,1 are appropriate.
ZOrder	Relative Z-order on the target. Lower = further to the front.
-------------------------------------------------------------------------*/

//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
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
    : ApplicationContext("Transformation")
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
    SceneNode* camNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam1 = scnMgr->createCamera("myCam");
    cam1->setNearClipDistance(5); // specific to this sample
    cam1->setAutoAspectRatio(true);
    //camNode->attachObject(cam1);
    // Position it at 500 in Z direction
    cam1->setPosition(Vector3(0, 0, 500));
    cam1->lookAt(Vector3(0, 0, -300));
    // Look back along -Z

    Camera* cam2 = scnMgr->createCamera("myCam2");
    cam2->setNearClipDistance(5); // specific to this sample
    // Position it at 500 in -Z direction
    cam2->setPosition(Vector3(0, 0, -500));
    cam2->lookAt(Vector3(0, 0, 300));
    cam2->setAutoAspectRatio(true);
    //camNode2->attachObject(cam2);


    // and tell it to render into the main window
    //getRenderWindow()->addViewport(cam);


    // Create first viewport, 1/2 vertical window, left side
   // Camera Name, Z-Order, Left, Right, Width, Height);

    Ogre::Viewport* vp = 0;

    vp = getRenderWindow()->addViewport(cam1, 0, 0, 0, 0.5, 1);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    // Alter the camera aspect ratio to match the viewport
    cam1->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    // Create second viewport, 1/2 vertical window, right side
    // Camera Name, Z-Order, Left, Right, Width, Height,);

    vp = getRenderWindow()->addViewport(cam2,  1, 0.5, 0, 0.5, 1);
    vp->setBackgroundColour(Ogre::ColourValue(0, 1, 0));
    // Alter the camera aspect ratio to match the viewport
    cam2->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    //if you wanted a horizonal split screen(2 viewports), all you would need to do is make these changes :
    //vp = getRenderWindow()->addViewport(cam1, 0, 0, 0, 1, .5);
    //vp = getRenderWindow()->addViewport(cam2, 1, 0, .5, 1, .5);

    //! [camera]

    //! [entity1]
    Entity* ogreEntity = scnMgr->createEntity("ninja.mesh");
    //! [entity1]

    //! [entity1node]
    SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //! [entity1node]

    //! [entity1nodeattach]
    ogreNode->attachObject(ogreEntity);
    //! [entity1nodeattach]

   

    //! [cameramove]
    //camNode->setPosition(0, 0, -500);
    //camNode2->setPosition(0, 0, -500);
    //! [cameramove]


    //Ogre::SceneNode* miniScreenNode =
    //    scnMgr->getRootSceneNode()->createChildSceneNode();
    //Ogre::Rectangle2D* mMiniScreen = new Ogre::Rectangle2D(true);
    //mMiniScreen->setCorners(.5, 1.0, 1.0, .5);
    //mMiniScreen->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
    //miniScreenNode->attachObject(mMiniScreen);

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
