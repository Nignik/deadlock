#pragma once

#include <string>
#include <vector>

#include "json/json.h"

using json = nlohmann::json;

enum class Category
{
	WEAPON, VITALITY, SPIRIT
};

inline bool operator<(Category lhs, Category rhs)
{
	return static_cast<int>(lhs) < static_cast<int>(rhs);
}

struct Item
{
	Category category;

	int cost;
	int tier;

	std::string name;

	std::map<std::string, std::string> statBoosts;
	std::vector<std::string> passives;
	std::vector<std::string> actives;

	Item(std::string& itemName, json& data)
	{
		category = Category::WEAPON;
		if (data["category"] == "Vitality")
			category = Category::VITALITY;
		else if (data["category"] == "Spirit")
			category = Category::SPIRIT;

		cost = std::stoi(data["cost"].get<std::string>());
		tier = std::stoi(data["tier"].get<std::string>());

		name = itemName;

		for (auto& statBoost : data["stat boosts"].items())
		{
			statBoosts[statBoost.key()] = statBoost.value();
		}

		for (auto& passive : data["passive effects"])
		{
			passives.push_back(passive.get<std::string>());
		}

		for (auto& active : data["active effects"])
		{
			actives.push_back(active.get<std::string>());
		}
	}

	bool operator<(const Item& other) const
	{
		return name < other.name;
	}
};

inline bool compareItemsByName(const Item& a, const Item& b)
{
	return a.name < b.name;
}

inline bool compareByCategory(const Item& a, const Item& b)
{
	return a.category < b.category;
}