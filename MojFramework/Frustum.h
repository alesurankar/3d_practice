#pragma once
#include "MyMath.h"

class FrustumView
{
public:
    static FrustumView BuildViewFrustum(float hfov, float aspect, float nearZ, float farZ)
    {
        FrustumView f;
        f.nearZ = nearZ;
        f.farZ = farZ;
        f.tanHalfHFov = std::tan(to_rad(hfov * 0.5f));
        f.tanHalfVFov = f.tanHalfHFov / aspect;
        return f;
    }
    static bool IsVisible_ViewSpace(const Vec3& centerVS, float radius, const FrustumView& f) noexcept
    {
        radius *= 1.2f;
        // Near / Far
        if (centerVS.z + radius < f.nearZ) return false;
        if (centerVS.z - radius > f.farZ)  return false;

        const float z = centerVS.z;

        // Left / Right
        const float maxX = z * f.tanHalfHFov;
        if (centerVS.x - radius > maxX) return false;
        if (centerVS.x + radius < -maxX) return false;

        // Top / Bottom
        const float maxY = z * f.tanHalfVFov;
        if (centerVS.y - radius > maxY) return false;
        if (centerVS.y + radius < -maxY) return false;

        return true;
    }
private:
    float nearZ;
    float farZ;
    float tanHalfHFov;
    float tanHalfVFov;
};