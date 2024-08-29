#include "MainLayer.h"

#include <Walnut/Application.h>
#include <Walnut/UI/UI.h>

#include "Data.h"

MainLayer::MainLayer()
{
	std::ifstream itemsFile("../../items.json");
	if (!itemsFile.is_open())
	{
		std::cerr << "Unable to open file\n";
		return;
	}

	itemsFile >> m_ItemsData;
	itemsFile.close();
	
	for (auto& [name, _] : m_ItemsData.items())
	{
		m_ItemNames.push_back(name);
	}
}

void MainLayer::OnUIRender()
{
	RenderItemsList();
	RenderStatsTable();
	RenderBoughtItems();
}

void MainLayer::RenderItemsList()
{
	ImVec2 size(300, 700);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockLeft"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Items");

	static unsigned int currentItem = 0;

	if (ImGui::BeginListBox(" ", size))
	{
		for (int i = 0; i < m_ItemNames.size(); i++)
		{
			const bool isSelected = (currentItem == i);

			SetTextColor(m_ItemNames[i]);
			if (ImGui::Selectable(m_ItemNames[i].c_str(), isSelected))
			{
				currentItem = i;
			}
			ImGui::PopStyleColor();

			if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered() && isSelected)
			{
				BuyItem(m_ItemNames[i]);
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}

			
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}

void MainLayer::RenderStatsTable()
{
	ImVec2 size(300, 700);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockRight"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Stats");

	if (ImGui::BeginTable("Stats", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed, 325);
		ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 50);
		ImGui::TableHeadersRow();

		for (const auto& name : deadlock::statNames)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("%s", name.c_str());
			ImGui::TableNextColumn();
			ImGui::Text("%d", 0);
		}

		ImGui::EndTable();
	}

	ImGui::End();
}

void MainLayer::RenderBoughtItems()
{
	ImVec2 size(700, 300);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockUp"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Bought Items");

	if (ImGui::BeginListBox(" ", size))
	{
		for (auto& name : m_BoughtItems)
		{
			SetTextColor(name);
			ImGui::Selectable(name.c_str(), false);
			ImGui::PopStyleColor();
		}

		ImGui::EndListBox();
	}

	ImGui::End();
}

void MainLayer::SetTextColor(std::string name)
{
	std::string category = m_ItemsData[name]["category"];

	ImVec4 weaponColor = ImVec4(0.79f, 0.48f, 0.01f, 1.0f);
	ImVec4 vitalityColor = ImVec4(0.4f, 0.6f, 0.09f, 1.0f);
	ImVec4 spiritColor = ImVec4(0.55f, 0.34f, 0.71f, 1.0f);

	ImVec4 color;
	if (category == "Weapon")
	{
		color = weaponColor;
	}
	else if (category == "Vitality")
	{
		color = vitalityColor;
	}
	else if (category == "Spirit")
	{
		color = spiritColor;
	}
	else
	{
		color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	ImGui::PushStyleColor(ImGuiCol_Text, color);
}

void MainLayer::BuyItem(std::string itemName)
{
	m_BoughtItems.push_back(itemName);
}

