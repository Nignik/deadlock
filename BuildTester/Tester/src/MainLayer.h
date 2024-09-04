#pragma once

#include <Walnut/Layer.h>

#include <fstream>
#include <iostream>
#include <set>
#include <functional>

#include "json/json.h"
#include "Item.h"
#include "Hero.h"

using json = nlohmann::json;

class MainLayer : public Walnut::Layer
{
public:
	MainLayer();

	virtual void OnUIRender() override;
	void RenderItemsList();
	void RenderStatsTable();
	void RenderPassives();
	void RenderBoughtItems();
	void RenderHeroes();

	void SetTextColor(Category itemCategory);

	void SetHero(Hero& hero);
	void UpdateStats();
	void UpdateStatValue(std::string statName, std::string statUpdate);
	void BuyItem(Item& item);
	void SellItem(Item& item);

private:
	Hero m_SelectedHero;
	std::vector<Item> m_Items;
	std::vector<Hero> m_Heroes;
	std::map<std::string, float> m_Stats;
	std::set<Item> m_BoughtItems;
};