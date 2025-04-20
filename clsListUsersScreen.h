#pragma once
#include <vector>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
class clsListUsersScreen : protected clsScreen
{
private:

	static void _PrintUserRecordLine(clsUser User)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << User.Username;
		cout << "| " << setw(20) << left << User.FullName();
		cout << "| " << setw(12) << left << User.PhoneNumber;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(8) << left << User.Permissions <<" |";
	}
	
public:
	static void ShowListUsersScreen() {
		vector <clsUser> vUsers = clsUser::GetUsersList();
		string subtitle = "\t   " + to_string(vUsers.size()) + " User(s)";
		_DrawScreenHeader("\t   List Users", enAlignment::Center, subtitle);


		
		cout << setw(8) << left << "" << "\n\t__________________________________________________________";
		cout << "____________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions |";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		if (vUsers.size() == 0)
			cout << "\t\t\t\t\tNo Users available in the system\n";
		
		else{
			for (const clsUser& user : vUsers) {
				_PrintUserRecordLine(user);
				cout << endl;
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

	}


};

