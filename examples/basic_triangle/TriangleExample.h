//
// Created by jose_alberto on 03/10/2025.
//

#ifndef BETOENGINE_TRIANGLEEXAMPLE_H
#define BETOENGINE_TRIANGLEEXAMPLE_H
#include "../../include/Engine.h"


class TriangleExample : public Engine {
    public:
        TriangleExample() = default;
        ~TriangleExample() override = default;

        void Start() override;
        void Update(float deltaTime) override;
};


#endif //BETOENGINE_TRIANGLEEXAMPLE_H