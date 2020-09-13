# Install script for directory: C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/Release/OgreRTShaderSystem.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Release/OgreRTShaderSystem.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/RelWithDebInfo/OgreRTShaderSystem.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/RelWithDebInfo/OgreRTShaderSystem.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/MinSizeRel/OgreRTShaderSystem.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/MinSizeRel/OgreRTShaderSystem.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/Debug/OgreRTShaderSystem_d.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Debug/OgreRTShaderSystem_d.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Debug/OgreRTShaderSystem_d.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/RelWithDebInfo/OgreRTShaderSystem.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RTShaderSystem" TYPE FILE FILES
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreRTShaderSystem.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderCGProgramProcessor.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderCGProgramWriter.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExDualQuaternionSkinning.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExGBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExHardwareSkinning.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExHardwareSkinningTechnique.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExIntegratedPSSM3.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExLayeredBlending.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExLinearSkinning.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExNormalMapLighting.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExPerPixelLighting.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExTextureAtlasSampler.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderExTriplanarTexturing.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPAlphaTest.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPColour.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPFog.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPLighting.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPRenderState.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPRenderStateBuilder.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPTexturing.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFFPTransform.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFunction.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderFunctionAtom.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderGLSLESProgramProcessor.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderGLSLESProgramWriter.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderGLSLProgramProcessor.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderGLSLProgramWriter.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderGenerator.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderHLSLProgramProcessor.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderHLSLProgramWriter.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderParameter.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderPrerequisites.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderProgram.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderProgramManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderProgramProcessor.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderProgramSet.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderProgramWriter.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderProgramWriterManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderRenderState.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderScriptTranslator.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreShaderSubRenderState.h"
    "C:/Hooman/GBC/GAME3121/ogre/build/include/OgreRTShaderExports.h"
    "C:/Hooman/GBC/GAME3121/ogre/build/include/OgreRTShaderConfig.h"
    "C:/Hooman/GBC/GAME3121/ogre/Components/RTShaderSystem/include/OgreRTShader.i"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Media/" TYPE DIRECTORY FILES "C:/Hooman/GBC/GAME3121/ogre/Media/RTShaderLib")
endif()

