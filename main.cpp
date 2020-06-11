#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    ListNode *l = new ListNode(1,new ListNode(2,new ListNode(3,new ListNode(4))));
    ListNode *r = sol.reverse_list(l);
    while(r){
        cout << r->val << " ";
        r = r->next;
    }
    cout << endl;
}