//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_MESHMANAGER_H
#define BETOENGINE_MESHMANAGER_H

#pragma once

#include <vector>

#include "Mesh.h"

class MeshManager {
    public:
        static std::vector<Mesh*> m_meshes;
};
#endif //BETOENGINE_MESHMANAGER_H