#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    uint32_t n = 4294967293;
    auto ret = sol.reverseBits(n);
    cout << ret << endl;
}