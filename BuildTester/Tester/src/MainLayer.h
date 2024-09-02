#pragma once

#include <Walnut/Layer.h>

#include <fstream>
#include <iostream>
#include <set>

#include "json/json.h"
#include "Item.h"

using json = nlohmann::json;

class MainLayer : public Walnut::Layer
{
public:
	MainLayer();

	virtual void OnUIRender() override;
	void RenderItemsList();
	void RenderStatsTable();
	void RenderBoughtItems();

	void SetTextColor(Category itemName);

	void UpdateStats(Item& itemName);
	void UpdateStatValue(std::string statName, std::string statUpdate);
	void BuyItem(Item& itemName);
	void SellItem(Item& itemName);

private:
	std::vector<Item> m_Items;
	std::map<std::string, float> m_Stats;
	std::set<Item> m_BoughtItems;
};