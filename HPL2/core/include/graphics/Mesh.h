/*
 * Copyright © 2011-2020 Frictional Games
 *
 * This file is part of Amnesia: A Machine For Pigs.
 *
 * Amnesia: A Machine For Pigs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Amnesia: A Machine For Pigs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Amnesia: A Machine For Pigs.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HPL_MESH_H
#define HPL_MESH_H

#include <vector>
#include <map>

#include "math/MathTypes.h"
#include "graphics/GraphicsTypes.h"
#include "system/SystemTypes.h"
#include "resources/ResourceBase.h"

#include "scene/Light.h"

namespace hpl {

	class cMaterialManager;
	class cAnimationManager;
	class cSubMesh;
	class cMeshEntity;
	class cSkeleton;
	class cAnimation;
	class cNode3D;
	class iCollideShape;
	class iPhysicsWorld;
	class iPhysicsBody;
	class iPhysicsJoint;
	class cBillboard;
	class cBeam;
	class cParticleSystem;
	class cSoundEntity;
	class cWorld;

	//--------------------------------------------------

	typedef std::vector<cAnimation*> tAnimationVec;
	typedef tAnimationVec::iterator tAnimationVecIt;

	typedef std::map<tString, int> tAnimationIndexMap;
	typedef tAnimationIndexMap::iterator tAnimationIndexMapIt;

	typedef std::vector<cSubMesh*> tSubMeshVec;
	typedef std::vector<cSubMesh*>::iterator tSubMeshVecIt;

	typedef std::multimap<tString,cSubMesh*> tSubMeshMap;
	typedef tSubMeshMap::iterator tSubMeshMapIt;

	typedef std::vector<cNode3D*> tNode3DVec;
	typedef tNode3DVec::iterator tNode3DVecIt;

	//--------------------------------------------------

	class cMesh : public iResourceBase
	{
	friend class cSubMesh;
	friend class cMeshEntity;
	public:
		cMesh(const tString& asName, const tWString& asFullPath, cMaterialManager* apMaterialManager, cAnimationManager * apAnimationManager);
		~cMesh();

		bool CreateFromFile(const tString asFile);

		cSubMesh* CreateSubMesh(const tString &asName);

		cSubMesh* GetSubMesh(size_t alIdx);
		int GetSubMeshIndex(const tString &asName);
		cSubMesh* GetSubMeshName(const tString &asName);
		size_t GetSubMeshNum();

		int GetTriangleCount();

		void SetSkeleton(cSkeleton* apSkeleton);
		cSkeleton* GetSkeleton();

		void AddAnimation(cAnimation *apAnimation);

		cAnimation* GetAnimation(int alIndex);
		cAnimation* GetAnimationFromName(const tString& asName);
        int GetAnimationIndex(const tString& asName);

		void ClearAnimations(bool abDeleteAll);

		size_t GetAnimationNum();

		void CompileBonesAndSubMeshes();

		float GetBoneBoundingRadius(int alIdx){ return mvBoneBoundingRadii[alIdx];}

		//Node
		cNode3D* GetRootNode();
		void AddNode(cNode3D* apNode);
		int GetNodeNum();
		cNode3D* GetNode(int alIdx);
		cNode3D* GetNodeByName(const tString &asName);


		//Resources implementation
		bool Reload(){ return false;}
		void Unload(){}
		void Destroy(){}

	private:
		cMaterialManager* mpMaterialManager;
		cAnimationManager * mpAnimationManager;

		tSubMeshVec mvSubMeshes;
		tSubMeshMap m_mapSubMeshes;

		cSkeleton *mpSkeleton;

		tAnimationVec mvAnimations;
		tAnimationIndexMap m_mapAnimIndices;

		tFloatVec mvBoneBoundingRadii;

		cNode3D *mpRootNode;
        tNode3DVec mvNodes;
	};

};
#endif // HPL_MESH_H
