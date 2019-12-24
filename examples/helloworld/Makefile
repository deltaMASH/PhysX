CXX = clang++

PHYSX_ROOT = ../..

INC = $(PHYSX_ROOT)/PxShared/include \
	$(PHYSX_ROOT)/PxShared/src/foundation/include \
	$(PHYSX_ROOT)/PhysX_3.4/Include
INC_PARAMS = $(foreach d, $(INC), -I$d)
STATIC_LIB_DIR = -L$(PHYSX_ROOT)/PhysX_3.4/Bin/linux64 -L$(PHYSX_ROOT)/PxShared/bin/linux64
LIB = PxFoundationDEBUG_x64 PxPvdSDKDEBUG_x64 PhysX3DEBUG_x64 PhysX3CharacterKinematicDEBUG_x64 PhysX3CommonDEBUG_x64 PhysX3CookingDEBUG_x64
LIB_PARAMS = $(foreach d, $(LIB), -l$d)
STATIC_LIBS = $(PHYSX_ROOT)/PhysX_3.4/Lib/linux64/libPhysX3Extensions.a

all: helloworld

helloworld: main.cpp
	$(CXX) -g $(INC_PARAMS) $(LIB_PARAMS) $(STATIC_LIB_DIR) -o helloworld main.cpp $(STATIC_LIBS)

