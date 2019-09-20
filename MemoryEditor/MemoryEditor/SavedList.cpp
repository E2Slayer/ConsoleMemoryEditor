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
	system("cls");


	int userInput = 0;
	while (userInput != 9 )
	{
		int i_Number = 1;
		for (auto i : savedList)
		{
			std::cout << "[" << i_Number << "] = " "Address : " << std::hex << i->address << " / Description : " << i->description << " / Types " << std::dec << i->type << std::endl;
			++i_Number;
		}
		
		std::cout << "===============================" << std::endl;
		std::cout << "0 : Create a New Address" << std::endl;
		std::cout << "1 : Edit a Saved Address" << std::endl;
		std::cout << "2 : Delete a Saved Address" << std::endl;
		std::cout << "===============================" << std::endl;
		std::cout << "9 : Back" << std::endl;
		std::cout << "===============================" << std::endl;
		std::cout << "Please, enter a number : ";
		std::cin >> userInput;

		if(userInput == 9)
		{
			break;
		}


		int num = 0;
		switch (userInput)
		{
		case 0:

			AddAList();

			break;
		case 1:
			std::cout << "Which one do you want to modify? : ";
			std::cin >> std::dec >> num;
			--num;
			EditAList(num);
			break;
		case 2:
			std::cout << "Which one do you want to Delete? : ";
			std::cin >> std::dec >> num;
			--num;
			DeleteAList(num);
			break;
		default:
			break;
		}
		

		

	}
}

void SavedList::AddAList()
{
	uintptr_t temp = 0x0;
	std::cout << "New Address : ";
	//std::getline(std::cin, str);
	std::cin >> std::hex >> temp;

	std::string str = "No Description";
	std::cout << "Description of this address : ";
	//std::getline(std::cin, str);
	std::cin >> str;

	int value = 0;
	std::cout << "What kind of Type is it ? (0: Byte / 1: 2 Bytes / 2: 4 Bytes) : ";
	std::cin >> std::dec >> value;


	auto t = SavedList();
	t.SaveAnAddress(temp, str, Types(value));
}

void SavedList::EditAList(int num)
{
	int userInput = 0;
	while (userInput != 9)
	{


		std::cout << "===============================" << std::endl;
		std::cout << "0 : Edit an Address" << std::endl;
		std::cout << "1 : Edit a Description" << std::endl;
		std::cout << "2 : Edit a Type" << std::endl;
		std::cout << "===============================" << std::endl;
		std::cout << "9 : Back" << std::endl;
		std::cout << "===============================" << std::endl;
		std::cout << "Please, enter a number : ";
		std::cin >> userInput;

		if (userInput == 9)
		{
			break;
		}

		uintptr_t temp = 0x0;
		std::string str = "No Description";
		int tempi = 0;

		switch (userInput)
		{
		case 0:

			std::cout << "Enter a New Address : ";
			std::cin >> std::hex >> temp;
			savedList[num]->address = temp;

			break;
		case 1:

			std::cout << "Enter a New Description : ";
			std::cin >> str;
			savedList[num]->description = str;
			break;
		case 2:

			std::cout << "Enter a New Type : ";
			std::cin >> std::dec >> tempi;
			savedList[num]->type = Types(tempi);
			break;
		default:
			break;
		}
		
	}
	
}

void SavedList::DeleteAList(int num)
{

	savedList.erase(savedList.begin() + num);

	std::cout << "List [ " << num+1 << "] has been removed"  << std::endl;
}
