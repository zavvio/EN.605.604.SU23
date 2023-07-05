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

typedef struct LineItem
{
    std::string name;
    double price;
    unsigned count;
    LineItem(std::string name, double price, unsigned count) : name{ name }, price{ price }, count{ count } {}
} LineItem;

const std::vector<LineItem> defaultConfig = {
    {"Coke",     1.5, 3},
    {"Pepsi",    1.5, 3},
    {"Lemonade", 2.5, 3}
};

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
    // void refill(unsigned columnIndex, LineItem items);
    void processRequests();

private:
    bool initialized{ false };
    std::vector<std::unique_ptr<DispensingColumnStorage>> dispensingColumns;
    std::vector<std::unique_ptr<SelectionButton>> columnButtons;
    std::vector<std::pair<unsigned, unsigned>> column_button_pairings; // pair<button, column>
    std::unique_ptr<DrinkStorage> deliverySlot;
    MainMoneyStorage moneySlot{ 5 };
    MoneyStorage changeReturnSlot;
    SelectionButton refundButton;
};