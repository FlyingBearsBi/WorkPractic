#include "geometry.h"

//计算质心坐标
Vector3D Barycentric(Vector3D A, Vector3D B, Vector3D C, Vector3D P)
{
    Vector3D Vec[2];
    Vec[0].x = B.x - A.x;
    Vec[0].y = C.x - A.x;
    Vec[0].z = A.x - P.x;
    Vec[1].x = B.y - A.y;
    Vec[1].y = C.y - A.y;
    Vec[1].z = A.y - P.y;
    Vector3D u = Vec[0].cross(Vec[1]);
    if (u.z > 0)
    {
        return Vector3D(1.0f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
    }
    return Vector3D(-1, 1, 1);
}