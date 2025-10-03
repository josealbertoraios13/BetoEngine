//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_ELLIPSE_H
#define BETOENGINE_ELLIPSE_H

#include "../Mesh.h"

class Ellipse : public Mesh{
    public:
        Ellipse();

    protected:
        void Render() const override;
};

#endif //BETOENGINE_ELLIPSE_H