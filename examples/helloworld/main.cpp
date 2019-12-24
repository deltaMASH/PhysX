#ifndef _DEBUG
#define _DEBUG
#endif

#include <foundation/PxFoundation.h>
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>
#include <extensions/PxDefaultErrorCallback.h>
#include <iostream>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->release(); (p)=NULL; }}
#endif

using namespace physx;

void fatalError(const std::string& msg)
{
  std::cerr << "Fatal Error in application: " << msg << std::endl;
  std::exit(1);
}

int main(int argc, char** argv)
{
  PxDefaultAllocator defaultAllocator_;
  static PxDefaultErrorCallback defaultErrorCallback_;
  PxFoundation* foundation_;
  PxPhysics* physics_;
  PxPvd* pvd_;
  PxScene* scene_;
  PxCooking* cooking_;

  physx::PxAllocatorCallback* allocator = &defaultAllocator_;
  foundation_ = PxCreateFoundation(PX_FOUNDATION_VERSION, *allocator, defaultErrorCallback_);
  if (!foundation_)
    fatalError("PxCreateFoundation failed!");

  physx::PxTolerancesScale scale;
  // customizeTolerances(scale);

  physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation_, scale);
  if (!physics_)
    fatalError("PxCreatePhysics failed!");
  
  PxCookingParams params(scale);
  params.meshWeldTolerance = 0.001f;
  params.meshPreprocessParams = PxMeshPreprocessingFlags(PxMeshPreprocessingFlag::eWELD_VERTICES);
  params.buildGPUData = true;
  
  PxSceneDesc sceneDesc(physics_->getTolerancesScale());
  sceneDesc.gravity = PxVec3(0.0f, 0.0f, -9.81f);
  scene_ = physics_->createScene(sceneDesc);
  if (!physics_)
    fatalError("createScene failed!");

  cooking_ = PxCreateCooking(PX_PHYSICS_VERSION, *foundation_, params);
  if (!cooking_)
    fatalError("PxCreateCooking failed!");
  
  std::cout << "Initialize success!\n";

  // shutdown
  SAFE_RELEASE(scene_);
  SAFE_RELEASE(cooking_);
  SAFE_RELEASE(physics_);
  SAFE_RELEASE(foundation_);
}
