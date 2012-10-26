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

#include "tanklib/Actor.h"
#include "tanklib/SceneManager.h"

using namespace tank;

//-------------------------------------------------------------------------------------
Actor::Actor(void)
: GameObject("Actor"),
  mIsWalking(false)
{
	// Create the entity
	Ogre::SceneManager* tempSceneManager = SceneManager::Instance();
	mEntity = tempSceneManager->createEntity("Robot", "robot.mesh");

	// Create the scene node
	mNode = tempSceneManager->getRootSceneNode()->
			createChildSceneNode("RobotNode", Ogre::Vector3(0.0f, 0.0f, 25.0f));
	mNode->attachObject(mEntity);

	mWalkSpeed = 50.0f;

	mTurningSpeed = 3.0f;

}
//-------------------------------------------------------------------------------------
Actor::~Actor(void)
{
}

void Actor::Shoot()
{
	std::cout << "Shoot!\n" << std::endl;
	mAnimationState = mEntity->getAnimationState("Shoot");
	mAnimationState->setTimePosition(0.0);
	mAnimationState->setLoop(false);
	mAnimationState->setEnabled(true);
}
void Actor::Jump()
{
	mAnimationState = mEntity->getAnimationState("Jump");
	mAnimationState->setLoop(false);
	mAnimationState->setEnabled(true);
}

void Actor::Turn(Ogre::Real direction)
{
	mIsTurning = true;
	mTurningDirection = direction;
}
void Actor::Stop()
{
	Idle();
	mIsWalking = false;
}
void Actor::Walk()
{
	if (!mIsWalking)
	{
		mIsWalking = true;
		mAnimationState = mEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}
}

void Actor::Walk(const Ogre::Vector3 & /*position*/)
{
	mAnimationState = mEntity->getAnimationState("Walk");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);

	/*mDestination = position;
	mDirection = mDestination - mNode->getPosition();
	Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
	src.y = 0;                                                    // Ignore pitch difference angle
	mDirection.y = 0;
	src.normalise();
	Ogre::Quaternion quat = src.getRotationTo(mDirection);
	mNode->rotate(quat);
	mDistance = mDirection.normalise();*/
}
void Actor::Update(GCL::Real idt)
{
	Ogre::Real dt = idt;
	mAnimationState->addTime(dt);
	if (mIsWalking)
	{
		const Ogre::Vector3 direction = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
		mNode->translate(direction*mWalkSpeed*dt);
	}
	if (mIsTurning)
	{
		mNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(mTurningSpeed*mTurningDirection*dt));
	}
}
