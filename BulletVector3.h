#pragma once
#include "WorldTransform.h"
#include <math.h>

namespace Vector3Math {
Vector3 diff(Vector3& vecA, Vector3& vecB); //����(A - B)
bool norm(Vector3& vec3);                   //���������߂�
Vector3 Normalize(Vector3& vec3);           //���K��
} // namespace Vector3Math