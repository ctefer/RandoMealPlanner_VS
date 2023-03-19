#pragma once

#include <vector>
#include <map>
#include <random>
#include <iostream>
#include <sstream>
#include "MealItems.h"

std::ostringstream& operator<<(std::ostringstream& oss, const std::vector<MealItem>& vect)
{
	for(const auto item : vect)
	{
		oss << item.Name << ",";
	}

	return oss;
}

class RandoMealPlanner
{
public:
	RandoMealPlanner();
	~RandoMealPlanner();

	void main(int argc, char**argv);

private:

	void GenerateMealPlan(size_t days);
	void GetGroceryList();
	void HttpSendGroceryList();
	void PrintDays();
	void PrintGroceryList();


	int roll(int min, int max);
	MealItem rollMealItem(std::vector<MealItem> items);
	void addGroceryItem(std::map<std::string, MealItem>& list, MealItem item);
	bool planHasMeal(const std::map<std::uint16_t, MealPlan>& thePlan, const MealPlan& theItem);
	bool checkBackItems(size_t ii, const std::string& origin, const std::string& meat);
	MealPlan GetMeal();

	// consume meal plans from csv files
	std::vector<MealItem> m_entreeItems;
	std::vector<MealItem> m_starchItems;
	std::vector<MealItem> m_sideItems;
	std::vector<MealItem> m_regularItems;
	std::map<std::string, MealItem> m_groceryItems;
	std::map<std::uint16_t, MealPlan> m_theplan;
	std::map<std::string, MealItem> m_finalGroceryList;

	std::minstd_rand0 m_gRand;

	void PrintMealItems(const std::vector<MealItem>& vect)
	{
		std::ostringstream oss;
		oss << vect;
		std::cout << oss.str() << std::endl;
	}
};


