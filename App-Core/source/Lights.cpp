#include "Lights.h"
#include "Base.h"
#include "Application.h"

#include <raylib.h>

using namespace Core;

namespace Scene
{
    DirectionalLight CreateDirectionalLight(v3 direction, v3 color, float intensity)
    {
        DirectionalLight light;
        light.direction = direction;
        light.color = color;
        light.intensity = intensity;
        light.shader = App->GetDefaultShader();

        if (light.shader.id != 0)
        {
            light.locations[LIGHT_DIR_LOC_DIRECTION] = GetShaderLocation(light.shader, "directionalLight.direction");
            light.locations[LIGHT_DIR_LOC_COLOR] = GetShaderLocation(light.shader, "directionalLight.color");
            light.locations[LIGHT_DIR_LOC_INTENSITY] = GetShaderLocation(light.shader, "directionalLight.intensity");
        }

        return light;
    }

    void UpdateDirectionalLight(DirectionalLight& light)
    {
        if (light.shader.id != 0)
        {
            SetShaderValue(light.shader, light.locations[LIGHT_DIR_LOC_DIRECTION], &light.direction, SHADER_UNIFORM_VEC3);
            SetShaderValue(light.shader, light.locations[LIGHT_DIR_LOC_COLOR], &light.color, SHADER_UNIFORM_VEC3);
            SetShaderValue(light.shader, light.locations[LIGHT_DIR_LOC_INTENSITY], &light.intensity, SHADER_UNIFORM_FLOAT);
        }
    }
}
