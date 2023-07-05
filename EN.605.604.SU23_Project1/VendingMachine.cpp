#include "VendingMachine.h"

// Set the vending machine up with pre-configured settings
void VendingMachine::initialize(const unsigned maxCount, const std::vector<LineItem>& configs)
{
    // Initialization can only be performed once.
    if (initialized) return;

    std::unique_ptr<DispensingColumnStorage> newDispensingColumn;
    std::unique_ptr<SelectionButton> newSelectionButton;
    for (unsigned i = 0; i < configs.size(); i++)
    {
        // Creating the dispensing column, selection button and pairing
        newDispensingColumn = std::make_unique<DispensingColumnStorage>(maxCount);
        dispensingColumns.push_back(std::move(newDispensingColumn));
        newSelectionButton = std::make_unique<SelectionButton>();
        columnButtons.push_back(std::move(newSelectionButton));
        column_button_pairings.push_back(std::make_pair(i, i));

        // Fill the dispensing column with drinks
        std::unique_ptr<Drink> newDrink;
        for (unsigned j = 0; j < configs[i].count; j++)
        {
            newDrink = std::make_unique<Drink>(configs[i].name, configs[i].price);
            dispensingColumns[i]->insert(newDrink);
        }
    }

    deliverySlot = std::make_unique<DrinkStorage>(maxCount * configs.size());

    initialized = true;
}

void VendingMachine::insertMoney(MoneyType type)
{
    moneySlot.insertMoney(type);
}

double VendingMachine::getInsertedMoney()
{
    return moneySlot.getCurrentSessionValue();
}

void VendingMachine::pressRefundButton()
{
    refundButton.press();
}

void VendingMachine::pressColumnButton(unsigned index)
{
    columnButtons[index]->press();
}

std::map<MoneyType, unsigned> VendingMachine::getRefund()
{
    return changeReturnSlot.dispenseMoney(changeReturnSlot.getTotalValue());
}

std::unique_ptr<Drink> VendingMachine::getDispensedDrink()
{
    std::unique_ptr<Drink> drink = deliverySlot->dispense();
    return drink;
}

size_t VendingMachine::getNumOfDispensingColumn()
{
    return dispensingColumns.size();
}

void VendingMachine::getColumnInfo(unsigned index, std::string& name, double& price, bool& empty, size_t& maxSize, size_t& currSize)
{
    if (index >= dispensingColumns.size())
    {
        throw std::out_of_range("");
    }
    empty = dispensingColumns[index]->isEmpty();
    if (empty)
    {
        name = "<Empty>";
        price = 0.0;
        maxSize = dispensingColumns[index]->getMaxCount();
        currSize = dispensingColumns[index]->getCurrentCount();
    }
    else
    {
        name = dispensingColumns[index]->getDrinkName();
        price = dispensingColumns[index]->getDrinkPrice();
        maxSize = dispensingColumns[index]->getMaxCount();
        currSize = dispensingColumns[index]->getCurrentCount();
    }
}

void VendingMachine::processRequests()
{
    // Check all dispensing column buttons
    std::unique_ptr<Drink> drink;
    for (std::pair<unsigned, unsigned> p : column_button_pairings)
    {
        if (columnButtons[p.first]->isActivated())
        {
            // Check for inventory and if money balance is sufficient
            if (!dispensingColumns[p.second]->isEmpty() &&
                moneySlot.getCurrentSessionValue() >= dispensingColumns[p.second]->getDrinkPrice())
            {
                moneySlot.setCurrentSessionValue(
                    moneySlot.getCurrentSessionValue() - dispensingColumns[p.second]->getDrinkPrice()
                );
                drink = dispensingColumns[p.second]->dispense();
                deliverySlot->insert(drink);
            }
            columnButtons[p.first]->reset();
        }
    }

    // Check refund button
    if (refundButton.isActivated())
    {
        // Transfer current balance from moneySlot to changeReturnSlot
        changeReturnSlot.insertMoney(
            moneySlot.dispenseMoney(moneySlot.getCurrentSessionValue())
        );
        refundButton.reset();
    }
}