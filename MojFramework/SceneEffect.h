#pragma once
//#include "GeometryFlatEffect.h"
//#include "SolidGeometryEffect.h"
//#include "VertexFlatEffect.h"
//#include "GouraudEffect.h"
//#include "GouraudPointEffect.h"
#include "SpecularPhongPointEffect.h"
#include "SolidEffect.h"


using SceneEffect = SpecularPhongPointEffect;
using SceneVertex = SceneEffect::Vertex;

using SolidVertex = SolidEffect::Vertex;