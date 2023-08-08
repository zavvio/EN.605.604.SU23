#pragma once
#include <vector>
#include "DevUtil.h"
#include "Listener.h"
#include "Passenger.h"
#include "PassengerCheckPointListener.h"
#include "Record.h"

// This is not an actual part of the airport security system;
// instead, it is a virtual part to help log all passenger info;
// all passengers passed through a scanning station would be processed here at last.
class ProcessInfoListener : public Listener
{
public:
    ProcessInfoListener() = delete;
    ProcessInfoListener(Record& record) : record{ record } {};
    ~ProcessInfoListener();
    void update(double currTime = 0.0) override;
    void addUpstream(std::shared_ptr<PassengerCheckPointListener>& upstream);

private:
    std::vector<std::shared_ptr<PassengerCheckPointListener>> upstreams;
    Record& record;
};
