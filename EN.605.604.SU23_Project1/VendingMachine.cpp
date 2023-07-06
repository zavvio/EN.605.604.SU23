#include "VendingMachine.h"

// Set the vending machine up using configurations as specified by LineItems.
// Each LineItem record is expected to represent a unique product (drink) type.
// The vending machine will create the same amount of dispensing columns and buttons as the number of unique item types.
// Each dispensing button is associated with a unique dispensing column;
// it's possible, despite illogical to associate multiple dispensing buttons to the same column.
// The vending machine will also construct/keep a delivery slot.
// A vending machine may only be initialized once.
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
        button_column_pairings.push_back(std::make_pair(i, i));

        // Fill the dispensing column with drinks
        /*std::unique_ptr<Drink> newDrink;
        for (unsigned j = 0; j < configs[i].count; j++)
        {
            newDrink = std::make_unique<Drink>(configs[i].name, configs[i].price);
            dispensingColumns[i]->insert(newDrink);
        }*/
        refill(i, configs[i]);
    }

    deliverySlot = std::make_unique<DrinkStorage>(maxCount * configs.size());

    initialized = true;
}

// Let user add money to the coin/bill slot.
void VendingMachine::insertMoney(MoneyType type)
{
    moneySlot.insertMoney(type);
}

// Query the current balance inserted to the coin/bill slot.
// This only represents the money value available for purchase or refund.
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

// Extract a stash of money currencies out of the vending machine.
// Format of the output is a count for each type of money currency.
// The money value from the stash should be calculated by the receiver, if necesary.
std::map<MoneyType, unsigned> VendingMachine::getRefund()
{
    return changeReturnSlot.dispenseMoney(changeReturnSlot.getTotalValue());
}

// Extract the first avaiable drink, in the delivery slot, out of the vending machine.
// The vending machine will transfer/release ownership of the drink beyond this point.
std::unique_ptr<Drink> VendingMachine::getDispensedDrink()
{
    std::unique_ptr<Drink> drink = deliverySlot->dispense();
    return drink;
}

size_t VendingMachine::getNumOfDispensingColumn()
{
    return dispensingColumns.size();
}

// Retrieve current basic information of a dispensing column.
void VendingMachine::getColumnInfo(unsigned index, std::string& name, double& price, bool& empty, size_t& maxSize, size_t& currSize)
{
    if (index >= dispensingColumns.size())
    {
        throw std::out_of_range("");
    }
    empty = dispensingColumns[index]->isEmpty();
    name = dispensingColumns[index]->getDrinkName();
    price = dispensingColumns[index]->getDrinkPrice();
    maxSize = dispensingColumns[index]->getMaxCount();
    currSize = dispensingColumns[index]->getCurrentCount();
}

// Refill the vending machine by constructing/adding a number of products as specified in LineItem.
unsigned VendingMachine::refill(unsigned columnIndex, LineItem items)
{
    std::unique_ptr<Drink> newDrink;
    unsigned i;
    for (i = 0; i < items.count && !dispensingColumns[columnIndex]->isFull(); i++)
    {
        newDrink = std::make_unique<Drink>(items.name, items.price);
        dispensingColumns[columnIndex]->insert(newDrink);
    }
    return i;
}

// Ideally a background thread but can be actively triggered;
// This function ensures any button press requests will be captured and processed
// by the vending machine, the button could be for dispensing columns or refund.
void VendingMachine::processRequests()
{
    // Check all dispensing column buttons
    std::unique_ptr<Drink> drink;
    for (std::pair<unsigned, unsigned> p : button_column_pairings)
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