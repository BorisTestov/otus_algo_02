#pragma once

#include "tester.h"

class StringLengths : public ITask {
public:
    virtual std::string Run(std::vector<std::string> data) override final {
        std::string line = data.at(0);
        int length = line.size();
        return std::to_string(length);
    }
};