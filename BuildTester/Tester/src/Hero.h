#pragma once

#include <map>

struct BaseWeapon
{
	float dps;
	float bulletDamage;
	float ammo;
	float bulletsPerSec;
	float lightMelee;
	float heavyMelee;
};

struct BaseVitality
{
	float maxHealth;
	float healthRegen;
	float bulletResist;
	float spiritResist;
	float moveSpeed;
	float sprintSpeed;
	float stamina;
};

struct Hero
{
	std::string name;
	std::map<std::string, float> baseStats;
};