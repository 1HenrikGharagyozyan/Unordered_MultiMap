#include <iostream>

#include "Unordered_MultiMap.h"

int main() 
{
    Unordered_MultiMap<int, std::string> map;

    // insert
    map.insert({ 1, "one" });
    map.insert({ 2, "two" });
    map.insert({ 1, "uno" });
    map.insert({ 3, "three" });

    // print
    std::cout << "Contents:\n";
    for (const auto& [key, value] : map)
        std::cout << key << " => " << value << "\n";

    // count
    std::cout << "\nCount for key 1: " << map.count(1) << "\n";

    // find
    auto it = map.find(2);
    if (it != map.end())
        std::cout << "Found key 2: " << it->second << "\n";

    // equal_range
    std::cout << "\nEqual range for key 1:\n";
    auto [first, last] = map.equal_range(1);
    for (; first != last; ++first)
        std::cout << first->first << " => " << first->second << "\n";

    // erase one entry with key = 1
    map.erase(1);
    std::cout << "\nAfter erasing one value for key 1:\n";
    for (const auto& [key, value] : map)
        std::cout << key << " => " << value << "\n";

    // clear
    map.clear();
    std::cout << "\nAfter clear, size = " << map.size() << "\n";
}
