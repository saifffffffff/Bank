#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferRecordLine(clsBankClient::stTransferRecord TransferRecord) {
		cout << "\t\t  | " << TransferRecord.Date_Time;
		cout << " | " <<setw(6)<<left <<  TransferRecord.SenderAccountNumber ;
		cout << " | " <<setw(6)<<left <<  TransferRecord.RecieverAccountNumber ;
		cout << " | " <<setw(7)<<left <<  TransferRecord.TrasnferedAmout ;
		cout << " | " <<setw(9)<<left <<  TransferRecord.SenderAccountBalance ;
		cout << " | " <<setw(9)<<left <<  TransferRecord.RecieverAccountBalance ;
		cout << " | " <<setw(10)<<left <<  TransferRecord.Username << "|" << endl;

	}

public:
	static void ShowTransferLogScreen() {

		vector <clsBankClient::stTransferRecord> vTransferRecords = clsBankClient::GetTransferRecordsListScreen();
		_DrawScreenHeader("\t   Transfer Log", enAlignment::Center);
		cout << "\n\n\t\t  ______________________________________________________________________________________\n\n";
		cout << setw(20) << "| " << setw(19) << left << "Date/Time ";
		cout << "| " << setw(5)<< left << "s.Acct ";
		cout << "| " << setw(5)<< left << "r.Acct ";
		cout << "| " << setw(7)<< left << "Ammount ";
		cout << "| " << setw(7)<< left << "s.Balance ";
		cout << "| " << setw(7)<< left << "r.Balance ";
		cout << "| " << setw(8)<< left << "User name |";
		cout << "\n\t\t  ______________________________________________________________________________________\n";
		
		
		for (auto& T : vTransferRecords) {
			_PrintTransferRecordLine(T);
		}
		cout << "\t\t  ______________________________________________________________________________________\n\n\n";
	}
};

