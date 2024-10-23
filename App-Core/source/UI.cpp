#include "UI.h"
#include "Application.h"

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

using namespace Core;

namespace UI
{
    static bool uiInitialized = false;

    void UISetup()
    {
        if (uiInitialized)
        {
            TraceLog(LOG_ERROR, "UI cannot be initialized more than once!");
            return;
        }

        rlImGuiSetup(true);
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        uiInitialized = true;
    }

    void UIShutdown()
    {
        rlImGuiShutdown();
    }

    void UIBeginFrame()
    {
        rlImGuiBegin();
    }

    void UIEndFrame()
    {
        rlImGuiEnd();
    }

    ImVec2 GetLargestSizeForViewport()
    {
        const ApplicationSpecification& appInfo = App->GetSpecification();
        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        windowSize.x -= ImGui::GetScrollX();
        windowSize.y -= ImGui::GetScrollY();

        float aspect = (float)appInfo.windowWidth / appInfo.windowHeight;
        float aspectWidth = windowSize.x;
        float aspectHeight = aspectWidth / aspect;

        if (aspectHeight > windowSize.y)
        {
            aspectHeight = windowSize.y;
            aspectWidth = aspectHeight * aspect;
        }

        return ImVec2(aspectWidth, aspectHeight);
    }

    ImVec2 GetViewportCenteredPosition(ImVec2 aspectSize)
    {
        const ApplicationSpecification& appInfo = App->GetSpecification();
        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        windowSize.x -= ImGui::GetScrollX();
        windowSize.y -= ImGui::GetScrollY();

        ImVec2 viewportPosition;
        viewportPosition.x = (windowSize.x / 2.f) - (aspectSize.x / 2.f);
        viewportPosition.y = (windowSize.y / 2.f) - (aspectSize.y / 2.f);
        viewportPosition.x += ImGui::GetCursorPosX();
        viewportPosition.y += ImGui::GetCursorPosY();

        return viewportPosition;
    }

}
