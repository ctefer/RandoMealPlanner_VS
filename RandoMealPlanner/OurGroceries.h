#pragma once
#include <string>
#include <vector>

typedef int ItemId;
typedef std::pair<std::string, std::string> Payload;

class OurGroceries
{
public:
	OurGroceries();
	~OurGroceries() {}

	void Initialize(std::string filedb);

	void GetLists(std::vector<std::string>& lists);
	void GetListItems(const ItemId id, std::vector<std::string>& list);
	void GetCategories(std::vector<std::string>& categories);
	
	void CreateList(const std::string& name);
	void CreateCategory(const std::string& name, const std::string& type="SHOPPING");

	void ToggleItemCrossedOff(ItemId list_id, ItemId item_id, bool cross_off = false);

	ItemId AddItemToList(ItemId list_id, const std::string& name, const std::string& category = "uncategorized");
	void RemoveItemFromList(ItemId list_id, ItemId item_id);

private:

	void login();
	ItemId getItemId();
	void getSessionCookie();
	void postCommand(const std::string& command, const Payload& payload = {}, bool other_payload = false);

	std::string m_username;
	std::string m_password;
	ItemId m_teamId;
	ItemId m_sessionCookie;
	bool m_loggedIn;


};