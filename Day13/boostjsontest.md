USING BOOST JSON THE LINES CAN BE PARSED

```cpp
#define BOOST_JSON_STANDALONE
#include <boost/json.hpp>
#include <boost/json/src.hpp> // header-only
#include <iomanip>
#include <iostream>
namespace json = boost::json;

int main() {
    std::string input = R"(
         [
            {
            "username": "123456",
            "useraddress": "abc",
            "data": [
                        {
                            "schedule": true,
                            "task": "abc",
                            "risk": "1",
                        } 
                    ],
             "date": "0000-00-00"
            }
        ])";


    boost::json::parse_options options;
    options.allow_trailing_commas = true;
    auto json = boost::json::parse(input, {}, options);

    for (auto &el : json.as_array()) {
        std::cout << el.at("date") << "\n";
    }

    std::string test = "[1,[2,[3,[4,[5,6,7]]]],8,9]";
    auto js = boost::json::parse(test, {}, options);
    int i = 0;
    for(auto& el : js.as_array()){
        std::cout<<i++<<": ";
        std::cout<<el<<'\n';
    }
}
```


OUTPUTS: 
```
    "0000-00-00"
    0: 1
    1: [2,[3,[4,[5,6,7]]]]
    2: 8
    3: 9
```