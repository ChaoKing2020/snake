#include <iostream>
#include <map>

int main()
{
    std::map<std::string, std::pair<std::string, std::string>> mp;
    mp["a"] = {"11", "22"};
    mp.insert({"b", {"33", "44"}});
    for(const auto& item : mp) {
        std::cout << item.first << " " << item.second.first << std::endl;
    }
    return 0;
}