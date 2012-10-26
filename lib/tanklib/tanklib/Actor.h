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

#pragma once
#include <3rdparty/Ogre.h>
#include "tanklib/GameObject.h"
namespace tank
{
class Actor : public GameObject
{
public:
	Actor(void);
	virtual ~Actor(void);

	void Update(GCL::Real dt);
	void Idle()
	{
		mAnimationState = mEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
	}

	void Turn(Ogre::Real direction);
	void Shoot();
	void Jump();
	void Walk(const Ogre::Vector3 &position);
	void Walk();
	void Stop();
	void StopTurn() { mIsTurning = false; }



protected:


	Ogre::AnimationState *mAnimationState; // The current animation state of the object

	Ogre::Entity *mEntity;                 // The Entity we are animating

	Ogre::Real mWalkSpeed;                 // The speed at which the object is moving
	Ogre::Real mTurningSpeed;
	Ogre::Real mTurningDirection;
	bool mIsWalking;
	bool mIsTurning;
};
}
