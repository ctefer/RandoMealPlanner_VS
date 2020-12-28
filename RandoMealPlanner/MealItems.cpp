#include "MealItems.h"
#include <sstream> // stringstream
#include <fstream> // file stream

bool RandoMeal::GetNextCSVAttribute(std::stringstream& ss, std::string& value)
{
	if (ss.good())
	{
		std::getline(ss, value, ',');
		value.erase(std::remove(value.begin(), value.end(), '\t'), value.end());
		
		return !(value.empty());
	}

	return false;
}

void RandoMeal::ConsumeCSV(const std::string& filename, std::vector<MealItem>& items)
{
	std::ifstream fs(filename);
	std::string line;
	std::string type;
	std::getline(fs, type);
	while (std::getline(fs, line))
	{
		std::size_t found = line.find('#');
		if (found == 0)
			continue;

		if (line.empty())
			continue;

		MealItem item(line, type);
		items.push_back(item);
	}
	fs.close();
}

RandoMeal::MealItemTypes RandoMeal::TypesFromString(const std::string& str)
{
	std::string type;
	type.resize(str.size());

	std::transform(str.begin(), str.end(), type.begin(), ::toupper);

	if (type == "ENTREES") return MealItemTypes::ENTREES;
	if (type == "SIDES") return MealItemTypes::SIDES;
	if (type == "STARCHES") return MealItemTypes::STARCHES;
	if (type == "GROCERIES") return MealItemTypes::GROCERIES;

	return MealItemTypes::NONE;
}

MealItem::MealItem(const std::string& str, const std::string& type_str)
	: MealItem()
{
	std::stringstream ss(str);
	std::string value;
	int position = 0;

	Type = RandoMeal::TypesFromString(type_str);

	while (RandoMeal::GetNextCSVAttribute(ss, value))
	{
		if (Type == RandoMeal::GROCERIES)
		{
			switch (position)
			{
			case 0: Name = value; break;
			case 1: Category = value; break;
			case 2: Ratio = atoll(value.c_str()); break;
			default:
				break;
			}
		}
		else if (Type == RandoMeal::ENTREES)
		{
			switch (position)
			{
			case 0: Name = value; break;
			case 1: Meat = value; break;
			case 2: Origin = value; break;
			case 3: NeedsStarch = (value == "TRUE") ? true : false; break;
			case 4: NeedsSide = (value == "TRUE") ? true : false; break;
			default: Groceries.push_back(value); break;
			}
		}
		else if (Type == RandoMeal::SIDES || Type == RandoMeal::STARCHES)
		{
			switch (position)
			{
			case 0: Name = value; break;
			default: Groceries.push_back(value); break;
			}
		}

		position++;
	}
}

void MealItem::AddCount()
{
	Count++;
	if (Ratio == 0)
		More = 1;
	else
		More = static_cast<int>(ceil(Count / Ratio));
}

std::vector<std::string> MealPlan::GetGroceries()
{
	std::vector<std::string> items;

	items.insert(items.end(), Entree.Groceries.begin(), Entree.Groceries.end());
	items.insert(items.end(), Starch.Groceries.begin(), Starch.Groceries.end());
	items.insert(items.end(), Side.Groceries.begin(), Side.Groceries.end());

	return items;
}

