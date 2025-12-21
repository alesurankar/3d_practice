#pragma once
#include "GeometryFlatEffect.h"
#include "SolidGeometryEffect.h"
#include "VertexFlatEffect.h"
#include "GouraudEffect.h"
#include "GouraudPointEffect.h"
#include "PhongPointEffect.h"
#include "SolidEffect.h"


using SceneEffect = PhongPointEffect;
using SceneVertex = SceneEffect::Vertex;

using SolidVertex = SolidEffect::Vertex;