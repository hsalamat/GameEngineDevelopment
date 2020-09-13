# Install script for directory: C:/Hooman/GBC/GAME3121/ogre/OgreMain

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/Release/OgreMain.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Release/OgreMain.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/RelWithDebInfo/OgreMain.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/RelWithDebInfo/OgreMain.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/MinSizeRel/OgreMain.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/MinSizeRel/OgreMain.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Hooman/GBC/GAME3121/ogre/build/lib/Debug/OgreMain_d.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Debug/OgreMain_d.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/Debug/OgreMain_d.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Hooman/GBC/GAME3121/ogre/build/bin/RelWithDebInfo/OgreMain.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE" TYPE FILE FILES
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Ogre.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreASTCCodec.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAlignedAllocator.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAnimable.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAnimation.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAnimationState.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAnimationTrack.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAny.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreArchive.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreArchiveFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreArchiveManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAtomicScalar.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAutoParamDataSource.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreAxisAlignedBox.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBillboard.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBillboardChain.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBillboardParticleRenderer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBillboardSet.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBitwise.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBlendMode.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreBone.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCamera.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCodec.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreColourValue.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCommon.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositionPass.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositionTargetPass.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositionTechnique.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositor.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositorChain.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositorInstance.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositorLogic.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCompositorManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreConfig.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreConfigDialog.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreConfigFile.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreConfigOptionMap.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreController.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreControllerManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreConvexBody.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreCustomCompositionPass.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDataStream.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDefaultHardwareBufferManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDeflate.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDepthBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDistanceLodStrategy.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDualQuaternion.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDynLib.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDynLibManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreEdgeListBuilder.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreEntity.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreException.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreExternalTextureSource.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreExternalTextureSourceManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreFactoryObj.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreFileSystem.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreFileSystemLayer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreFrameListener.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreFrustum.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreGpuProgram.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreGpuProgramManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreGpuProgramParams.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreGpuProgramUsage.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareBufferManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareCounterBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareIndexBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareOcclusionQuery.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwarePixelBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareUniformBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHardwareVertexBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHeaderPrefix.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHeaderSuffix.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHighLevelGpuProgram.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreHighLevelGpuProgramManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreImage.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreImageCodec.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstanceBatch.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstanceBatchHW.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstanceBatchHW_VTF.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstanceBatchShader.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstanceBatchVTF.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstanceManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreInstancedEntity.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreIteratorWrapper.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreIteratorWrappers.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreKeyFrame.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreLight.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreLodListener.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreLodStrategy.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreLodStrategyManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreLog.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreLogManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreManualObject.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMaterial.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMaterialManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMaterialSerializer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMath.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMatrix3.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMatrix4.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMemoryAllocatorConfig.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMesh.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMeshFileFormat.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMeshManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMeshSerializer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMovableObject.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMovablePlane.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreMurmurHash3.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreNameGenerator.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreNode.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreNumerics.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreOptimisedUtil.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticle.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleAffector.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleAffectorFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleEmitter.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleEmitterFactory.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleIterator.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleSystem.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleSystemManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreParticleSystemRenderer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePass.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePatchMesh.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePatchSurface.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePixelCountLodStrategy.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePixelFormat.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePlane.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePlaneBoundedVolume.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePlatform.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePlatformInformation.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePlugin.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePolygon.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePose.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePredefinedControllers.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgrePrerequisites.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreProfiler.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreQuaternion.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRadixSort.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRay.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRectangle2D.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderObjectListener.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderOperation.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderQueue.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderQueueInvocation.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderQueueListener.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderQueueSortingGrouping.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderSystem.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderSystemCapabilities.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderSystemCapabilitiesManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderSystemCapabilitiesSerializer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderTarget.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderTargetListener.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderTexture.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderToVertexBuffer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderWindow.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRenderable.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreResource.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreResourceBackgroundQueue.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreResourceGroupManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreResourceManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRibbonTrail.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRoot.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreRotationalSpline.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSceneLoader.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSceneLoaderManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSceneManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSceneManagerEnumerator.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSceneNode.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSceneQuery.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreScriptCompiler.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreScriptLoader.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreScriptTranslator.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSearchOps.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSerializer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreShadowCameraSetup.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreShadowCameraSetupFocused.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreShadowCameraSetupLiSPSM.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreShadowCameraSetupPSSM.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreShadowCameraSetupPlaneOptimal.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreShadowCaster.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSharedPtr.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSimpleRenderable.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSimpleSpline.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSingleton.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSkeleton.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSkeletonFileFormat.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSkeletonInstance.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSkeletonManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSkeletonSerializer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSphere.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStaticFaceGroup.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStaticGeometry.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStdHeaders.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStreamSerialiser.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreString.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStringConverter.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStringInterface.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreStringVector.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSubEntity.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreSubMesh.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTagPoint.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTangentSpaceCalc.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTechnique.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTexture.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTextureManager.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTextureUnitState.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreTimer.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreUnifiedHighLevelGpuProgram.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreUserObjectBindings.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreVector.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreVector2.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreVector3.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreVector4.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreVertexBoneAssignment.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreVertexIndexData.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreViewport.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreWireBoundingBox.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreWorkQueue.h"
    "C:/Hooman/GBC/GAME3121/ogre/build/include/OgreBuildSettings.h"
    "C:/Hooman/GBC/GAME3121/ogre/build/include/OgreComponents.h"
    "C:/Hooman/GBC/GAME3121/ogre/build/include/OgreExports.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Ogre.i"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueue.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueueStandard.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueueTBB.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefines.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesBoost.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesNone.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesPoco.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesTBB.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeaders.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersBoost.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersPoco.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersTBB.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueueStandard.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreDDSCodec.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreETCCodec.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreASTCCodec.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/OgreZip.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/Threading" TYPE FILE FILES
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueue.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueueStandard.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueueTBB.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefines.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesBoost.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesNone.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesPoco.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesTBB.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeaders.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersBoost.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersPoco.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersTBB.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadDefinesSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreThreadHeadersSTD.h"
    "C:/Hooman/GBC/GAME3121/ogre/OgreMain/include/Threading/OgreDefaultWorkQueueStandard.h"
    )
endif()

