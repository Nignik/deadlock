#include "DataLoader.h"

#include <iostream>
#include <fstream>

#include "Hero.h"

json DataLoader::LoadJsonData(std::string fileName)
{
	std::ifstream itemsFile("../../" + fileName);
	if (!itemsFile.is_open())
	{
		std::cerr << "Unable to open file\n";
		return nullptr;
	}

	json itemsData;
	itemsFile >> itemsData;
	itemsFile.close();

	return itemsData;
}

std::vector<Item> DataLoader::LoadItemsData()
{
	json itemsData = LoadJsonData("items.json");

	std::vector<Item> items;
	for (auto& [itemName, itemData] : itemsData.items())
	{
		items.emplace_back(std::string(itemName), itemData);
	}

	return items;
}

std::vector<Hero> DataLoader::LoadHeroesData()
{
	json heroesData = LoadJsonData("heroes.json");

	std::vector<Hero> heroes;
	for (auto& [heroName, heroData] : heroesData.items())
	{
		json weapon = heroData["BaseWeapon"];
		json vitality = heroData["BaseVitality"];

		auto conv = [](json x) -> float {
			try
			{
				return x.get<float>();
			}
			catch (const std::exception& e)
			{
				std::cerr << "Error converting JSON to float: " << e.what() << std::endl;
				return 0.0f;
			}
		};

		std::map<std::string, float> stats;

		for (auto& [statName, statValue] : weapon.items())
		{
			stats[statName] = statValue;
		}
		for (auto& [statName, statValue] : vitality.items())
		{
			stats[statName] = statValue;
		}

		heroes.push_back({ heroName, std::move(stats) });
	}

	return heroes;
}

