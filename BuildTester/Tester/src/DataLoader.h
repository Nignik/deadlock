#pragma once

#include <string>
#include <vector>
#include <map>

#include "json/json.h"
#include "Item.h"
#include "Hero.h"

using nlohmann::json;

class DataLoader
{
public:
	static DataLoader& GetInstance()
	{
		static DataLoader instance;
		return instance;
	}

	static json LoadJsonData(std::string fileName);
	static std::vector<Item> LoadItemsData();
	static std::vector<Hero> LoadHeroesData();

	DataLoader(const DataLoader&) = delete;
	DataLoader& operator=(const DataLoader&) = delete;

private:
	static std::string m_DataFolderpath;

	DataLoader() {}
	~DataLoader() = default;
};