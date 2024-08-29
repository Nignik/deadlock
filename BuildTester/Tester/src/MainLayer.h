#pragma once

#include <Walnut/Layer.h>

#include <fstream>
#include <iostream>

#include "json.h"

using json = nlohmann::json;

class MainLayer : public Walnut::Layer
{
public:
	MainLayer();

	virtual void OnUIRender() override;
	void RenderItemsList();
	void RenderStatsTable();
	void RenderBoughtItems();

	void SetTextColor(std::string name);

	void BuyItem(std::string itemName);

private:
	json m_ItemsData;
	std::vector<std::string> m_ItemNames;
	std::vector<std::string> m_statNames;
	std::vector<std::string> m_BoughtItems;
};