#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    int target = 80;
    vector<int> nums = {10,5,13,4,8,4,5,11,14,9,16,10,20,8};
    cout << sol.minSubArrayLen(target, nums) << endl;
}