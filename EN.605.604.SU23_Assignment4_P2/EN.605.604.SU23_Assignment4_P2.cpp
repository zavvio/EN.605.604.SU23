// EN.605.604.SU23_Assignment4_P2.cpp

#include <set>
#include "State.h"

using namespace std;

int main()
{
    cout << "Assignment 4 P2 - State and Capital City" << endl;

    set<unique_ptr<State>> states;
    set<unique_ptr<State>>::iterator itr;
    // Instantiating State the easy way.
    states.insert(make_unique<State>("Illinois", "Springfield"));
    states.insert(make_unique<State>("Wisconsin", "Madison"));
    states.insert(make_unique<State>("California", "Sacramento"));
    states.insert(make_unique<State>("New York", "Albany"));
    // Instantiating State the hard way.
    unique_ptr<State> state = make_unique<State>("");
    auto insertResult = states.insert(std::move(state));
    itr = insertResult.first;
    itr->get()->setStateName("Alaska");
    itr->get()->setCapitalCityName("Juneau");
    // Displaying each state.
    cout << "##### State Name ##### | ##### Capital City Name #####" << endl;
    for (itr = begin(states); itr != end(states); ++itr)
    {
        cout << setw(15) << itr->get()->getStateName() << setw(30) << itr->get()->getCapitalCityName() << endl;
    }
    return 0;
}