//https://www.reddit.com/r/dailyprogrammer/comments/3r7wxz/20151102_challenge_239_easy_a_game_of_threes/

#include <cstdlib>
#include <iostream>

using namespace std;


void gameOfThrees(int number) {
    if (number == 1)
        return;
    int op = (-1*number - 1) % 3 + 1;
    cout << number << " " << op << endl;
    gameOfThrees( (number + op) / 3 );
}


int main(int argc, char** argv) {
    
    int number;
    cout << "Enter a rather large number to play with!" << endl;
    cin >> number;
    gameOfThrees(number);
    cout << 1 << endl;
    
    return 0;
}

