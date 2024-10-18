#pragma once
#include <raylib.h>
#include <string>
#include <vector>

namespace Scene
{
    struct TransformComponent
    {
        bool isEnabled = false;
        Vector2 position;
        float rotation;
        Vector2 scale;

        TransformComponent()
        {
            position = {0.f, 0.f};
            rotation = 0.f;
            scale = {1.f, 1.f};
        }

        TransformComponent(Vector2 position, float rotation, Vector2 scale)
        {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }
    };
}
