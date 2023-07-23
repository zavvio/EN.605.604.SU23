#pragma once
#include <vector>
#include "DevUtil.h"
#include "Listener.h"
#include "Passenger.h"
#include "PassengerCheckPointListener.h"
#include "Record.h"

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
