#pragma once
#include <string>
#include <vector>
#include <math.h>
#include <algorithm> 
#include <iostream>
#include <iomanip>
#include <sstream>

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
		, Category("Uncategorized")
		, Ratio(1.0)
		, Count(0)
		, More(1)
		, Groceries()
		, NeedsStarch(false)
		, NeedsSide(false)
	{	}

	friend std::ostringstream& operator << (std::ostringstream& oss, const MealItem& mi)
	{
		oss << mi.Category << " Item: " << mi.Name;
		int more = (int) mi.More;
		
		if(more > 1)
			oss << "[" << more << "]";
		
		return oss;
	}
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

	friend std::ostringstream& operator << (std::ostringstream& oss, const MealPlan& mp)
	{
		oss << mp.Entree.Name;
		if(mp.HasStarch())
		{
			oss << "," << mp.Starch.Name;
		}
		if(mp.HasSide())
		{
			oss << "," << mp.Side.Name;
		}
		return oss;
	}

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


