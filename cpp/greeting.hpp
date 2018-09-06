#pragma once
#include <string>

namespace hello {

class Greeting {
    std::string prefix;

public:
    explicit Greeting(std::string prefix)
        : prefix(std::move(prefix))
    {
    }

    Greeting(Greeting const&) = default;
    Greeting(Greeting&&) = default;
    Greeting& operator=(Greeting const&) = default;
    Greeting& operator=(Greeting&&) = default;

    virtual ~Greeting() = default;

    std::string greet(std::string const& name);
};

} // namespace hello

