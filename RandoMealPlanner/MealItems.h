#pragma once
#include <string>
#include <vector>
#include <math.h>
#include <algorithm> 
#include <iostream>

struct MealItem;

namespace RandoMeal
{
	typedef enum MealItemTypes
	{
		NONE = 0,
		ENTREES,
		SIDES,
		STARCHES,
		GROCERIES
	}MealItemTypes;

	MealItemTypes TypesFromString(const std::string& str);

	void ConsumeCSV(const std::string& filename, std::vector<MealItem>& items);
	bool GetNextCSVAttribute(std::stringstream& ss, std::string& value);
}




struct MealItem {

	std::string Name;
	std::string Meat;
	std::string Origin;
	RandoMeal::MealItemTypes Type;
	std::string Category;
	double Ratio;
	int Count;
	int More;
	std::vector<std::string> Groceries;

	bool NeedsStarch;
	bool NeedsSide;

	MealItem(const std::string& str, const std::string& type_str);
	void AddCount();

	MealItem()
		: Name("TAKEOUT")
		, Meat("ANY")
		, Origin("ANY")
		, Type(RandoMeal::NONE)
		, Category("uncategorized")
		, Ratio(1.0)
		, Count(0)
		, More(0)
		, Groceries()
		, NeedsStarch(false)
		, NeedsSide(false)
	{}
};

struct MealPlan {
public:
	MealPlan()
		: Type(eMealPlanType::DINNER)
		, Entree()
		, Starch()
		, Side()
	{}

	enum class eMealPlanType {
		BREAKFAST,
		LUNCH,
		DINNER
	};

	eMealPlanType Type;
	MealItem Entree;
	MealItem Starch;
	MealItem Side;

	std::string Name() const
	{
		return Entree.Name;
	}

	std::string Meat() const
	{
		return Entree.Meat;
	}

	std::string Origin() const
	{
		return Entree.Origin;
	}

	bool HasStarch() const
	{
		return Entree.NeedsStarch;
	}

	bool HasSide() const
	{
		return Entree.NeedsSide;
	}

	std::vector<std::string> GetGroceries();

};