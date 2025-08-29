#include "UserInterface.h"

#include "Event.h"
#include "EventDispatcher.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

SOLAR::UserInterface::UserInterface(GLFWwindow* window) : window(window)
{
	cameraModes = {"Free Cam", "Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

SOLAR::UserInterface::~UserInterface()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void SOLAR::UserInterface::ShowHint()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	ImGui::SetNextWindowPos(ImVec2(width * 0.3f, height * 0.8f), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowBgAlpha(0.9f); // A bit translucent

	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;

	if (ImGui::Begin("Hint", nullptr, flags))
	{
		ImGui::TextUnformatted("In the Free Look mode W,A,S,D to move.");
		ImGui::TextUnformatted("Hold Left Mouse button to Look around.");
		ImGui::TextUnformatted("Planet mode locks the movement but still allows you to look around.");
	}
	ImGui::End();
}

void SOLAR::UserInterface::CameraModePicker()
{
	ImGui::SetNextWindowBgAlpha(0.9f); // A bit translucent
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;

	if (ImGui::Begin("Camera Mode Picker", nullptr, flags))
	{
		// 3 columns (for a 3-wide grid)
		if (ImGui::BeginTable("grid", 2))
		{
			for (int row = 0; row < 6; row++)
			{
				ImGui::TableNextRow();
				for (int col = 0; col < 2; col++)
				{
					ImGui::TableSetColumnIndex(col);

					int id = row * 2 + col + 1;
					if (id > cameraModes.size())
					{
						break;
					}

					char label[32];
					sprintf(label, cameraModes.at(id - 1).c_str());

					if (ImGui::Button(label, ImVec2(150, 40)))
					{
						// Handle button press
						EventDispatcher::Get().Broadcast(GuiButtonPressedEvent(id));
					}
				}
			}
			ImGui::EndTable();
		}
	}
	ImGui::End();
}
