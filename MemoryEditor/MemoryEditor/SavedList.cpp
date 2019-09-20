#include "SavedList.h"

void SavedList::SaveAnAddress(uintptr_t add, std::string str, Types type)
{
	//uintptr_t add2 = 0x44;
	AddressInfo* temp = new AddressInfo();
	temp->address = add;
	temp->description = str;
	temp->type = type;
	savedList.push_back(temp);
}

void SavedList::ShowAllList()
{
	for(auto i : savedList)
	{
		std::cout << "Address : " << std::hex << i->address << " Description : " << i->description << " Types " << std::dec << i->type << std::endl;
	}
}
