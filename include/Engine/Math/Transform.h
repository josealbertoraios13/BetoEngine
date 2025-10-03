//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_TRANSFORM_H
#define BETOENGINE_TRANSFORM_H

#include <glm/glm.hpp>
class Transform {
    public:
    //Local
    glm::vec3 localPosition{0.f};
    glm::vec3 localRotation{0.f}; //Em graus
    glm::vec3 localScale{1.f};

    //Global
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};

    glm::mat4 localMatrix{1.0f};
    glm::mat4 worldMatrix{1.0f};
};

#endif //BETOENGINE_TRANSFORM_H