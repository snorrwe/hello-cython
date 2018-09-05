#include "greeting.hpp"
#include <sstream>

using namespace hello;

std::string Greeting::greet(std::string const& name)
{
    const auto print = [&]() {
        std::stringstream buff;
        buff << prefix << ' ' << name << "!\n";
        return buff.str();
    };
    return print();
}

