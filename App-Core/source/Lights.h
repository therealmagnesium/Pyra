#pragma once
#include "Base.h"
#include <raylib.h>

namespace Scene
{
    enum DirectionalLightLoc
    {
        LIGHT_DIR_LOC_DIRECTION = 0,
        LIGHT_DIR_LOC_COLOR,
        LIGHT_DIR_LOC_INTENSITY,
        LIGHT_DIR_LOC_COUNT,
    };

    struct DirectionalLight
    {
        Vector3 direction;
        Vector3 color;
        float intensity;
        Shader shader;

        u32 locations[LIGHT_DIR_LOC_COUNT];
    };

    DirectionalLight CreateDirectionalLight(v3 direction, v3 color, float intensity);
    void UpdateDirectionalLight(DirectionalLight& light);

}
