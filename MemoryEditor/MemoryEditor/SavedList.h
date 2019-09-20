#pragma once
#include "AddressInfo.h"
#include <vector>


static std::vector<AddressInfo*> savedList;

class SavedList
{
public:
	
	SavedList()
	{
		
	};
	void SaveAnAddress(uintptr_t add, std::string str, Types type);

	void ShowAllList();

	void AddAList();
	
	void EditAList(int num);

	void DeleteAList(int num);
};

