#pragma once
#include "Base.h"

#include <raylib.h>
#include <string>
#include <vector>

namespace Scene
{
    struct TransformComponent
    {
        bool isEnabled = false;
        Vector3 position = (v3){0.f, 0.f, 0.f};
        Vector3 rotation = (v3){0.f, 0.f, 0.f};
        Vector3 scale = (v3){1.f, 1.f, 1.f};

        TransformComponent() = default;
        TransformComponent(v3 position, v3 rotation, v3 scale)
        {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }
    };

    struct ModelComponent
    {
        bool isEnabled = false;
        Model* model = NULL;
        Color tint = WHITE;

        ModelComponent() = default;
        ModelComponent(Model* model, Color tint)
        {
            this->model = model;
            this->tint = tint;
        }
    };

    struct CameraComponent
    {
        bool isEnabled = false;
        bool isPrimary = false;
        Camera camera;

        CameraComponent() = default;
        CameraComponent(bool isPrimary)
        {
            this->isPrimary = isPrimary;
            this->camera.target = V3_ZERO;
            this->camera.position = (v3){-5.f, 3.f, 10.f};
            this->camera.up = (v3){0.f, 1.f, 0.f};
            this->camera.fovy = 45.f;
        }
    };
}
