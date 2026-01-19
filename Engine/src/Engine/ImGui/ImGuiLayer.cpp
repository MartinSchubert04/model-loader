#include "ImGuiLayer.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEVent.h"
#include "Events/MouseEVent.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "pch.h"

namespace Engine {

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::onAttach() {

  ImGui::CreateContext();

  // setup theme
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking

  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform Windows
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // viewports set up
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

  float fontSize = 18.0f;  // *2.0f;
  io.Fonts->AddFontFromFileTTF("Editor/Assets/Fonts/OpenSans/OpenSans-Bold.ttf", fontSize);
  io.FontDefault = io.Fonts->AddFontFromFileTTF("Editor/Assets/Fonts/OpenSans/OpenSans-Regular.ttf", fontSize);

  ImGuiStyle &style = ImGui::GetStyle();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  Application &app = Application::get();

  GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

  // Después de los Inits
  CORE_INFO("Viewports en Config: {0}", (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");
  CORE_INFO("Platform Viewports: {0}", (io.BackendFlags & ImGuiBackendFlags_PlatformHasViewports) ? "SI" : "NO");
  CORE_INFO("Renderer Viewports: {0}", (io.BackendFlags & ImGuiBackendFlags_RendererHasViewports) ? "SI" : "NO");

  int major, minor, rev;
  glfwGetVersion(&major, &minor, &rev);

  CORE_INFO("GLFW version string: %s", glfwGetVersionString());

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  CORE_INFO("Viewports en Config: {0}", (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");

  ImGui_ImplOpenGL3_Init("#version 460 core");
  CORE_INFO("Viewports en Config: {0}", (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");
}

void ImGuiLayer::onDetach() {
  ImGui::DestroyPlatformWindows();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::onEvent(Event &event) {
  ImGuiIO &io = ImGui::GetIO();

  if (mBlockEvents) {
    event.handled |= event.isInCategory(EventCategoryMouseButton) & io.WantCaptureMouse;
    event.handled |= event.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
  }
}

void ImGuiLayer::begin() {
  ImGuiIO &io = ImGui::GetIO();
  float time = (float)glfwGetTime();
  io.DeltaTime = mTime > 0 ? (time - mTime) : (1.0f / 60.0f);
  mTime = time;

  CORE_INFO("Viewports en Config: {0}", (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");

  ImGui_ImplOpenGL3_NewFrame();  // render
  CORE_INFO("Después de opengl NewFrame → Viewports: {0}",
            (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");
  ImGui_ImplGlfw_NewFrame();  // plataforma
  CORE_INFO("Después de GLFW NewFrame → Viewports: {0}",
            (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");
  ImGui::NewFrame();  // gen new frame

  CORE_INFO("Después de NewFrame → Viewports: {0}",
            (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) ? "SI" : "NO");
}

void ImGuiLayer::end() {
  ImGuiIO &io = ImGui::GetIO();

  Window &window = Application::get().getWindow();
  io.DisplaySize = ImVec2(window.getWidth(), window.getHeight());

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void ImGuiLayer::onImGuiRender() {
  ImGuiIO &io = ImGui::GetIO();

  // Create the docking environment
  // ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
  //                                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
  //                                ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
  //                                ImGuiWindowFlags_NoBackground;

  // ImGuiViewport *viewport = ImGui::GetMainViewport();
  // ImGui::SetNextWindowPos(viewport->Pos);
  // ImGui::SetNextWindowSize(viewport->Size);
  // ImGui::SetNextWindowViewport(viewport->ID);

  // ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  // ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  // ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
  // ImGui::PopStyleVar(3);

  // ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

  // ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

  // ImGui::End();
  // end of Root docking env, all ImGui widget must go under this code

  bool show = true;

  ImGui::ShowDemoWindow(&show);
}

}  // namespace Engine
