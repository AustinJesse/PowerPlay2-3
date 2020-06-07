// Group Three - Alexeev, Anton & Austin Jesse

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

struct Object
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};

std::vector<Object> loadMonsters(const std::string& fileName);
void displayBattle(const Object& player, const std::vector<Object>& monsters);
void monsterAttack(Object& player, const std::vector<Object>& monsters);
void playerAttack(const Object& player, std::vector<Object>& monsters);
int attack(const Object& attacker);
void defend(Object& defender, int damage);
void heal(Object& object);
void bringOutYourDead(std::vector<Object>& monsters);
int strengthGenerator();
int healthGenerator();
int willAttack();
int willDefend();

int main()
{

	Object player;
	player.name = "Jake";
	player.strength = std::max(1, strengthGenerator());
	player.health = std::max(1, healthGenerator());

	std::vector<Object> monsters;
	loadMonsters("monsters.txt");

	std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
	while (player.health > 0 && monsters.size() > 0)
	{
		std::cout << "What do you do? (a)ttack (h)eal ";
		char command{ 'x' };
		std::cin >> command;
		switch (command)
		{
		case 'a':
		{
			playerAttack(player, monsters);
			break;
		}
		case 'h':
			heal(player);
			break;
		default:
			std::cout << "please enter a or h" << std::endl;
			break;
		}

		bringOutYourDead(monsters);

		monsterAttack(player, monsters);

		for (const auto& monster : monsters)
		{
			if (willAttack())
			{
				std::cout << monster.name << " attacks!" << std::endl;
				player.health -= monster.strength;
			}
			else
			{
				std::cout << monster.name << " twiddles its thumbs" << std::endl;
			}
		}

		system("PAUSE");
		system("CLS");
	}

	if (player.health <= 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.health <= 0 && monsters.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}

std::vector<Object> loadMonsters(const std::string& fileName) {
	std::ifstream fin;
	int numberOfMonsters{ 0 };

	std::vector<Object> monsters;
	fin.open("monsters.txt");
	if (fin.is_open()) {
		fin >> numberOfMonsters;

		for (int i = 0; i < numberOfMonsters; ++i) {
			Object newMonster;
			fin >> newMonster.name >> newMonster.strength >> newMonster.health;
			monsters.push_back(newMonster);
		}
	}
	return monsters;
}

void displayBattle(const Object& player, const std::vector<Object>& monsters) {
	std::cout << player.name << " has " << player.health << " health and " << player.strength << " strength." << std::endl;
	for (int i{ 0 }; i < monsters.size(); i++)
	{
		std::cout << "Monster: " << i + 1 << " is named " << monsters[i].name << ". It has " << monsters[i].health << " health and " <<
			monsters[i].strength << " strength." << std::endl;
	}
}

void monsterAttack(Object& player, const std::vector<Object>& monsters) {
	for (const auto& monster : monsters)
	{
		if ((bool)(willAttack()) == true)
		{
			std::cout << monster.name << " attacks!" << std::endl;
			player.health -= monster.strength;
		}
		else
		{
			std::cout << monster.name << " twiddles its thumbs" << std::endl;
		}
	}
}

void playerAttack(const Object& player, std::vector<Object>& monsters) {
	std::cout << "Choose a monster to attack:";
	int monsterNum{ 0 };
	std::cin >> monsterNum;
	if (monsterNum > 0 && monsterNum <= monsters.size())
	{
		monsters[monsterNum - 1].health -= player.strength;
	}
}

int attack(const Object& attacker) {
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::normal_distribution<double> damageDealt(attacker.strength, 1.0);

	std::cout << attacker.name << " deals ";

	return damageDealt(engine);
}

void defend(Object& defender, int damage) {
	int defendedAmount = willDefend();
	defender.health = defendedAmount + defender.health;
	std::cout << defender.name << " defended this much: " << defendedAmount << std::endl;
}


void heal(Object& object) {
	object.health += object.strength * 2;
}

void bringOutYourDead(std::vector<Object>& monsters) {
	for (auto monsterIter{ monsters.begin() }; monsterIter != monsters.end(); ) {
		if (monsterIter->health <= 0) {
			monsterIter = monsters.erase(monsterIter);
		}
		else {
			monsterIter++;
		}
	}
}

int strengthGenerator() {
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::normal_distribution<double> randomStrength(5.0, 1.0);
	return randomStrength(engine);
}

int healthGenerator() {
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::normal_distribution<double> randomHealth(30.0, 5.0);
	return randomHealth(engine);
}

int willAttack() {
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::bernoulli_distribution willAttack(.75);
	return willAttack(engine);
}

int willDefend() {
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::normal_distribution<double> randomDefense(strengthGenerator() * 2, 3);
	return randomDefense(engine);
}