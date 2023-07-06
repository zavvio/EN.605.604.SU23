#include "CommandLineUserInterface.h"
using namespace std;

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

// A one-time prompt is presented during start-up to help set up the vending machine.
CommandLineUserInterface::CommandLineUserInterface(VendingMachine& machine) : aMachine{ machine }
{
    // Interactive prompt to set up the vending machine during CLI initialization.
    unsigned option = 0;
    cout << "Welcome to the Vending Machine Command Line User Interface." << endl;
    do
    {
        cout << "\tEnter 1 to initialize vending machine with default config." << endl;
        cout << "\tEnter 2 to initialize vending machine with custom config." << endl;
        cout << "Option (1 or 2): ";
        cin >> option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (option != 1 && option != 2);

    if (option == 1) // ========== DEFAULT CONFIG ==========
    {
        // Summary for default config.
        cout << "Initializing vending machine with..." << endl;
        for (const LineItem& item : defaultConfig)
        {
            cout << "\t" << item.count << " ($" << item.price << ") " << item.name << endl;
        }
        aMachine.initialize();
    }
    else // ========== CUSTOMIZED CONFIG ==========
    {
        // Configure number of dispensing column.
        int numOfDispensingColumn;
        do
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "What is the number of dispensing column? [min: 1] ";
            cin >> numOfDispensingColumn;
        } while (cin.fail() || numOfDispensingColumn < 1);
        cout << "There will be " << numOfDispensingColumn << " dispensing columns." << endl;

        // Configure maximum dispensing column count.
        int maxDispensingColumnCount;
        do
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "What is the max count per dispensing column? [min: 5] ";
            cin >> maxDispensingColumnCount;
        } while (cin.fail() || maxDispensingColumnCount < 5);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Each column will hold at most " << maxDispensingColumnCount << " drinks." << endl;

        // Generate custom drink inventory, one LineItem per dispensing column.
        vector<LineItem> customConfig;
        string name;
        double price;
        int count;
        for (int i = 0; i < numOfDispensingColumn; i++)
        {
            cout << "Name of the drink on column " << i << "? ";
            cin >> name;
            do
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "How much is each " << name << "? ";
                cin >> price;
            } while (cin.fail() || price <= 0);
            do
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "How many " << name << " shall be inserted? [max: " << maxDispensingColumnCount << "] ";
                cin >> count;
            } while (cin.fail() || count < 0 || count > maxDispensingColumnCount);
            customConfig.push_back(LineItem(name, price, count));
        }

        // Summary for customized config.
        cout << "Initializing vending machine with..." << endl;
        for (LineItem& item : customConfig)
        {
            cout << "\t" << item.count << " ($" << item.price << ") " << item.name << endl;
        }
        aMachine.initialize(maxDispensingColumnCount, customConfig);
    }
    cout << "Vending machine and CLI are initialized succesfully." << endl;
}

// A continuous loop to manipulate the vending machine until user seeks to terminate.
void CommandLineUserInterface::execute()
{
    std::unique_ptr<Drink> drink;
    std::map<MoneyType, unsigned> refund;
    double balance;
    // Loop until the terminate option is chosen.
    while (menuChoice != (mainMenuChoices.size() - 1))
    {
        displayMainMenu();
        getUserMenuInput(mainMenuChoices.size() - 1);
        switch (menuChoice)
        {
        case 1: // 1 - insert money
            displayMoneyMenu();
            getUserMenuInput(moneyMenuChoices.size() - 1);
            processMoneyMenuInput();
            break;
        case 2: // 2 - press refund button
            aMachine.pressRefundButton();
            aMachine.processRequests();
            break;
        case 3: // 3 - press button for dispensing column
            balance = aMachine.getInsertedMoney();
            displayColumnMenu();
            getUserMenuInput(aMachine.getNumOfDispensingColumn());
            processColumnMenuInput();
            aMachine.processRequests();
            if (balance == aMachine.getInsertedMoney())
            {
                cout << "Purchase failed." << endl;
            }
            else
            {
                cout << "Purchase successful." << endl;
            }
            break;
        case 4: // 4 - get dispensed drink
            drink = aMachine.getDispensedDrink();
            if (drink != nullptr)
            {
                cout << "Retrieved a " << drink->getName() << "." << endl;
                drink = nullptr;
            }
            else
            {
                cout << "There is nothing in delivery slot." << endl;
            }
            break;
        case 5: // 5 - get refund
            refund = aMachine.getRefund();
            displayRefund(refund);
            break;
        case 6: // 6 - terminate
            cout << "Program Ending." << endl;
            break;
        default:
            cerr << "[ERROR] Unrecognized menu choice." << endl;
        }
    }
}

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================

// Main menu for overall functionalities of the vending machine.
void CommandLineUserInterface::displayMainMenu() const
{
    double balance = aMachine.getInsertedMoney();
    cout << fixed << setprecision(2) << mainMenuChoices[0] << balance << "; Main menu:" << endl;
    for (int i = 1; i < mainMenuChoices.size(); i++)
    {
        cout << mainMenuChoices[i] << endl;
    }
}

// Money menu has specific functionalities w.r.t. the coin/bill slot.
void CommandLineUserInterface::displayMoneyMenu() const
{
    double balance = aMachine.getInsertedMoney();
    cout << fixed << setprecision(2) << moneyMenuChoices[0] << balance << "; Insert money:" << endl;
    for (int i = 1; i < moneyMenuChoices.size(); i++)
    {
        cout << moneyMenuChoices[i] << endl;
    }
}

// Dispensing column menu shows basic info from each column and presents the corresponding dispensing button.
void CommandLineUserInterface::displayColumnMenu() const
{
    std::string name;
    double price;
    bool empty;
    size_t maxSize, currSize;
    double balance = aMachine.getInsertedMoney();
    cout << fixed << setprecision(2) << mainMenuChoices[0] << balance << "; Press button for dispensing column:" << endl;
    for (int i = 0; i < aMachine.getNumOfDispensingColumn(); i++)
    {
        aMachine.getColumnInfo(i, name, price, empty, maxSize, currSize);
        if (empty)
        {
            cout << "\t" << i + 1 << " - column " << i + 1 << " is empty, pressing this will have no effect." << endl;
        }
        else
        {
            cout << "\t" << i + 1 << " - column " << i + 1 << ", " << name << " (" << price << ")" << endl;
        }
    }
}

// Parse the stash of refunded money currencies for presentation.
void CommandLineUserInterface::displayRefund(std::map<MoneyType, unsigned> refund) const
{
    double total = 0.0;
    unsigned count = 0;
    cout << "Retrieved refund of:" << endl;
    count = refund.at(MoneyType::NICKEL);
    if (count != 0)
    {
        cout << "\t" << count << " Nickel ($0.05)" << endl;
        total += count * 0.05;
    }
    count = refund.at(MoneyType::DIME);
    if (count != 0)
    {
        cout << "\t" << count << " Dime ($0.10)" << endl;
        total += count * 0.10;
    }
    count = refund.at(MoneyType::QUARTER);
    if (count != 0)
    {
        cout << "\t" << count << " Quarter ($0.25)" << endl;
        total += count * 0.25;
    }
    count = refund.at(MoneyType::ONE_DOLLAR);
    if (count != 0)
    {
        cout << "\t" << count << " One Dollar ($1.00)" << endl;
        total += count * 1.00;
    }
    count = refund.at(MoneyType::FIVE_DOLLAR);
    if (count != 0)
    {
        cout << "\t" << count << " Five Dollar ($5.00)" << endl;
        total += count * 5.00;
    }
    count = refund.at(MoneyType::TEN_DOLLAR);
    if (count != 0)
    {
        cout << "\t" << count << " Ten Dollar ($10.00)" << endl;
        total += count * 10.00;
    }
    count = refund.at(MoneyType::TWENTY_DOLLAR);
    if (count != 0)
    {
        cout << "\t" << count << " Twenty Dollar ($20.00)" << endl;
        total += count * 20.00;
    }
    cout << "Total refund: $" << std::fixed << std::setprecision(2) << total << endl;
}

// Accept integer based user input for an intended action.
void CommandLineUserInterface::getUserMenuInput(size_t maxOption)
{
    do
    {
        cout << "Please enter one of the options [1 - " << maxOption << "]: ";
        cin >> menuChoice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (menuChoice < 1 || menuChoice > maxOption);
}

// Insert the appropriate money currency into the vending machine as requested.
void CommandLineUserInterface::processMoneyMenuInput()
{
    switch (menuChoice)
    {
    case 1:
        aMachine.insertMoney(MoneyType::NICKEL);
        break;
    case 2:
        aMachine.insertMoney(MoneyType::DIME);
        break;
    case 3:
        aMachine.insertMoney(MoneyType::QUARTER);
        break;
    case 4:
        aMachine.insertMoney(MoneyType::ONE_DOLLAR);
        break;
    case 5:
        aMachine.insertMoney(MoneyType::FIVE_DOLLAR);
        break;
    case 6:
        aMachine.insertMoney(MoneyType::TEN_DOLLAR);
        break;
    case 7:
        aMachine.insertMoney(MoneyType::TWENTY_DOLLAR);
        break;
    default:
        break;
    }
    menuChoice = 0;
}

// Acknowledge the dispensing column button press action.
void CommandLineUserInterface::processColumnMenuInput()
{
    aMachine.pressColumnButton(menuChoice - 1);
    menuChoice = 0;
}
