# Bank Management System

A C++ console-based banking management system built with Visual Studio. This application provides comprehensive banking operations including client management, user authentication, transactions, currency exchange, and activity logging.

## Features

### Client Management
- **View Client List** - Display all bank clients with their details
- **Add New Client** - Register new clients with account information
- **Delete Client** - Remove clients from the system
- **Update Client Info** - Modify existing client details
- **Find Client** - Search for clients by account number

### User Management & Authentication
- **Login System** - Secure username/password authentication with 3-attempt limit
- **User Registration** - Track login activities
- **Manage Users** - Add, delete, update, and list system users
- **Role-based Access** - Different permission levels for users

### Transaction Operations
- **Deposit** - Add funds to client accounts
- **Withdraw** - Withdraw funds with balance validation
- **Transfer** - Transfer funds between accounts with transaction logging
- **Transfer Log** - View complete history of all transfers

### Currency Exchange
- **Currency Listing** - View all supported currencies with rates
- **Currency Calculator** - Convert between currencies
- **Update Currency Rates** - Modify exchange rates
- **Find Currency** - Search for specific currencies

### Activity Tracking
- **Login Register** - Track all user login activities with timestamps

## Project Structure

```
Bank/
├── Main.cpp                          # Entry point
├── Bank.sln                          # Visual Studio Solution
├── Bank.vcxproj                      # Visual Studio Project
├── Bank.vcxproj.filters              # Project filters
├── Global.h                          # Global variables
├── GlobalFiles.h                     # File paths configuration
├── clsScreen.h                       # Base screen class
├── clsInputValidate.h                # Input validation utilities
├── clsString.h                       # String manipulation utilities
├── clsUtil.h                         # Utility functions
├── clsDate.h                         # Date/time handling
├── clsPerson.h                       # Base person class
├── clsUser.h                         # User management
├── clsBankClient.h                   # Bank client management
├── clsCurrency.h                     # Currency management
├── clsCurrencyCalculator.h           # Currency conversion logic
├── clsMainScreen.h                   # Main menu screen
├── clsLoginScreen.h                  # Login screen
├── clsLoginRegisterScreen.h          # Login register screen
├── clsClientListScreen.h             # Client list display
├── clsAddClientScreen.h              # Add client screen
├── clsDeleteClientScreen.h           # Delete client screen
├── clsUpdateClientScreen.h           # Update client screen
├── clsFindClientScreen.h             # Find client screen
├── clsTransactionsScreen.h           # Transactions menu
├── clsDepositScreen.h                # Deposit screen
├── clsWithdrawScreen.h               # Withdraw screen
├── clsTransferScreen.h               # Transfer screen
├── clsTransferLogScreen.h            # Transfer log screen
├── clsManageUsersScreen.h            # Manage users menu
├── clsListUsersScreen.h              # List users screen
├── clsAddUserScreen.h                # Add user screen
├── clsDeleteUserScreen.h             # Delete user screen
├── clsUpdateUserScreen.h             # Update user screen
├── clsFindUserScreen.h               # Find user screen
├── clsCurrencyExchangeScreen.h       # Currency exchange menu
├── clsListCurrenciesScreen.h         # List currencies screen
├── clsFindCurrencyScreen.h           # Find currency screen
├── clsUpdateCurrencyRateScreen.h     # Update currency rate screen
├── clsCurrencyCalculatorScreen.h     # Currency calculator screen
├── clsPeroid.h                       # Period/date range handling
└── Bank_files/                       # Data storage directory
    ├── Clients.txt                   # Client data
    ├── users.txt                     # User data
    ├── LoginRegister.txt             # Login activity log
    ├── TransferLog.txt               # Transfer transaction log
    └── Currencies.txt                # Currency data
```

## Data Storage

The system uses text files for data persistence (located in `Bank_files/`):
- **Clients.txt** - Client records (Account#, Name, Email, Phone, Pin, Balance)
- **users.txt** - User accounts (Username, Password, Permissions)
- **LoginRegister.txt** - Login history (Date, Time, Username, Password, Permissions)
- **TransferLog.txt** - Transfer transactions (Date, Sender, Receiver, Amount, Balances, User)
- **Currencies.txt** - Currency rates (Country, Code, Name, Rate)

## Building & Running

### Prerequisites
- Visual Studio 2019 or later
- Windows OS (uses `system("clear")` and `system("pause>0")`)

### Steps
1. Open `Bank.sln` in Visual Studio
2. Build the solution (Ctrl+Shift+B)
3. Run the application (F5 or Ctrl+F5)

### Command Line Build
```bash
# Using MSBuild
msbuild Bank.sln /p:Configuration=Release
```

## Default Login

The system requires user authentication. Check `Bank_files/users.txt` for existing users or create new ones through the Manage Users menu (requires admin permissions).

## Architecture

The application follows a layered architecture:
- **UI Layer** - Screen classes (`*Screen.h`) handle user interaction
- **Business Logic Layer** - Core classes (`clsBankClient`, `clsUser`, `clsCurrency`) contain business rules
- **Data Access Layer** - File-based persistence through static methods in business classes
- **Utility Layer** - Helper classes for validation, string manipulation, dates

## Key Classes

| Class | Responsibility |
|-------|----------------|
| `clsBankClient` | Client CRUD operations, transactions (deposit/withdraw/transfer) |
| `clsUser` | User authentication, permissions, login tracking |
| `clsCurrency` | Currency data and exchange rates |
| `clsCurrencyCalculator` | Currency conversion calculations |
| `clsMainScreen` | Main menu navigation |
| `clsLoginScreen` | Authentication flow |

## Permissions System

Users have permission flags:
- `pListClients` - View client list
- `pAddNewClient` - Add clients
- `pDeleteClient` - Delete clients
- `pUpdateClient` - Update clients
- `pFindClient` - Find clients
- `pTransactions` - Perform transactions
- `pManageUsers` - Manage users
- `pLoginRegister` - View login register
- `pCurrencyExchange` - Access currency exchange

## License

This project is for educational purposes.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request