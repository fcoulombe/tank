#Copyright (C) 2011 by Francois Coulombe

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# 

import os
import os.path
import atexit
import sys
import platform
import subprocess

#################################################################
#
#   adding custom commandline argument
#
#################################################################
AddOption('--verbose', action="store_true", 
          dest="verbose",
          default=False,
          help='make the build verbose')

AddOption('--use-valgrind', action="store_true", 
          dest="useValgrind",
          default=False,
          help='run the unit tests with valgrind')

AddOption('--print-component-dependencies', action="store_true", 
          dest="print-component-dependencies",
          default=False,
          help='prints the component dependnecies for the programs')


AddOption('--gen-valgrind-suppressions', action="store_true", 
          dest="genValgrindSuppressions",
          default=False,
          help='generate valgrind suppression files')

AddOption('--compiler', action="store",
          type='string', 
          dest="compiler",
          default='gcc',
          help='specify the compiler')

AddOption('--configuration', action="store",
          type='string', 
          dest="configuration",
          default='debug',
          help='specify whether we are compiling in (debug, opt) mode')


########################################################################
#
#   fetching some other packages from github if they don't seem to be there
#   usually on used on very first build
#
########################################################################
targetList = COMMAND_LINE_TARGETS

default_env = Environment()
default_env.SConsignFile(default_env.File("#build/.sconsign.dblite").abspath) 
#detect if we have the build script installed (hopefully its gonna be the right one)

##############################################
#
#    SELECT COMPILER
#
##############################################
compiler = GetOption('compiler')

lflags = [] 
cflags = [ ]
if default_env['PLATFORM']=='darwin':
    cflags.append("-DOS_MACOSX")
elif default_env['PLATFORM']=='win32':
    cflags.append("-DOS_WIN32")
else:
    cflags.append("-DOS_LINUX") 
                     
if platform.architecture()[0] == "32bit":
    cflags.append('-DUSE_64BIT_PLATFORM=0')
elif platform.architecture()[0] == "64bit":
    cflags.append('-DUSE_64BIT_PLATFORM=1')
else:
    print "unsupported architecture: %s" % platform.architecture()[0] 

configuration = GetOption('configuration')
if compiler == 'gcc':
    extracflags = [ "-g", "-Wall",  '-fexceptions', '-ftrapv', '-DFBXSDK_NEW_API'] #, '-fvisibility=hidden']   
    cflags.extend(extracflags)
    cflags.append("-Werror")
    cflags.append("-Wextra")
    default_env['CXX'] = 'g++'
    default_env['CC'] = 'gcc'
    #default_env['CXX'] = 'scan-build g++'
    #default_env['CC'] = 'scan-build gcc'
    cflags.append("-std=c++0x");
    #cflags.append("-pedantic")
    lflags.append("-L/usr/lib/")
    lflags.append("-rdynamic");
    if configuration == 'debug':
        cflags.append("-O0")
    elif configuration == 'opt':
        cflags.append("-O3")
elif compiler == 'clang':
    extracflags = [ "-g", "-Wall",  '-fexceptions', '-ftrapv', '-DFBXSDK_NEW_API'] #, '-fvisibility=hidden']   
    cflags = cflags+extracflags
    
    if default_env['PLATFORM']=='darwin':
        default_env['CXX'] = '/Developer//usr/bin/clang++'
        default_env['CC'] = '/Developer//usr/bin/clang'
    else:
        default_env['CXX'] = 'clang++'
        default_env['CC'] = 'clang'
    cflags.append("-std=c++0x");
    cflags.append("-pedantic")
    cflags.append("-Wextra" )
    #cflags.append("-Werror" )
    lflags.append("-L/usr/lib/")
    if configuration == 'debug':
        cflags.append("-O0")
    elif configuration == 'opt':
        cflags.append("-O3")
elif compiler == 'vc':
    default_env['CXX'] = 'cl.exe'
    default_env['CC'] = 'cl.exe'
    cflags.append("/WX")
    cflags.append("/EHsc")
    cflags.append("/ZI")
    if configuration == 'debug':
        cflags.append("-Od")
    elif configuration == 'opt':
        cflags.append("-O3")
    #lflags.append("/NODEFAULTLIB:library")
    lflags.append("/DEBUG")
    cflags.append("/MDd")
else:
    print "this isn't good"
default_env.Append(CPPPATH=[default_env.Dir("#3rdParty/include")])
#default_env['CXX'] = 'scan-build -k'
#default_env['CC'] = 'scan-build -k'


default_env.AppendUnique(CPPFLAGS=cflags )
default_env.AppendUnique(CFLAGS=cflags)
#default_env.AppendUnique(CXXFLAGS=cflags)
default_env.AppendUnique(LINKFLAGS=lflags)
variant ="%s-%s-%s-%s" % (default_env['CC'], platform.machine(),  platform.architecture()[0], configuration) 
print variant

if not GetOption('verbose'):
    default_env['RANLIBCOMSTR'] = "[ranlib] $TARGET" 
    default_env['ARCOMSTR'] = "[ar] $TARGET"
    default_env['CCCOMSTR'] = "[cc] $SOURCE"
    default_env['CXXCOMSTR'] = "[cxx] $SOURCE"
    default_env['LINKCOMSTR'] = "[link] $TARGET"
    default_env['INSTALLSTR'] = '[install] $TARGET'

default_env['INSTALL_DIR'] = '#/bin/' + variant 
default_env['BUILD_VARIANT'] = variant
    
##############################################
##############################################


default_env.Tool('Profiler', toolpath=['site_scons/site_tools'])
default_env.Tool('Catalog', toolpath=['site_scons/site_tools'])
default_env.Tool('SConsWalk', toolpath=['site_scons/site_tools'])
default_env.Tool('Wrappers', toolpath=['site_scons/site_tools'])
default_env.Tool('RSync', toolpath=['site_scons/site_tools'])
default_env.Tool('Data', toolpath=['site_scons/site_tools'])
default_env.Tool('UnitTest', toolpath=['site_scons/site_tools'])

if default_env['PLATFORM']=='win32':
    #default_env['ENV']['PATH'] += "C:\Program Files/Microsoft Visual Studio 10.0/VC/bin/"
    print "1"
    os.system("\"c:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat\"")
    print "2"
else:
    default_env['ENV']['PATH'] = '/usr/local/bin:/opt/local/bin:/opt/local/sbin:/usr/bin:/bin:/Developer/usr/bin' 
    default_env['ENV']['PKG_CONFIG_PATH'] = '/usr/local/lib/pkgconfig:/usr/local/lib64/pkgconfig'
    print default_env['ENV']['PATH']



sconsFilesList = [
#third party
"./3rdParty/freetype/SConscript",
"./3rdParty/il/SConscript",
"./3rdParty/libfreenect/SConscript",
"./3rdParty/zlib/SConscript",
"./3rdParty/libpng/SConscript",
"./3rdParty/opencv/SConscript",
"./3rdParty/opengl/SConscript",
"./3rdParty/openal/SConscript",
"./3rdParty/ogg/SConscript",
"./3rdParty/ogre/SConscript",
"./3rdParty/ois/SConscript",
"./3rdParty/vorbis/SConscript",
"./3rdParty/glew/SConscript",
"./3rdParty/sdl/SConscript",
"./3rdParty/pthread/SConscript",

#libs

"./lib/gcl/gcl/SConscript",
"./lib/tanklib/SConscript",
#tools
"./program/tools/common/SConscript",
"./program/tools/common/unittest/SConscript",

"./program/tools/meshconverter/SConscript",

#tools unittest

"./lib/gcl/gcl/unittest/SConscript",
"./lib/tanklib/unittest/SConscript",


#unittest

#programs
"./program/tank/SConscript",
]
if GetOption('genValgrindSuppressions'):
    sconsFilesList.append("./tools/valgrindgen/SConscript") #this tool generates some rules for valgrind so that it ignores certain pattern of memory errors that we don't care about

#default_env.StampTime("start SConscript Parse...")
default_env.SConsWalkList(sconsFilesList, './SConscript', variant)
default_env.StampTime("Parsing Time")
if "@aliases" in targetList:
    default_env.displayAliases()
    sys.exit()

def OnExit():
    default_env.StampTime("exit")

atexit.register(OnExit)
