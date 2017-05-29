//https://www.reddit.com/r/dailyprogrammer/comments/6e08v6/20170529_challenge_317_easy_collatz_tag_system/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#define NORMAL 1
#define BONUS 2

using namespace std;

struct rulebook {
    const map<char, string> rules {
        {'a', "bc"},
        {'b', "a"},
        {'c', "aaa"}
    };
    const vector<char> abc {'0','1'};
    const vector<string> productions { "010","000", "1111" };
    const int n = 2;
};

bool rulesExist(string s, rulebook const &rules, int mode) {
    if (mode == NORMAL) {
            for (char c : s) {
                if ( rules.rules.find(c) == rules.rules.end() )
                    return false;
            }
        } else if (mode == BONUS) {
            for (char c : s) {
                if ( find(rules.abc.begin(), rules.abc.end(), c) == rules.abc.end())
                    return false;
        }
    }
    return true;
}

void process(string input, rulebook const &rules, int mode, int &nextProduction) {
    if (mode == NORMAL) {
        if (input.length() < 2) {
            cout << input << endl;
            return;
        }
        cout << input << endl;
        char currentChar = input.at(0);
        string result = input.substr(rules.n, string::npos );
        result = result.append( rules.rules.find(currentChar)->second );
        process(result, rules, mode, nextProduction);
    } else if (mode == BONUS) {
        if ( input == "" ) {
            return;
        }
        cout << input << endl;
        char currentChar = input.at(0);
        string result ="";
        if (input.length() > 1) {
           result = input.substr(1, string::npos);
        }
        if ( (currentChar - '0') ) {
            result.append( rules.productions.at(nextProduction) );
        }
        nextProduction++;
        if ( nextProduction >= rules.productions.size() )
            nextProduction = 0;
        process(result, rules, mode, nextProduction);
    }
} 

int main(int argc, char** argv) {
    const rulebook rules;
    int mode = 0;
    int nextProduction = 0;
    string input = "";
    cin >> input;
    while ( mode == 0 ) {
        if( rulesExist(input, rules, NORMAL) ) {
            mode = NORMAL;
            break;
        } else if ( rulesExist(input, rules, BONUS) ) {
            mode = BONUS;
            break;
        }
        cout << "Invalid string." << endl;
        cin >> input;
    }
    process(input, rules, mode, nextProduction);
    return 0;
}
