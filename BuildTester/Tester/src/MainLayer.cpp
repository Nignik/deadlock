#include "MainLayer.h"

#include <Walnut/Application.h>
#include <Walnut/UI/UI.h>

#include "DataLoader.h"
#include "Data.h"
#include "Decode.h"

MainLayer::MainLayer()
{
	m_Items = DataLoader::GetInstance().LoadItemsData();
	m_Heroes = DataLoader::GetInstance().LoadHeroesData();

	UpdateStats();
}

void MainLayer::OnUIRender()
{
	RenderItemsList();
	RenderStatsTable();
	RenderBoughtItems();
	RenderHeroes();
}

void MainLayer::RenderItemsList()
{
	ImVec2 size(400, 700);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockLeft"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Items");

	static unsigned int currentItem = 0;

	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));

	if (ImGui::BeginListBox(" ", size))
	{
		for (int i = 0; i < m_Items.size(); i++)
		{
			const bool isSelected = (currentItem == i);

			SetTextColor(m_Items[i].category);
			if (ImGui::Selectable(m_Items[i].name.c_str(), isSelected))
			{
				currentItem = i;
			}
			ImGui::PopStyleColor();

			if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered() && isSelected)
			{
				BuyItem(m_Items[i]);
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndListBox();
	}

	ImGui::PopStyleColor();

	ImGui::End();
}

void MainLayer::RenderStatsTable()
{
	ImVec2 size(500, 700);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockRight"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Stats");

	if (ImGui::BeginTable("Stats", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed, 500);
		ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableHeadersRow();

		for (const auto& [statName, statValue] : m_Stats)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("%s", statName.c_str());
			ImGui::TableNextColumn();
			ImGui::Text("%.3f", statValue);
		}

		ImGui::EndTable();
	}

	ImGui::End();
}

void MainLayer::RenderPassives()
{
	ImVec2 size(500, 700);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockDown"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Passives");

	if (ImGui::BeginTable("Stats", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed, 500);
		ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 100);
		ImGui::TableHeadersRow();

		for (const auto& [statName, statValue] : m_Stats)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("%s", statName.c_str());
			ImGui::TableNextColumn();
			ImGui::Text("%.3f", statValue);
		}

		ImGui::EndTable();
	}

	ImGui::End();
}

void MainLayer::RenderBoughtItems()
{
	ImVec2 size(400, 300);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockUp"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Bought Items");

	static unsigned int currentBoughtItem = 0;

	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
	
	std::vector<Item> itemsToSell;
	if (ImGui::BeginListBox(" ", size))
	{
		int i = 0;
		for (auto& item : m_BoughtItems)
		{
			const bool isSelected = (currentBoughtItem == i);

			SetTextColor(item.category);
			if (ImGui::Selectable(item.name.c_str(), isSelected))
			{
				currentBoughtItem = i;
			}
			ImGui::PopStyleColor();

			if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered() && isSelected)
			{
				itemsToSell.push_back(item);
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}

			i++;
		}
		ImGui::EndListBox();
	}

	ImGui::PopStyleColor();

	ImGui::End();

	for (auto& itemToSell : itemsToSell)
	{
		SellItem(itemToSell);
	}
}

void MainLayer::RenderHeroes()
{
	ImVec2 size(400, 700);

	ImGui::SetNextWindowDockID(ImGui::GetID("DockDown"), ImGuiCond_FirstUseEver);
	ImGui::Begin("Heroes");

	static unsigned int currentHero = 0;

	if (ImGui::BeginListBox(" ", size))
	{
		for (int i = 0; i < m_Heroes.size(); i++)
		{
			const bool isSelected = (currentHero == i);

			if (ImGui::Selectable(m_Heroes[i].name.c_str(), isSelected))
			{
				if (currentHero != i)
				{
					SetHero(m_Heroes[currentHero]);
				}
				currentHero = i;
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

void MainLayer::SetTextColor(Category itemCategory)
{
	ImVec4 weaponColor = ImVec4(0.79f, 0.48f, 0.01f, 1.0f);
	ImVec4 vitalityColor = ImVec4(0.4f, 0.6f, 0.09f, 1.0f);
	ImVec4 spiritColor = ImVec4(0.55f, 0.34f, 0.71f, 1.0f);

	ImVec4 color;

	switch (itemCategory)
	{
	case Category::WEAPON:
		color = weaponColor;
		break;
	case Category::VITALITY:
		color = vitalityColor;
		break;
	case Category::SPIRIT:
		color = spiritColor;
		break;
	default:
		color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	ImGui::PushStyleColor(ImGuiCol_Text, color);
}

void MainLayer::SetHero(Hero& hero)
{
	m_SelectedHero = hero;
	UpdateStats();
}

void MainLayer::UpdateStats()
{
	m_Stats.clear();
	for (auto& [statName, statValue] : m_SelectedHero.baseStats)
	{
		m_Stats[statName] = statValue;
	}

	for (auto& item : m_BoughtItems)
	{
		for (auto& [statName, statValue] : item.statBoosts)
		{
			UpdateStatValue(statName, statValue);
		}
	}
}

void MainLayer::UpdateStatValue(std::string statName, std::string statUpdate)
{
	m_Stats[statName] += decode::decodeStatBoost(statUpdate, m_Stats[statName]);
}

void MainLayer::BuyItem(Item& item)
{
	m_BoughtItems.insert(item);
	UpdateStats();
}

void MainLayer::SellItem(Item& item)
{
	m_BoughtItems.erase(item);
	UpdateStats();
}

