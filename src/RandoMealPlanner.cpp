#include <iostream>
#include <map>
#include <vector>
#include <exception>
#include <chrono>
#include <fstream> // file stream
#include <sstream> // stringstream
#include <utility> // make_pair

#include "MealItems.h"
#include "RandoMealPlanner.h"

constexpr const char* SEED_DATA_FILE = "seed.dat";

const std::vector<std::string> EXPECTED_CSVS = {"groceries.csv","entrees.csv","starches.csv","sides.csv","regulars.csv"};
constexpr const size_t DEFAULT_DAYS=14;
using _Clock = std::chrono::steady_clock;

int RandoMealPlanner::roll(int min, int max)
{
	// x is in [0,1]
	double x = m_gRand() / static_cast<double>(RAND_MAX);

	// [0, 1 * (max - min) + min is in [min,max]]
	int that = min + static_cast<int>(x * abs(max - min));

	return that;
}

MealItem RandoMealPlanner::rollMealItem(std::vector<MealItem> items)
{
	const std::size_t index = static_cast<std::size_t>(roll(0, items.size()));
	return items.at(index);
}

void RandoMealPlanner::addGroceryItem(std::map<std::string, MealItem>& list, MealItem item)
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

bool RandoMealPlanner::planHasMeal(const std::map<std::uint16_t, MealPlan>& thePlan, const MealPlan& theItem)
{
	for (auto iter : thePlan)
	{
		if (iter.second.Name() == theItem.Name())
			return true;
	}

	return false;
}

RandoMealPlanner::RandoMealPlanner()
	: m_entreeItems()
	, m_starchItems()
	, m_sideItems()
	, m_regularItems()
	, m_groceryItems()
	, m_theplan()
	, m_finalGroceryList()
{
	std::ifstream seedFile(SEED_DATA_FILE);
	if(seedFile.fail())
	{
		m_gRand = std::minstd_rand0(_Clock::now().time_since_epoch().count());
	}
	else
	{
		seedFile >> m_gRand;
	}
	seedFile.close();
}

RandoMealPlanner::~RandoMealPlanner()
{
	std::ofstream seedFile(SEED_DATA_FILE);
	seedFile << m_gRand;
	seedFile.close();
}

int main(int argc, char** argv)
{
	RandoMealPlanner obj;
	obj.main(argc, argv);
}



void RandoMealPlanner::main(int argc, char** argv)
{
	std::string folder = "csvs/";
	size_t days = DEFAULT_DAYS;
	std::cout << "RandoMealPlanner\n";

	if(argc < 2)
	{
		std::cout << "Running with defaults: Days: " << (int) DEFAULT_DAYS << " CSV Folder: " << folder << "\n";
		std::cout << "To modify use the following options:\n";
		std::cout << "./RandoMealPlanner [FOLDER:{CSV_FOLDER}] [DAYS:{INT}]" << std::endl;
	}
	else
	{
		for(int ii=1; ii<argc; ++ii)
		{
			std::string argument = argv[ii];
			size_t del_pos = argument.find(":") + 1;
			std::string value;

			if(del_pos != std::string::npos)
			{
				value = argument.substr(del_pos);
			}

			if(argument.find("FOLDER") != std::string::npos)
			{
				folder = value + "/";
			}
			
			if(argument.find("DAYS") != std::string::npos)
			{
				try
				{
					days = atoi(value.c_str());
				}
				catch(const std::exception& e)
				{
					std::cerr << "Days value of " << value << "was not expected" << std::endl;
				}
				
				
			}
		}
		
	}

	//// consume grocery items
	std::vector<MealItem> groceryVector;

	// consume meal plans from csv files
	RandoMeal::ConsumeCSV(folder + EXPECTED_CSVS[0], groceryVector);
	RandoMeal::ConsumeCSV(folder + EXPECTED_CSVS[1], m_entreeItems);
	RandoMeal::ConsumeCSV(folder + EXPECTED_CSVS[2], m_starchItems);
	RandoMeal::ConsumeCSV(folder + EXPECTED_CSVS[3], m_sideItems);
	RandoMeal::ConsumeCSV(folder + EXPECTED_CSVS[4], m_regularItems);

	for (auto item : groceryVector)
	{
		m_groceryItems[item.Name] = item;
	}

	std::cout << "Randomizing " << (int)days << " Day Meal Plan" << std::endl;
	GenerateMealPlan(days);
	GetGroceryList();
	PrintDays();
	PrintGroceryList();
	std::cout << "Fin!" << std::endl;
}

bool RandoMealPlanner::checkBackItems(size_t ii, const std::string& origin, const std::string& meat)
{
	
	int backone = (ii > 0) ? ii - 1 : 0;
	int backtwo = (ii > 1) ? ii - 2 : 0;

	// follow rules
	return (
		(origin == m_theplan[backone].Origin()) ||
		(origin == m_theplan[backtwo].Origin()) ||
		(meat == m_theplan[backone].Meat()) ||
		(meat == m_theplan[backtwo].Meat())
	);
}

void RandoMealPlanner::PrintGroceryList()
{
	// convert final grocery list to categories
	std::multimap<std::string, MealItem> categoryList;
	for (auto iter : m_finalGroceryList)
	{
		// @TODO: some items appear to be duplicated (probably with more), and they
		// don't belong in this list... all items should have a category in the CSV files.
		// removing the uncategorized items solves a weird printing problem and items in 
		// the printed list are duplicates.
		size_t found = iter.second.Category.find("Uncategorized");
		if(found == std::string::npos)
		{
			categoryList.insert(std::make_pair(iter.second.Category, iter.second));
		}
	}

	// print groceries
	for (auto iter : categoryList)
	{
		std::ostringstream oss;
		oss << iter.second;
		std::cout << oss.str() << "\n";
	}
}
void RandoMealPlanner::PrintDays()
{
	for (auto iter : m_theplan)
	{
		std::ostringstream oss;
		oss << iter.second;
		std::cout << "Day " << (int) (iter.first + 1) << ": " << oss.str() << "\n";
	}
}


void RandoMealPlanner::GenerateMealPlan(size_t days)
{

	size_t ii = 0;
	while (ii < days)
	{
		MealPlan plan;
		int randomizer = 0;
		while (randomizer < m_entreeItems.size())
		{
			randomizer++;

			plan.Entree = rollMealItem(m_entreeItems);

			if (ii < 1)
				break;

			// if the plan already contains this meal, reroll
			if (planHasMeal(m_theplan, plan))
				continue;

			// follow rules, if entry already exists, redo the day
			if( ! checkBackItems(ii, plan.Entree.Origin, plan.Entree.Meat) ) 
				randomizer--;
		}

		if (plan.HasSide())
		{
			plan.Side = rollMealItem(m_sideItems);
		}

		if (plan.HasStarch())
		{
			plan.Starch = rollMealItem(m_starchItems);
		}

		std::vector<std::string> items = plan.GetGroceries();

		for (auto item : items)
		{
			
			MealItem mItem;
			mItem.Name = item;
			m_regularItems.push_back(mItem);
		}

		m_theplan[ii] = plan;
		ii++;
	}
}

void RandoMealPlanner::GetGroceryList()
{
	// add the regular items to the grocery list
	for (auto item : m_regularItems)
	{
		auto iter = m_groceryItems.find(item.Name);
		if (iter != m_groceryItems.end())
		{
			item.Category = iter->second.Category;
			item.Ratio = iter->second.Ratio;
		}
		addGroceryItem(m_finalGroceryList, item);
	}
}
