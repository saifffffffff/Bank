#pragma once
#include <string>
#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord RegisterUserRecord) {
		
		cout << setw(8) << left << "" << "\t\t     | " << left << setw(22) << RegisterUserRecord.Date_Time;
		cout << "| " << setw(10) << left <<  RegisterUserRecord.Username;
		cout << "| " << setw(12) << left  << RegisterUserRecord.Password;
		cout << "| " << setw(11) << left << to_string(RegisterUserRecord.Permissions) << " |";
		cout << endl;

	}

public:

	static void ShowLoginRegisterScreen() {
		
		
		if (!_CheckAccessRights(clsUser::enPermissions::pShowLoginRegister))
			return;
		
		_DrawScreenHeader("\tLogin Register Screen", enAlignment::Center);
		
		cout << setw(8) << left << "" << "\n\t\t\t     _________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "\t\t     | " << left << setw(22) << "Date/time";
		cout << "| " << left << setw(10) << "User name";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(12) << "Permissions |";
		cout << setw(8) << left << "" << "\n\t\t\t     _________________________________________________________________\n";
	
		vector <clsUser::stLoginRegisterRecord> vLoginRegisters = clsUser::GetLoginRegisterList();

		for (auto& loginRegisterRecord : vLoginRegisters) {
			_PrintLoginRegisterRecordLine(loginRegisterRecord);
		}

		cout <<  "\t\t\t     _________________________________________________________________\n";



	}

};

