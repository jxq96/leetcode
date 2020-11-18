#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    string s = "  hello world!  ";
    string ret = sol.reverseWords(s);
    cout << ret << endl;
}