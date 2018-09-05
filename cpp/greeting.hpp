#pragma once
#include <string>

namespace hello {

class Greeting {
    std::string prefix;

public:
    Greeting(std::string const& prefix)
        : prefix(prefix)
    {
    }

    std::string greet(std::string const& name);
};

}

