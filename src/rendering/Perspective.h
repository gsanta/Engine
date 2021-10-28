#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "Proj.h"

struct PerspectiveOptions {
    float fieldOfView;
    float aspect;
    float zNear;
    float zFar;
};

class Perspective : public Proj {

public:
    Perspective(PerspectiveOptions options);
    ~Perspective();
};

#endif