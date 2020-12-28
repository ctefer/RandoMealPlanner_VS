#include <iostream> // std::cout
#include <map>
#include <vector>
#include <fstream> // file stream
#include <sstream> // stringstream
#include <ctime> // time
#include <iomanip> // setw
#include <utility> // make_pair

#include "MealItems.h"

int roll(int min, int max)
{
	// x is in [0,1[
	double x = rand() / static_cast<double>(RAND_MAX + 1);

	// [0,1[ * (max - min) + min is in [min,max[
	int that = min + static_cast<int>(x * abs(max - min));

	return that;
}

MealItem rollMealItem(std::vector<MealItem> items)
{
	const std::size_t index = static_cast<std::size_t>(roll(0, items.size()));
	return items.at(index);
}

void AddGroceryItem(std::map<std::string, MealItem>& list, MealItem item)
{
	auto iter = list.find(item.Name);
	if (iter != list.end())
	{
		MealItem& rItem = list.at(item.Name);
		rItem.AddCount();
	}
	else
	{
		item.AddCount();
		list[item.Name] = item;
	}
}



bool planHasMeal(const std::map<std::uint16_t, MealPlan>& thePlan, const MealPlan& theItem)
{
	for (auto iter : thePlan)
	{
		if (iter.second.Name() == theItem.Name())
			return true;
	}

	return false;
}


int main(int argc, int** argv)
{
	std::cout << "Randomizing 14 day meal plan" << std::endl;

	std::map<std::uint16_t, MealPlan> theplan;

	//// consume grocery items
	std::vector<MealItem> groceryVector;
	RandoMeal::ConsumeCSV("../groceries.csv", groceryVector);
	std::map<std::string, MealItem> groceryItems;

	for (auto item : groceryVector)
	{
		groceryItems[item.Name] = item;
	}

	// consume meal plans from csv files
	std::vector<MealItem> entreeItems;
	RandoMeal::ConsumeCSV("../entrees.csv", entreeItems);
	std::vector<MealItem> starchItems;
	RandoMeal::ConsumeCSV("../starches.csv", starchItems);
	std::vector<MealItem> sideItems;
	RandoMeal::ConsumeCSV("../sides.csv", sideItems);
	std::vector<MealItem> regularItems;
	RandoMeal::ConsumeCSV("../regulars.csv", regularItems);

	

	std::map<std::string, MealItem> finalGroceryList;

	// seed the random with time
	srand(time(NULL));


	// choose random takeout days
	const int takeout1 = roll(4, 7);
	const int takeout2 = roll(9, 13);

	theplan[takeout1]; theplan[takeout2];

	int ii = 0;
	while(ii < 14)
	{
		if (ii == takeout1 || ii == takeout2)
		{
			ii++;
			continue;
		}

		MealPlan plan;
		int randomizer = 0;

		while(randomizer < entreeItems.size())
		{
			randomizer++;

			plan.Entree = rollMealItem(entreeItems);
			


			if (ii < 1)
				break;

			// if the plan already contains this meal, reroll
			if (planHasMeal(theplan, plan))
				continue;

			int backone = (ii > 0) ? ii - 1 : 0;
			int backtwo = (ii > 1) ? ii - 2 : 0;
			int backthr = (ii > 2) ? ii - 3 : 0;

			// follow rules
			if ((plan.Entree.Origin == theplan[backone].Origin()) ||
				(plan.Entree.Origin == theplan[backtwo].Origin()) ||
				(plan.Entree.Meat == theplan[backone].Meat()) ||
				(plan.Entree.Meat == theplan[backtwo].Meat()) )
			{
				continue;
			}
			else
			{
				break;
			}
		}

		if (plan.HasSide())
		{
			plan.Side = rollMealItem(sideItems);
		}

		if (plan.HasStarch())
		{
			plan.Starch = rollMealItem(starchItems);
		}

		std::vector<std::string> items = plan.GetGroceries();

		for (auto item : items)
		{
			auto iter = groceryItems.find(item);
			MealItem mItem;
			mItem.Name = item;
			if (iter != groceryItems.end())
			{
				mItem.Category = iter->second.Category;
				mItem.Ratio = iter->second.Ratio;
			}
			AddGroceryItem(finalGroceryList, mItem);
		}
		
		theplan[ii] = plan;
		ii++;
	}

	// add the regular items to the grocery list
	for (auto item : regularItems)
	{
		auto iter = groceryItems.find(item.Name);
		if (iter != groceryItems.end())
		{
			item.Category = iter->second.Category;
			item.Ratio = iter->second.Ratio;
		}
		AddGroceryItem(finalGroceryList, item);
	}

	//std::cout << std::setw(30);

	// print meals
	for (auto iter : theplan)
	{
		std::cout << std::to_string(iter.first)
			<< " : " << iter.second.Entree.Name;

		if (iter.second.HasStarch())
			std::cout << " , " << iter.second.Starch.Name;

		if (iter.second.HasSide())
			std::cout << " , " << iter.second.Side.Name;

		std::cout << std::endl;
	}

	// convert final grocery list to categories
	std::multimap<std::string, MealItem> categoryList;
	for (auto iter : finalGroceryList)
	{
		categoryList.insert(std::make_pair(iter.second.Category, iter.second));

	}


	// print groceries
	for (auto iter : categoryList)
	{
		std::cout << iter.first << " - "
			<< "Item: " << iter.second.Name
			<< "(" << iter.second.More << ")" << std::endl;
	}

	std::cout << "Fin!" << std::endl;

}