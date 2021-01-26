#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    vector<vector<int>> dungeon = vector<vector<int>>(3,vector<int>(3));
    dungeon[0][0] = -2;
    dungeon[0][1] = -3;
    dungeon[0][2] = 3;
    dungeon[1][0] = -5;
    dungeon[1][1] = -10;
    dungeon[1][2] = 1;
    dungeon[2][0] = 10;
    dungeon[2][1] = 30;
    dungeon[2][2] = -5;
    int ret = sol.calculateMinimumHP(dungeon);

}