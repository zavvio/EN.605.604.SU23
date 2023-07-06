#pragma once
#include <map>
#include <memory>
#include <utility>
#include <vector>
#include "Drink.h"
#include "DrinkStorage.h"
#include "DispensingColumnStorage.h"
#include "MoneyStorage.h"
#include "MainMoneyStorage.h"
#include "SelectionButton.h"
#include "DevUtil.h"

// LineItem represents inventory for a certain type of merchandise;
// it's used as guideline to generate sufficient merchandise object to fill the vending machine.
typedef struct LineItem
{
    std::string name;
    double price;
    unsigned count;
    LineItem(std::string name, double price, unsigned count) : name{ name }, price{ price }, count{ count } {}
} LineItem;

// Hardcoded default configuration for vending machine initialization if customized configuration is not provided.
const std::vector<LineItem> defaultConfig = {
    {"Coke",     1.5, 3},
    {"Pepsi",    1.5, 3},
    {"Lemonade", 2.5, 3}
};

// A vending machine has some amount of dispensing columns to hold merchandises (not necessary drinks);
// and the matching amount of dispensing buttons associated with each dispensing column.
// It also has a delivery slot to hold all purchased merchandise dispensed from the columns prior to retrival by user.
// It has a coin/bill slot for user to input money currencies, which also keep track of the balance.
// A user may use the vending machine's refund button to request full refund from the coin/bill slot.
// Refunded money are placed into the refund slot prior to retrival by user.
class VendingMachine
{
public:
    void initialize(const unsigned maxCount = 5, const std::vector<LineItem>& configs = defaultConfig);
    void insertMoney(MoneyType type);
    double getInsertedMoney();
    void pressRefundButton();
    void pressColumnButton(unsigned index);
    std::map<MoneyType, unsigned> getRefund();
    std::unique_ptr<Drink> getDispensedDrink();
    size_t getNumOfDispensingColumn();
    void getColumnInfo(unsigned index, std::string& name, double& price, bool& empty, size_t& maxSize, size_t& currSize);
    unsigned refill(unsigned columnIndex, LineItem items);
    void processRequests();

private:
    bool initialized{ false };
    std::vector<std::unique_ptr<DispensingColumnStorage>> dispensingColumns;
    std::vector<std::unique_ptr<SelectionButton>> columnButtons;
    std::vector<std::pair<unsigned, unsigned>> button_column_pairings; // associate a button to a dispensing column
    std::unique_ptr<DrinkStorage> deliverySlot;
    MainMoneyStorage moneySlot{ 5 };
    MoneyStorage changeReturnSlot;
    SelectionButton refundButton;
};