#pragma once
#include <iostream>
#include <iomanip>
#include "clsDate.h"
#include "Global.h"
#include "clsUser.h"
using namespace std;
class clsScreen
{

protected:

	enum enAlignment {Right, Center, Left};

	static void _DrawScreenHeader(string Title ,enAlignment AlignmentType = Left ,string SubString = "") {
		string align = "";
		if (AlignmentType == Center)
			align = "\t\t\t\t\t";
		if (AlignmentType == Right)
			align = "\t\t\t\t\t\t\t\t";

		cout << align << "==================================\n";
		cout << align << Title << '\n';
		if (!SubString.empty())
			cout << align << SubString << '\n';

		cout  << align<<"date: " << clsDate::DateToString(clsDate()) << "   ";
		cout <<"User name: " << (SystemUser.IsEmpty() ? "Empty" : SystemUser.Username) << endl;

		cout << align << "==================================\n";

	}


	static bool _CheckAccessRights(clsUser::enPermissions permission){
		if (!SystemUser.CheckPermission(permission)) {
			_DrawScreenHeader("\t    Not Allowed", enAlignment::Center, " You don't have the permission to \n\t\t\t\t\t      perform this operatoin");
			
			return false;
		}
		return true;
		
	}
};

