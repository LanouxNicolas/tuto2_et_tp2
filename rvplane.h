#ifndef RVPLANE_H
#define RVPLANE_H
#include "rvbody.h"

class RVPlane : public RVBody
{
public:
    RVPlane();
    void draw() override;
    QMatrix4x4 modelMatrix() override;

protected:
    void initializeBuffer() override;

private:
    int x;
    int z;
};
#endif // RVPLANE_H
