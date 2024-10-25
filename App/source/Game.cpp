#include "Game.h"

#include <Application.h>
#include <Entity.h>
#include <EntityManager.h>
#include <Lights.h>
#include <UI.h>

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

using namespace Core;
using namespace Scene;
using namespace UI;

static bool gridEnabled = true;

static Model model;
static DirectionalLight directionalLight;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    m_camera.position = (v3){-5.f, 3.f, 10.f};
    m_camera.target = (v3){0.f, 0.f, 0.f};
    m_camera.up = (v3){0.f, 1.f, 0.f};
    m_camera.projection = CAMERA_PERSPECTIVE;
    m_camera.fovy = 45.f;

    directionalLight = CreateDirectionalLight((v3){0.3f, -1.f, 0.f}, (v3){0.8f, 0.8f, 0.8f}, 1.f);

    model = LoadModelFromMesh(GenMeshTorus(0.4f, 2.f, 16, 32));
    model.materials[0].shader = this->GetDefaultShader();

    // this->SetPrimaryCamera(&m_camera);
}

void Game::OnUpdate()
{
    this->SetPrimaryCameraLock(true);
    UpdateDirectionalLight(directionalLight);

    if (IsKeyPressed(KEY_F1))
        gridEnabled = !gridEnabled;
}

void Game::OnRender()
{
    if (gridEnabled)
        DrawGrid(50, 1.f);

    DrawModel(model, (v3){0.f, 0.f, 0.f}, 1.f, WHITE);
}

void Game::OnRenderUI()
{
    const ApplicationSpecification& appInfo = this->GetSpecification();

    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    {
        const RenderTexture& framebuffer = this->GetFramebuffer();
        ImVec2 aspectSize = GetLargestSizeForViewport();
        ImVec2 windowPosition = GetViewportCenteredPosition(aspectSize);

        ImGui::SetCursorPos(windowPosition);

        Rectangle source;
        source.x = 0.f;
        source.y = 0.f;
        source.width = framebuffer.texture.width;
        source.height = -framebuffer.texture.height;
        rlImGuiImageRect(&framebuffer.texture, aspectSize.x, aspectSize.y, source);

        if (ImGui::IsWindowHovered() && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            this->SetPrimaryCameraLock(false);
    }
    ImGui::End();

    ImGui::ShowDemoWindow();

    ImGui::Begin("Lighting Properties");
    {
        ImGui::DragFloat3("Direction", &directionalLight.direction.x, 0.01f, -1.f, 1.f);
        ImGui::ColorEdit3("Color", &directionalLight.color.x);
        ImGui::DragFloat("Intensity", &directionalLight.intensity, 0.01f);
    }
    ImGui::End();
}

void Game::OnShutdown()
{
    UnloadModel(model);
}
