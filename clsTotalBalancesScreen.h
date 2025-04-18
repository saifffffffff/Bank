#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"


class clsTotalBalancesScreen : protected clsScreen
{

private:
	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << setw(20) << "" << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(10) << left << Client.AccountBalance ;
		cout << setw(8) << left << "" << "| " << setw(26) << left << Client.AccountNumber();
		cout << "|";
	}

public:

	static void ShowTotalBalancesScreen() {
		
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string substr = "\t  (" + to_string(vClients.size()) + ") " + "Client(s) ";
		_DrawScreenHeader("\t  Total Balances", enAlignment::Center, substr);
		
		
		cout << setw(20) << "" << left << "\n\t\t    _______________________________________________________________________\n\n";

		cout << setw(20) << "" << left << "| " << left << setw(20) << "Client Name";
		cout << setw(8) << left << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "| " << left << setw(15) << "Accout Number       |";

		cout << setw(20) << "" << left << "\n\t\t    _______________________________________________________________________\n\n";

	

		if (vClients.size() == 0)
			cout << "\t\t\t\t\tNo avialable clients in system \n";
		
		else {
			for (clsBankClient& client : vClients) {
				_PrintClientRecordLine(client);
				cout << endl;
			}
		}
		cout << setw(20) <<  "" <<left  << "_______________________________________________________________________\n\n";
	
		cout << "\t\t    Total Balances : " << clsBankClient::GetTotalBalances() << " (" << clsUtil::DigitToString(clsBankClient::GetTotalBalances()) << ") \n" << endl;	

	}


};