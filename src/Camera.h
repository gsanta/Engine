#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {

public:
    Camera(float x, float y, float z);
    ~Camera();


    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }

    glm::mat4& getViewMatrix() {
        return vMat;        
    }
private:
    float x;
    float y;
    float z;
    glm::mat4 vMat;
};

#endif
