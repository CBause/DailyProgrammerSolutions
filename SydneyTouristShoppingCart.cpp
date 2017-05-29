#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct pricings {
    std::map<const char*, int> currentPricings {
        { "OH" , 300 },
        { "BC" , 110 },
        { "SK", 30 }
    };
    std::vector < std::pair <std::pair<const char*, int>, std::pair<const char*, int> > > offers {
        { {"OH", 3 }, {"OH",-1} },
        { {"OH", 1}, {"SK", 1 } },
        { {"BC", 4}, {"", -20} } //empty string means plain discount
    };
};

int processOrder(const pricings &currentRules, vector<const char*> &currentOrder) {
    int result = 0;
    for (std::pair<const char*, int> p : currentRules.currentPricings) {
        result += p.second * ( std::count(currentOrder.begin(), currentOrder.end(), p.first));
    }
    for (std::pair <std::pair<const char*, int>, std::pair<const char*, int>> p : currentRules.offers) {
        std::pair<const char*, int> condition = p.first;
        std::pair<const char*, int> reward = p.second;
        if ( std::count(currentOrder.begin(), currentOrder.end(), condition.first) >= condition.second) {
            if (reward.first == "" ) {
                result += reward.second;
            } else if (reward.second < 0) {
                result += reward.second * currentRules.currentPricings.find(reward.first)->second;
            } else {
                int alreadyBooked = std::count(currentOrder.begin(), currentOrder.end(), reward.first);
                if (alreadyBooked == 0) {
                    currentOrder.push_back(reward.first);
                } else if(alreadyBooked >= 1) {
                    result -= currentRules.currentPricings.find(reward.first)->second;
                    alreadyBooked--;
                    for (int i=0; i < alreadyBooked; i++) {
                        currentOrder.push_back(reward.first);
                    }
                }
            }
        }
    }
    return result;
}

int main(int argc, char** argv) {
    std::vector<std::vector<const char*>> orders {
       vector<const char*>{"OH", "OH", "OH", "BC"},
       vector<const char*>{"OH","SK"},
       vector<const char*>{"BC", "BC", "BC", "BC", "BC", "OH"},
       vector<const char*>{"OH", "OH", "OH", "BC", "SK"}, 
       vector<const char*>{"OH", "BC", "BC", "SK", "SK"}, 
       vector<const char*>{"BC", "BC", "BC", "BC", "BC", "BC", "OH", "OH"} ,
       vector<const char*> {"SK", "SK", "BC"}
    };
    const pricings currentPricings;
    for (vector<const char*> currentOrder : orders) {
        int total = processOrder(currentPricings, currentOrder);
        for (const char* c : currentOrder) {
            cout << c << " ";
        }
        cout << "Total: " << total << endl;
    }
    return 0;
}

