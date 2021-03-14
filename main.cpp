#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    vector<string> words = {"abcd"};
    vector<vector<char>> board = {
        {'a', 'b'},
        {'c', 'd'}
    };
    auto ret = sol.findWords(board, words);
    for(auto t : ret)
    {
        cout << t << " ";
    }
}