#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
    bool defused = false;
    bool exploded = false;
    int cutCount = 0;
    int extraCutCount = 0;
    vector<int> doNotCut;
    vector<int> cables {'w', 'b', 'p', 'r', 'g', 'o'};
    std::map<int, std::vector<int>> rules {
        {'w', vector<int> {'w', 'b'} },
        {'b', vector<int> {'w','g','o'} },
        {'p', vector<int> {'p', 'g', 'o', 'w'} },
        {'r', vector<int> {-'g'} },
        {'g', vector<int> {-'o',-'w'} },
        {'o', vector<int> {-'r', -'b'} }
    };
    
    cout << "Which cables should be cut?" << endl;
    
    while (!defused && !exploded) {
        if (cutCount == 4) {
            defused = true;
            break;
        }
        char readCable[10];
        cin >> readCable;
        int cable = readCable[0];
        if ( std::find(cables.begin(), cables.end(), cable) != cables.end() ) {
            vector<int> cablesToCut;
            if ( std::find(doNotCut.begin(), doNotCut.end(), cable) != doNotCut.end()) {
                cutCount++;
                exploded = true;
                break;
            }
            vector<int> currentRule = rules.find(cable)->second;
            for (int i : currentRule) {
                if (i > 0) {
                    doNotCut.push_back(i);
                } else {
                    cablesToCut.push_back(i*-1);
                }
            }
            if (!cablesToCut.empty()) {
                bool extraCableCut = false;
                for (int i : cablesToCut) {
                    if ( std::find( doNotCut.begin(), doNotCut.end(), i) == doNotCut.end()) {
                        extraCableCut =true;
                        extraCutCount++;
                        break;
                    }
                }
                if (!extraCableCut) {
                    exploded = true;
                    extraCutCount++;
                    break;
                }
            }
            cutCount++;
        } else {
            cout << "No such cable." << endl;
        }
    }
    
    if (exploded == true) {
        cout << "The bomb exploded!\nCables cut: " << cutCount+extraCutCount << endl;
    } else {
        cout << "The bomb got defused!\nCables cut: " << cutCount+extraCutCount << endl;
    }
    
    return 0;
}

