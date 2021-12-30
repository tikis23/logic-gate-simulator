#include "ImGuiManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_stdlib.h"

#include "WindowManager.h"
#include "Input.h"
#include "Settings.h"

void ImGuiManager::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow("main")->GetHandle(), true);
	ImGui_ImplOpenGL2_Init();
	ImGui::GetIO().IniFilename = NULL;
}

void ImGuiManager::Exit()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool ImGuiManager::Update()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	bool hovered = false;
	if (ImGui::Begin("Settings"))
	{
		if (ImGui::InputInt("Current Map ID", &Settings::currentMapID))
		{
			if (CircuitManager::managers.find(Settings::currentMapID) == CircuitManager::managers.end())
				Settings::currentMapID = 0;
		}
		if (ImGui::BeginListBox("Circuits"))
		{
			// custom
			ImGui::Text("Custom");
			if (ImGui::Button("Custom"))
				CreateDefinedCircuit(DefinedCircuit::CUSTOM);

			// gates
			ImGui::Text("Gates");
			if (ImGui::Button("AND"))
				CreateDefinedCircuit(DefinedCircuit::AND);
			if (ImGui::Button("NAND"))
				CreateDefinedCircuit(DefinedCircuit::NAND);
			if (ImGui::Button("OR"))
				CreateDefinedCircuit(DefinedCircuit::OR);
			if (ImGui::Button("NOR"))
				CreateDefinedCircuit(DefinedCircuit::NOR);
			if (ImGui::Button("XOR"))
				CreateDefinedCircuit(DefinedCircuit::XOR);
			if (ImGui::Button("XNOR"))
				CreateDefinedCircuit(DefinedCircuit::XNOR);
			if (ImGui::Button("NOT"))
				CreateDefinedCircuit(DefinedCircuit::NOT);

			// clocks
			ImGui::Text("Clocks");
			if (ImGui::Button("Clock60Hz"))
				CreateDefinedCircuit(DefinedCircuit::Clock60Hz);
			if (ImGui::Button("Clock30Hz"))
				CreateDefinedCircuit(DefinedCircuit::Clock30Hz);
			if (ImGui::Button("Clock15Hz"))
				CreateDefinedCircuit(DefinedCircuit::Clock15Hz);

			// misc
			ImGui::Text("Misc");
			if (ImGui::Button("LED"))
				CreateDefinedCircuit(DefinedCircuit::LED);
			if (ImGui::Button("ButtonPress"))
				CreateDefinedCircuit(DefinedCircuit::ButtonPress);
			if (ImGui::Button("ButtonHold"))
				CreateDefinedCircuit(DefinedCircuit::ButtonHold);
			if(ImGui::Button("ConstantTrue"))
				CreateDefinedCircuit(DefinedCircuit::ConstantTrue);
			if(ImGui::Button("ConstantFalse"))
				CreateDefinedCircuit(DefinedCircuit::ConstantFalse);
			if (ImGui::Button("InputNode"))
				CreateDefinedCircuit(DefinedCircuit::InputNode);
			if (ImGui::Button("OutputNode"))
				CreateDefinedCircuit(DefinedCircuit::OutputNode);
			ImGui::EndListBox();
		}


		if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
			hovered = true;
		ImGui::End();
	}


	if (Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::RIGHT, Input::Action::PRESS))
	{
		deletableCircuit = Circuit::hovered;
		ImGui::OpenPopup("Popup");
	}

	if (ImGui::BeginPopup("Popup"))
	{
		if(deletableCircuit != nullptr && ImGui::Button("Delete"))
		{
			CircuitManager::managers[Settings::currentMapID]->RemoveCircuit(deletableCircuit);
			deletableCircuit = nullptr;
			ImGui::CloseCurrentPopup();
		}
		if (deletableCircuit != nullptr && ImGui::Button("Duplicate"))
		{
			DuplicateDefinedCircuit(CircuitManager::managers[Settings::currentMapID]->circuits[deletableCircuit].type, CircuitManager::managers[Settings::currentMapID]->circuits[deletableCircuit].pointer);
			deletableCircuit = nullptr;
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Enter Edit Mode"))
		{
			if (deletableCircuit != nullptr && CircuitManager::managers[Settings::currentMapID]->circuits[deletableCircuit].type == DefinedCircuit::CUSTOM)
			{
				editingCircuit = (CUSTOM*)CircuitManager::managers[Settings::currentMapID]->circuits[deletableCircuit].pointer;
				editingCircuit->EnterEditMode();
			}
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Exit Edit Mode"))
		{
			if (editingCircuit != nullptr)
			{
				editingCircuit->ExitEditMode();
				editingCircuit = nullptr;
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	return hovered;
}

void ImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

Circuit* ImGuiManager::deletableCircuit = nullptr;
CUSTOM* ImGuiManager::editingCircuit = nullptr;