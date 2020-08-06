#include<iostream>
#include "solution.h"
using namespace std;
int main(){
    solution sol;
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    auto res = sol.levelOrderBottom(root);
    for(auto vec : res){
        for(auto num : vec){
            cout << num << " ";
        }
        cout << endl;
    }
}