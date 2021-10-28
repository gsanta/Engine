#ifndef PROJ_H
#define PROJ_H

#include <glm/glm.hpp>

class Proj {

public:
    Proj();
    ~Proj();

    glm::mat4& getProjectionMatrix() {
        return projectionMat;        
    }

protected:
    glm::mat4 projectionMat;
};

#endif