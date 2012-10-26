/*
 * Copyright (C) 2011 by Francois Coulombe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "tanklib/TankGame.h"
#include "tanklib/ControllerManager.h"
#include "tanklib/SceneManager.h"


using namespace tank;

//-------------------------------------------------------------------------------------
TankGame::TankGame(void)
{
}
//-------------------------------------------------------------------------------------
TankGame::~TankGame(void)
{
}

//-------------------------------------------------------------------------------------
void TankGame::createScene(void)
{
	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
	{
		mCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
	}
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

	SceneManager::Instance()->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	Ogre::Light* light = SceneManager::Instance()->createLight("tstLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(lightdir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	//mSinbad = new Sinbad();
	mActor = new Actor();
	mSkyBox = new SkyBox();
	//mTerrain = new Terrain(light);

	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	plane.d = 0;

	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 4500.0f, 4500.0f, 10, 10, true, 1, 50.0f, 50.0f, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* planeEnt = SceneManager::Instance()->createEntity("plane", "floor");
	planeEnt->setMaterialName("Examples/GrassFloor");
	planeEnt->setCastShadows(false);
	SceneManager::Instance()->getRootSceneNode()->createChildSceneNode()->attachObject(planeEnt);

	// Set the camera to look at our handiwork
	mCamera->setPosition(90.0f, 280.0f, 535.0f);
	mCamera->pitch(Ogre::Degree(-30.0f));
	mCamera->yaw(Ogre::Degree(-15.0f));

	mCamera->setAutoTracking(true, mActor->GetSceneNode());


	SceneManager::Instance()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
}
void TankGame::createFrameListener(void)
{
	BaseApplication::createFrameListener();
	mActor->Idle();

}

bool TankGame::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);
	//mTerrain->Update(evt.timeSinceLastFrame);
	mActor->Update(evt.timeSinceLastFrame);

	return ret;
}


bool TankGame::keyReleased( const OIS::KeyEvent &arg )
{
	bool ret = BaseApplication::keyReleased(arg);
	if (arg.key == OIS::KC_UP)   // toggle visibility of advanced frame stats
	{
		mActor->Stop();
	}
	if (arg.key == OIS::KC_LEFT)   // toggle visibility of advanced frame stats
	{
		mActor->StopTurn();
	}
	else if (arg.key == OIS::KC_RIGHT)   // toggle visibility of advanced frame stats
	{
		mActor->StopTurn();
	}
	return ret;
}

bool TankGame::keyPressed( const OIS::KeyEvent &arg )
{
	bool ret = BaseApplication::keyPressed(arg);
	//ControllerManager::Instance().KeyPressed(arg);

	if (arg.key == OIS::KC_Z)   // toggle visibility of advanced frame stats
	{
		mActor->Walk(Ogre::Vector3(300,0,300));
	}
	if (arg.key == OIS::KC_UP)   // toggle visibility of advanced frame stats
	{
		mActor->Walk();
	}
	if (arg.key == OIS::KC_LEFT)   // toggle visibility of advanced frame stats
	{
		mActor->Turn(1.0);
	}
	else if (arg.key == OIS::KC_RIGHT)   // toggle visibility of advanced frame stats
	{
		mActor->Turn(-1.0);
	}
	if (arg.key == OIS::KC_SPACE)   // toggle visibility of advanced frame stats
	{
		mActor->Shoot();
	}
	if (arg.key == OIS::KC_1)   // toggle visibility of advanced frame stats
	{
		mActor->Jump();
	}

	return ret;
}

