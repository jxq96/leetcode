#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    vector<vector<char>> grid;
    grid.push_back(vector<char>{'1','1','0','0','0'});
    grid.push_back(vector<char>{'1','1','0','0','0'});
    grid.push_back(vector<char>{'0','0','1','0','0'});
    grid.push_back(vector<char>{'0','0','0','1','1'});
    int ret = sol.numIslands(grid);
    cout << ret << endl;
}