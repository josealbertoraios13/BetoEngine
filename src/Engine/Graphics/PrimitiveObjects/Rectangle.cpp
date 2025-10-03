//
// Created by jose_alberto on 03/10/2025.
//

#include "../../../../include/Engine/Graphics/PrimitiveObjects/Rectangle.h"

Rectangle::Rectangle() : Mesh({-0.5f, 0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                               0.5f, -0.5f, 0.0f}) {
    SetName("newRectangle");
}
