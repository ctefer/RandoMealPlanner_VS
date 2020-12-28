#include "OurGroceries.h"
#include <utility>
#include "boost/beast.hpp"

namespace
{
	
	// urls used
	const char* BASE_URL = "https://www.ourgroceries.com";
	const char* SIGN_IN = "{}/sign-in";
	const char* YOUR_LISTS = "{}/your-lists/";

	// cookies
	const char* COOKIE_KEY_SESSION = "ourgroceries-auth";

	// form fields when logging in
	const char* FORM_KEY_USERNAME = "emailAddress";
	const char* FORM_KEY_PASSWORD = "password";
	const char* FORM_KEY_ACTION = "action";
	const char* FORM_VALUE_ACTION = "sign-me-in";

	// actions to preform on post api
	const char* ACTION_GET_LIST = "getList";
	const char* ACTION_GET_LISTS = "getOverview";

	const char* ACTION_ITEM_CROSSED_OFF = "setItemCrossedOff";
	const char* ACTION_ITEM_ADD = "insertItem";
	const char* ACTION_ITEM_REMOVE = "deleteItem";
	const char* ACTION_ITEM_RENAME = "changeItemValue";

	const char* ACTION_LIST_CREATE = "createList";
	const char* ACTION_LIST_REMOVE = "deleteList";
	const char* ACTION_LIST_RENAME = "renameList";


	// regex to get team id
	const char* REGEX_TEAM_ID = "^g_teamId = (.*);";
	const char* REGEX_CATEGORY_ID = "^g_categoryListId = (.*);";

	// post body attributes
	const char* ATTR_LIST_ID = "listId";
	const char* ATTR_LIST_NAME = "name";
	const char* ATTR_LIST_TYPE = "listType";

	const char* ATTR_ITEM_ID = "itemId";
	const char* ATTR_ITEM_CROSSED = "crossedOff";
	const char* ATTR_ITEM_VALUE = "value";
	const char* ATTR_ITEM_CATEGORY = "categoryId";
	const char* ATTR_COMMAND = "command";
	const char* ATTR_TEAM_ID = "teamId";


	// properties of returned data
	const char* PROP_LIST = "list";
	const char* PROP_ITEMS = "items";

	const int NO_ID_SPECIFIED = -1;

}

OurGroceries::OurGroceries()
	: m_username()
	, m_password()
	, m_teamId(NO_ID_SPECIFIED)
	, m_sessionCookie(NO_ID_SPECIFIED)
	, m_loggedIn(false)
{}

void OurGroceries::Initialize(std::string filedb)
{

}

void OurGroceries::GetLists(std::vector<std::string>& lists)
{}

void OurGroceries::GetListItems(const ItemId id, std::vector<std::string>& list)
{}

void OurGroceries::GetCategories(std::vector<std::string>& categories)
{}

void OurGroceries::CreateList(const std::string& name)
{}

void OurGroceries::CreateCategory(const std::string& name, const std::string& type)
{}

void OurGroceries::ToggleItemCrossedOff(ItemId list_id, ItemId item_id, bool cross_off)
{}

ItemId OurGroceries::AddItemToList(ItemId list_id, const std::string& name, const std::string& category)
{
	return 0;
}

void OurGroceries::RemoveItemFromList(ItemId list_id, ItemId item_id)
{}


void OurGroceries::login()
{}

ItemId OurGroceries::getItemId()
{
	return 0;
}

void OurGroceries::getSessionCookie()
{}

void OurGroceries::postCommand(const std::string& command, const Payload& payload, bool other_payload)
{

	if (!m_loggedIn)
		login();

	//Payload commanded_payload = std::make_pair(command, m_sessionCookie);



}