#include "Game.h"

#include <Application.h>
#include <Entity.h>
#include <EntityManager.h>
#include <UI.h>

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

using namespace Core;
using namespace Scene;
using namespace UI;

Game::Game(ApplicationSpecification& spec) : Application(spec)
{
    const ApplicationSpecification& appInfo = this->GetSpecification();
    DisableCursor();

    m_camera.position = (v3){-5.f, 3.f, 10.f};
    m_camera.target = (v3){0.f, 0.f, 0.f};
    m_camera.up = (v3){0.f, 1.f, 0.f};
    m_camera.projection = CAMERA_PERSPECTIVE;
    m_camera.fovy = 45.f;

    // this->SetPrimaryCamera(&m_camera);
}

void Game::OnUpdate()
{
}

void Game::OnRender()
{
    DrawGrid(50, 1.f);
    DrawCubeV((v3){0.f, 0.f, 0.f}, (v3){2.f, 2.f, 2.f}, BLUE);
}

void Game::OnRenderUI()
{
    const ApplicationSpecification& appInfo = this->GetSpecification();
    DrawFPS(20, 20);

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
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void Game::OnShutdown()
{
}
