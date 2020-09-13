# Install script for directory: C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Hooman/GBC/GAME3121/ogre/build/sdk")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OGRE" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/Release/Plugin_ParticleFX.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Release/Plugin_ParticleFX.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OGRE" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/RelWithDebInfo/Plugin_ParticleFX.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/RelWithDebInfo/Plugin_ParticleFX.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OGRE" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/MinSizeRel/Plugin_ParticleFX.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/MinSizeRel/Plugin_ParticleFX.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OGRE" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/Debug/Plugin_ParticleFX_d.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Debug/Plugin_ParticleFX_d.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Debug/Plugin_ParticleFX_d.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/RelWithDebInfo/Plugin_ParticleFX.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/Plugins/ParticleFX" TYPE FILE FILES
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreAreaEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreBoxEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreBoxEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourFaderAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourFaderAffector2.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourFaderAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourFaderAffectorFactory2.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourImageAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourImageAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourInterpolatorAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreColourInterpolatorAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreCylinderEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreCylinderEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreDeflectorPlaneAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreDeflectorPlaneAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreDirectionRandomiserAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreDirectionRandomiserAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreEllipsoidEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreEllipsoidEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreHollowEllipsoidEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreHollowEllipsoidEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreLinearForceAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreLinearForceAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreParticleFXPlugin.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgrePointEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgrePointEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreRingEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreRingEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreRotationAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreRotationAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreScaleAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/PlugIns/ParticleFX/include/OgreScaleAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/build/include/OgreParticleFXPrerequisites.h"
    )
endif()

