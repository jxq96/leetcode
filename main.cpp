#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    ListNode* l = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    auto ret = sol.reverseKGroup(l, 2);
    while(ret)
    {
        cout << ret->val << " ";
        ret = ret->next;
    }
    cout << "\n";
}