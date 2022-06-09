#pragma once
#include "WorldTransform.h"

namespace affinMove {
void Scale(WorldTransform &worldTransform); 

void Rotate(WorldTransform &worldTransform);

void Translate(WorldTransform &worldTransform);

void Transform(WorldTransform &worldTransform);
}