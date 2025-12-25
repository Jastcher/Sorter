#include "UI.h"
#include "Core/Sounds.h"
#include "Core/frameBuffer.h"
#include "imgui.h"

namespace Template
{

UI::UI(Window* window,
       std::shared_ptr<Sorter> _sorter,
       std::shared_ptr<FrameBuffer> _frameBuffer,
       std::shared_ptr<Renderer> _renderer,
       std::shared_ptr<SoundEngine> _soundEngine)
    : sorter(_sorter), frameBuffer(_frameBuffer), renderer(_renderer), soundEngine(_soundEngine)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking

	ImGui_ImplGlfw_InitForOpenGL(window->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

UI::~UI()
{
}

static inline void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

static inline void RenderUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static inline void MainWindow()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiWindowFlags host_window_flags = 0;
	host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
	    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
	host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("MainWindow", nullptr, host_window_flags);
	ImGui::PopStyleVar(3);
	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
	ImGui::End();
}

static inline void ViewportWindow(UI* UI)
{
	ImGui::Begin("Viewport");
	float viewportWidth = ImGui::GetWindowWidth();
	float viewportHeight = ImGui::GetWindowHeight();

	UI->frameBuffer->Resize(viewportWidth, viewportHeight);

	// Swap the y-coordinates in the ImVec2 to avoid rendering the framebuffer upside down
	ImGui::GetWindowDrawList()->AddImage(
	    (unsigned int*)UI->frameBuffer->textureColorbuffer,
	    ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y),
	    ImVec2(ImGui::GetCursorScreenPos().x + viewportWidth, ImGui::GetCursorScreenPos().y + viewportHeight),

	    ImVec2(0, 1),
	    ImVec2(1, 0));

	ImVec2 mousePos = ImGui::GetMousePos();

	ImGui::End();
}

static float width = 1.0f;
static inline void SettingsWindow(UI* ui)
{
	ImGui::Begin("Settings");

	if(ui->sorter->start) ImGui::BeginDisabled();

	ImGui::Text("Count: ");
	ImGui::SameLine();
	if(ImGui::DragInt("##01", (int*)&ui->sorter->dataSize, 1.0f, 0, 1000000)) { ui->sorter->ResizeData(); }

	ImGui::Text("Render skip: ");
	ImGui::SameLine();
	ImGui::DragInt("##02", (int*)&ui->renderer->renderSkip, 1.0f, 0, glm::pow(2, 16));

	ImGui::Separator();

	ImGui::Text("Algorithm: ");
	ImGui::SameLine();
	ImGui::ListBox("##03", &ui->sorter->sorterSelected, &ui->sorter->sorterNames[0], ui->sorter->sorterNames.size());

	ImGui::Text("Sleep: ");
	ImGui::SameLine();
	ImGui::DragInt("##04", &ui->sorter->props.sleep);

	if(ImGui::Button("Reset")) { ui->sorter->ResizeData(); }
	if(ImGui::Button("Shuffle")) { ui->sorter->ShuffleData(); }

	if(ui->sorter->start)
	{
		ImGui::EndDisabled();
		if(ImGui::Button("Stop")) ui->sorter->props.stop = true;
	}
	else if(ImGui::Button("Sort")) { ui->sorter->start = true; }

	ImGui::Text("Pitch ranges");
	ImGui::SameLine();
	ImGui::DragFloatRange2("##05", &ui->soundEngine->minPitch, &ui->soundEngine->maxPitch, 0.01f);

	ImGui::Text("Volume");
	ImGui::SameLine();
	if(ImGui::SliderFloat("##06", &ui->soundEngine->gain, 0.0f, 1.0f)) ui->soundEngine->SetGain();

	ImGui::End();
}

void UI::Update()
{
	StartFrame();

	MainWindow();
	ViewportWindow(this);
	SettingsWindow(this);

	RenderUI();
}

} // namespace Template
