#ifndef __SOLUTION__
#define __SOLUTION__
#include<iostream>
#include<string>
#include<vector>
using std::string;
using std::vector;
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};

class solution
{
private:
    int maxPathSumReturn;
    
public:
    solution() = default;
    ~solution() = default;
    int maxPathSum(TreeNode*); // #124
    int recurMaxPathSum(TreeNode*);
    bool isPalindrome(string s); // #125
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList); //#126

};

#endif