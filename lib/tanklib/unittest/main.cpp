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
 */#include <iostream>


#include "TankGameTest.h"
#include "SkyBoxTest.h"
#include "ActorTest.h"
 int main(int /*argc*/, char ** argv)
 {
	 try
	 {
		 TankGameTest::Test();
		 SkyBoxTest::Test();
		 ActorTest::Test();
	 }
	 catch (GCLException & e)
	 {
		 std::stringstream str;
		 str << "[FAILED] " << argv[0] << std::endl;
		 str << e.what();
		 std::cerr << str.str();
		 return -1;
	 }
	 catch( Ogre::Exception& e )
	 {
		 std::cerr << "An exception has occured: " <<
				 e.getFullDescription().c_str() << std::endl;
	 }
	 catch (std::exception &e)
	 {
		 std::cerr << "[FAILED] " << e.what() << std::endl;
		 return -1;
	 }
	 catch (...)
	 {
		 std::cerr << "[FAILED] not sure what happened" << std::endl;
	 }

	 return 0;
 }
