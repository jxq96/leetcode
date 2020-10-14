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

class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int x) : val(x),next(nullptr){};
    ListNode(int x, ListNode* next): val(x), next(next){};
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
    int ladderLength(string beginWord, string endWord, vector<string>& wordList); // #127
    int longestConsecutive(vector<int>& nums);  //#128
    int sumNumbers(TreeNode* root); // #129
    void solve(vector<vector<char>> &board); //#130
    vector<vector<string>> partition(string s); // #131
    int minCut(string s); // # 132
    Node* cloneGraph(Node* node); // #133
    int singleNumber(vector<int>& nums); // #136
    int singleNumber2(vector<int>& nums); // #137
    vector<string> wordBreak(string s, vector<string>& wordDict); // #140
    bool hasCycle(ListNode *head); // #141
    ListNode* detectCycle(ListNode *head); // #142
    void reorderList(ListNode* head); // #143
    ListNode *reverse_list(ListNode* head);
    vector<vector<int>> levelOrderBottom(TreeNode* root); // # 107
    TreeNode* sortedListToBST(ListNode *head); // # 109
    vector<int> inorderTraversal(TreeNode *root); // # 94
    vector<int> preorderTraversal(TreeNode *root); // # 144
    vector<int> postorderTraversal(TreeNode *root); // # 145
    ListNode* insertionSortList(ListNode* head); // #147
    void recoverTree(TreeNode *root); // #99
    ListNode *mergesortList_recursion(ListNode *head); // #148
    ListNode *mergesortList(ListNode *head); // #148, non-recursion mergesort list
};

#endif