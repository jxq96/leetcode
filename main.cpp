#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    ListNode *t = new ListNode(-1);
    t->next = new ListNode(-1);
    t->next->next = new ListNode(5);
    t->next->next->next = new ListNode(4);
    t->next->next->next->next = new ListNode(0);
    ListNode *ret = sol.quicksortList(t);
    while(ret){
        cout << ret->val << ",";
        ret = ret->next;
    }
    cout << endl;
}