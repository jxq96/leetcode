#include "solution.h"
#include <algorithm>
#include <functional>
#include <bitset>
#include <queue>
#include <map>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <utility>
#include <set>
#include <unordered_set>
#include <cmath>
#include <cstdlib>
#include <numeric>
using std::abs;
using std::accumulate;
using std::bitset;
using std::copy;
using std::find;
using std::list;
using std::make_pair;
using std::map;
using std::max;
using std::max_element;
using std::min;
using std::min_element;
using std::minmax_element;
using std::pair;
using std::queue;
using std::reverse;
using std::set;
using std::sort;
using std::stack;
using std::stol;
using std::swap;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
int solution::recurMaxPathSum(TreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int maxLeft = recurMaxPathSum(node->left);
    int maxRight = recurMaxPathSum(node->right);
    maxPathSumReturn = std::max(maxPathSumReturn, std::max(0, maxLeft) + std::max(0, maxRight) + node->val);
    return std::max(0, std::max(maxLeft, maxRight) + node->val);
}
int solution::maxPathSum(TreeNode *root)
{ //  #124
    maxPathSumReturn = -100000;
    recurMaxPathSum(root);
    return maxPathSumReturn;
}

bool solution::isPalindrome(string s)
{
    int len = s.size();
    int left = 0;
    int right = len - 1;
    int step = 'a' - 'A';
    while (left <= right)
    {
        while (!isalnum(s[left]) && left <= right)
        {
            left++;
        }
        while (!isalnum(s[right]) && left <= right)
        {
            right--;
        }
        if (left > right)
        {
            return true;
        }
        if (isupper(s[left]))
        {
            s[left] += step;
        }
        if (isupper(s[right]))
        {
            s[right] += step;
        }
        if (s[left] == s[right])
        {
            left++;
            right--;
            continue;
        }
        return false;
    }
    return true;
}

int distance(string &a, string &b)
{
    int len = a.size();
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i])
        {
            res++;
        }
    }
    return res;
}
int ladderLengthRecur(string beginWord, string endWord, vector<string> &wordList, vector<bool> &bitmap)
{
    int min = INT32_MAX;
    if (beginWord == endWord)
    {
        return 0;
    }
    int size = wordList.size();
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (bitmap[i] && distance(beginWord, wordList[i]) == 1)
        {
            bitmap[i] = false;
            min = std::min(min, ladderLengthRecur(wordList[i], endWord, wordList, bitmap));
            bitmap[i] = true;
        }
    }
    if (min == INT32_MAX)
    {
        return min;
    }
    return min + 1;
}
// brute force:  time-exceeded
/*
int solution::ladderLength(string beginWord, string endWord, vector<string>& wordList){
    int min = INT32_MAX;
    int size = wordList.size();
    int i;
    for(i = 0; i < size; i++){
        if(endWord == wordList[i]){
            break;
        }
    }
    if(i == size){
        return 0;
    }
    vector<bool> bitmap(wordList.size(), true);
    int res = ladderLengthRecur(beginWord,endWord,wordList,bitmap);
    if(res == INT32_MAX){
        return 0 ;
    }
    else{
        return res +1;
    }
}
*/
// transform to shortest path problem, undirected, no-weighted graph

int solution::ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    int word_length = beginWord.size();
    map<string, vector<string>> dict;
    for (auto word : wordList)
    {
        for (int i = 0; i < word_length; i++)
        {
            string pattern_word = word.substr(0, i) + "*" + word.substr(i + 1, word_length);
            vector<string> transformations;
            if (dict.count(pattern_word) != 0)
            {
                dict[pattern_word].emplace_back(word);
            }
            else
            {
                dict[pattern_word] = vector<string>({word});
            }
        }
    }

    queue<pair<string, int>> q;
    q.push(make_pair(beginWord, 1));
    map<string, bool> visited;
    visited[beginWord] = true;
    while (!q.empty())
    {
        pair<string, int> entry = q.front();
        q.pop();
        string word = entry.first;
        int level = entry.second;
        for (int i = 0; i < word_length; i++)
        {
            string pattern_word = word.substr(0, i) + "*" + word.substr(i + 1, word_length);
            for (auto adjacent_word : dict[pattern_word])
            {
                if (adjacent_word == endWord)
                {
                    return level + 1;
                }
                if (visited.count(adjacent_word) == 0)
                {
                    visited[adjacent_word] = true;
                    q.push(make_pair(adjacent_word, level + 1));
                }
            }
        }
    }
    return 0;
}

vector<vector<string>> solution::findLadders(string beginWord, string endWord, vector<string> &wordList)
{
    int word_length = beginWord.size();
    map<string, vector<string>> dict;
    vector<vector<string>> res;
    if (find(wordList.begin(), wordList.end(), endWord) == wordList.end())
    {
        return res;
    }
    for (auto word : wordList)
    {
        for (int i = 0; i < word_length; i++)
        {
            string pattern_word = word.substr(0, i) + "*" + word.substr(i + 1, word_length);
            vector<string> transformations;
            if (dict.count(pattern_word) != 0)
            {
                dict[pattern_word].emplace_back(word);
            }
            else
            {
                dict[pattern_word] = vector<string>({word});
            }
        }
    }
    queue<vector<string>> q;
    bool found = false;
    map<string, bool> visited;
    q.push({beginWord});
    visited[beginWord] = true;
    while (!q.empty())
    {
        int size = q.size();
        unordered_set<string> sub_visited;
        for (int i = 0; i < size; i++)
        {
            vector<string> path = q.front();
            q.pop();
            string word = path[path.size() - 1];
            for (int j = 0; j < word_length; j++)
            {
                string pattern_word = word.substr(0, j) + "*" + word.substr(j + 1, word_length);
                for (auto adjacent : dict[pattern_word])
                {
                    if (visited.count(adjacent) == 0)
                    {
                        if (adjacent == endWord)
                        {
                            path.push_back(adjacent);
                            res.push_back(path);
                            found = true;
                            path.pop_back();
                            continue;
                        }
                        path.push_back(adjacent);
                        q.push(path);
                        path.pop_back();
                        sub_visited.insert(adjacent);
                    }
                }
            }
        }
        for (auto visited_word : sub_visited)
        {
            visited[visited_word] = true;
        }
        sub_visited.clear();
        if (found)
        {
            break;
        }
    }
    return res;
}

int solution::longestConsecutive(vector<int> &nums)
{
    int max = 0;
    unordered_set<int> num_set;
    for (auto i : nums)
    {
        num_set.insert(i);
    }
    int current;
    for (auto i : nums)
    {
        if (num_set.count(i - 1) == 0)
        {
            current = i;
            while (num_set.count(current) == 1)
            {
                current += 1;
            }
            if (max < (current - i))
            {
                max = current - i;
            }
        }
    }
    return max;
}

int sumNumbersRecur(int upper, TreeNode *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return upper * 10 + root->val;
    }
    int res = 0;
    if (root->left)
    {
        res += sumNumbersRecur(upper * 10 + root->val, root->left);
    }
    if (root->right)
    {
        res += sumNumbersRecur(upper * 10 + root->val, root->right);
    }
    return res;
}
int solution::sumNumbers(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return sumNumbersRecur(0, root);
}

void solution::solve(vector<vector<char>> &board)
{
    int row = board.size();
    int column = row ? board[0].size() : 0;
    stack<pair<int, int>> s;
    if (row == 0 || row == 1)
    {
        return;
    }
    else
    {
        for (int i = 0; i < column; i++)
        {
            if (board[0][i] == 'O')
            {
                board[0][i] = 'T';
                s.push(make_pair(0, i));
            }
            if (board[row - 1][i] == 'O')
            {
                board[row - 1][i] = 'T';
                s.push(make_pair(row - 1, i));
            }
        }
        for (int i = 0; i < row; i++)
        {
            if (board[i][0] == 'O')
            {
                board[i][0] = 'T';
                s.push(make_pair(i, 0));
            }
            if (board[i][column - 1] == 'O')
            {
                board[i][column - 1] = 'T';
                s.push(make_pair(i, column - 1));
            }
        }
    }
    while (!s.empty())
    {
        auto position = s.top();
        s.pop();
        int i = position.first;
        int j = position.second;
        if (i != 0)
        {
            if (board[i - 1][j] == 'O')
            {
                board[i - 1][j] = 'T';
                s.push(make_pair(i - 1, j));
            }
        }
        if (i != row - 1)
        {
            if (board[i + 1][j] == 'O')
            {
                board[i + 1][j] = 'T';
                s.push(make_pair(i + 1, j));
            }
        }
        if (j != 0)
        {
            if (board[i][j - 1] == 'O')
            {
                board[i][j - 1] = 'T';
                s.push(make_pair(i, j - 1));
            }
        }
        if (j != column - 1)
        {
            if (board[i][j + 1] == 'O')
            {
                board[i][j + 1] = 'T';
                s.push(make_pair(i, j + 1));
            }
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (board[i][j] == 'O')
            {
                board[i][j] = 'X';
            }
            if (board[i][j] == 'T')
            {
                board[i][j] = 'O';
            }
        }
    }
}

vector<vector<string>> solution::partition(string s)
{
    if (s.empty())
    {
        return vector<vector<string>>();
    }
    else if (s.size() == 1)
    {
        return vector<vector<string>>{{s}};
    }
    else
    {
        vector<vector<string>> res;
        int len = s.size();
        for (int i = 0; i < len; i++)
        {
            int j = i;
            int k = 0;
            while (j >= k)
            {
                if (s[j] == s[k])
                {
                    j--;
                    k++;
                    continue;
                }
                break;
            }
            if (j < k)
            {
                if (i < len - 1)
                {
                    auto tmp = partition(s.substr(i + 1));
                    for (auto &t : tmp)
                    {
                        t.insert(t.begin(), s.substr(0, i + 1));
                        res.push_back(t);
                    }
                }
                else
                {
                    res.push_back(vector<string>{s});
                }
            }
        }
        return res;
    }
}

bool is_palindrome(string &s, int start, int end)
{
    while (start < end)
    {
        if (s[start] != s[end])
        {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int solution::minCut(string s)
{
    // BFS: 超时
    // if(s.empty() || s.size() == 1){
    //     return 0;
    // }
    // queue<pair<int,string>> q;
    // q.push(make_pair(0,s));
    // while(!q.empty()){
    //     auto entry = q.front();
    //     q.pop();
    //     int len = entry.second.size();
    //     string t = entry.second;
    //     for(int i = 0;i<len;i++){
    //         int j = i;
    //         int k = 0;
    //         while(j>=k){
    //             if(t[j]==t[k]){
    //                 j--;
    //                 k++;
    //                 continue;
    //             }
    //             break;
    //         }
    //         if( j < k){
    //             if(i == len -1){
    //                 return entry.first;
    //             }
    //             else{
    //                 q.push(make_pair(entry.first+1,t.substr(i+1)));
    //             }
    //         }
    //     }
    // }
    // return 0;
    if (s.empty() || s.size() == 1)
    {
        return 0;
    }
    int len = s.size();
    int *dp = new int[len];
    for (int i = 0; i < len; i++)
    {
        dp[i] = i;
    }
    for (int i = 1; i < len; i++)
    {
        if (is_palindrome(s, 0, i))
        {
            dp[i] = 0;
            continue;
        }
        for (int j = 0; j < i; j++)
        {
            if (is_palindrome(s, j + 1, i))
            {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    return dp[len - 1];
}

Node *solution::cloneGraph(Node *node)
{
    queue<Node *> q;
    queue<Node *> cloneq;
    if (!node)
    {
        return NULL;
    }
    q.push(node);
    cloneq.push(new Node(node->val));
    Node *ret = cloneq.front();
    unordered_set<Node *> visited;
    unordered_map<Node *, Node *> nodemap;
    nodemap[node] = ret;
    while (!q.empty())
    {
        Node *front = q.front();
        q.pop();
        Node *clone_front = cloneq.front();
        cloneq.pop();
        if (visited.count(front) == 0)
        {
            int neighbors_size = front->neighbors.size();
            for (int i = 0; i < neighbors_size; i++)
            {
                q.push(front->neighbors[i]);
                if (nodemap.count(front->neighbors[i]) == 0)
                {
                    clone_front->neighbors.push_back(new Node(front->neighbors[i]->val));
                    nodemap[front->neighbors[i]] = clone_front->neighbors[i];
                }
                else
                {
                    clone_front->neighbors.push_back(nodemap[front->neighbors[i]]);
                }
                cloneq.push(clone_front->neighbors[i]);
            }
            visited.insert(front);
        }
    }
    return ret;
}

int solution::singleNumber(vector<int> &nums)
{
    int ret = nums[0];
    int i = 1;
    int len = nums.size();
    while (i < len)
    {
        ret ^= nums[i];
        i++;
    }
    return ret;
}

int solution::singleNumber2(vector<int> &nums)
{
    int one = 0, two = 0;
    for (auto num : nums)
    {
        one = (one ^ num) & (~two);
        two = (two ^ num) & (~one);
    }
    return one;
}

// unknown error when submit?
vector<string> solution::wordBreak(string s, vector<string> &wordDict)
{
    vector<vector<vector<string>>> dp(s.length() + 1);
    dp[0] = vector<vector<string>>();
    dp[0].push_back(vector<string>(1, ""));
    int len = s.length();
    for (int i = 1; i <= len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (dp[j].size() > 0 && find(wordDict.begin(), wordDict.end(), string(s.begin() + j, s.begin() + i)) != wordDict.end())
            {
                for (auto &v : dp[j])
                {
                    vector<string> t = v;
                    t.push_back(string(s.begin() + j, s.begin() + i));
                    dp[i].push_back(t);
                }
            }
        }
    }
    vector<string> res;
    for (auto &v : dp[len])
    {
        string t;
        for (auto &str : v)
        {
            t += str;
            t += " ";
        }
        if (t.length() > 0)
        {
            res.push_back(string(t.begin() + 1, t.end() - 1));
        }
    }
    return res;
}

bool solution::hasCycle(ListNode *head)
{ // two pointers: one fast, one slow
    if (head == NULL || head->next == NULL)
    {
        return false;
    }
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (slow != fast)
    {
        if (fast == NULL || fast->next == NULL)
        {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}

ListNode *solution::detectCycle(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    ListNode *fast, *slow;
    fast = head;
    slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            break;
        }
    }
    if (fast == NULL || fast->next == NULL)
    {
        return NULL;
    }
    ListNode *pt1 = head;
    ListNode *pt2 = fast;
    while (pt1 != pt2)
    {
        pt1 = pt1->next;
        pt2 = pt2->next;
    }
    return pt1;
}

ListNode *recur_reorder_list(ListNode *head, int n)
{
    if (n == 1)
    {
        ListNode *ret = head->next;
        head->next = nullptr;
        return ret;
    }
    if (n == 2)
    {
        ListNode *ret = head->next->next;
        head->next->next = nullptr;
        return ret;
    }
    ListNode *tail = recur_reorder_list(head->next, n - 2);
    ListNode *sub_head = head->next;
    head->next = tail;
    ListNode *ret = tail->next;
    tail->next = sub_head;
    return ret;
}

ListNode *solution::reverse_list(ListNode *head)
{
    ListNode *pt, *prev, *next;
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    prev = head;
    pt = head->next;
    while (pt)
    {
        next = pt->next;
        pt->next = prev;
        prev = pt;
        pt = next;
    }
    head->next = nullptr;
    return prev;
}

void reorderListv2(ListNode *head)
{
}

void solution::reorderList(ListNode *head)
{
    int length = 0;
    ListNode *pt = head;
    while (pt)
    {
        length++;
        pt = pt->next;
    }
    recur_reorder_list(head, length);
}

vector<vector<int>> solution::levelOrderBottom(TreeNode *root)
{
    if (root == NULL)
    {
        return vector<vector<int>>();
    }
    else
    {
        queue<TreeNode *> visit_queue;
        visit_queue.push(root);
        visit_queue.push(NULL);
        stack<vector<int>> reverse_res_stack;
        while (!visit_queue.empty() && visit_queue.front() != NULL)
        {
            vector<int> level_nodes;
            while (visit_queue.front() != NULL)
            {
                TreeNode *present_node = visit_queue.front();
                visit_queue.pop();
                if (present_node->left)
                {
                    visit_queue.push(present_node->left);
                }
                if (present_node->right)
                {
                    visit_queue.push(present_node->right);
                }
                level_nodes.push_back(present_node->val);
            }
            reverse_res_stack.push(level_nodes);
            visit_queue.push(NULL);
            visit_queue.pop(); // pop null node in the queue
        }
        vector<vector<int>> res;
        while (!reverse_res_stack.empty())
        {
            res.push_back(reverse_res_stack.top());
            reverse_res_stack.pop();
        }
        return res;
    }
}

TreeNode *solution::sortedListToBST(ListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (head->next == NULL)
    {
        return new TreeNode(head->val);
    }
    ListNode *slow, *fast, *prev;
    slow = fast = prev = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    while (prev->next != slow)
    {
        prev = prev->next;
    }
    TreeNode *root = new TreeNode(slow->val);
    prev->next = NULL;
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(slow->next);
    prev->next = slow;
    return root;
}

vector<int> solution::preorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return vector<int>();
    }
    stack<TreeNode *> s;
    vector<int> res;
    TreeNode *entry;
    s.push(root);
    while (!s.empty())
    {
        entry = s.top();
        s.pop();
        res.emplace_back(entry->val);
        if (entry->right)
        {
            s.push(entry->right);
        }
        if (entry->left)
        {
            s.push(entry->left);
        }
    }
    return res;
}

vector<int> solution::inorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return vector<int>();
    }
    vector<int> ret;
    TreeNode *p = root;
    stack<TreeNode *> s;
    while (p || !s.empty())
    {
        while (p)
        {
            s.push(p);
            p = p->left;
        }
        if (!s.empty())
            ;
        {
            p = s.top();
            s.pop();
            ret.emplace_back(p->val);
            p = p->right;
        }
    }
    return ret;
}

vector<int> solution::postorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return vector<int>();
    }
    TreeNode *cur = root;
    TreeNode *prev = NULL;
    stack<TreeNode *> s;
    vector<int> ret;
    while (cur || !s.empty())
    {
        while (cur)
        {
            s.push(cur);
            cur = cur->left;
        }
        if (!s.empty())
        {
            cur = s.top();
            s.pop();
            if (cur->right == NULL || cur->right == prev)
            {
                ret.emplace_back(cur->val);
                prev = cur;
                cur = NULL;
            }
            else
            {
                s.push(cur);
                cur = cur->right;
            }
        }
    }
    return ret;
}

ListNode *solution::insertionSortList(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ListNode *outer = head;
    ListNode *inner = NULL;
    while (outer->next)
    {
        inner = outer->next;
        outer->next = inner->next;
        if (inner->val >= outer->val)
        { //means inner is maximum
            inner->next = outer->next;
            outer->next = inner;
            outer = inner;
            continue;
        }
        if (head->val > inner->val)
        {
            inner->next = head;
            head = inner;
        }
        else
        {
            ListNode *tmp1 = head;
            ListNode *tmp2 = head->next;
            while (tmp2 && tmp2->val <= inner->val && tmp2 != outer)
            {
                tmp1 = tmp2;
                tmp2 = tmp2->next;
                if (tmp1->val > outer->val)
                {
                    outer = tmp1;
                }
            }
            tmp1->next = inner;
            inner->next = tmp2;
        }
        // outer = outer->next;
    }
    return head;
}

void solution::recoverTree(TreeNode *root)
{ //隐式中序遍历，需要注意两个异常node的顺序不同
    TreeNode *x, *y, *prev;
    TreeNode *p = root;
    stack<TreeNode *> s;
    prev = NULL;
    x = NULL;
    y = NULL;
    if (root == NULL)
    {
        return;
    }
    while (p || !s.empty())
    {
        while (p)
        {
            s.push(p);
            p = p->left;
        }
        if (!s.empty())
        {
            if (!prev)
            {
                prev = s.top();
                s.pop();
                p = prev->right;
                continue;
            }
            p = s.top();
            s.pop();
            if (prev->val > p->val)
            {
                y = p;
                if (!x)
                {
                    x = prev;
                }
                else
                {
                    break;
                }
            }
            prev = p;
            p = p->right;
        }
    }
    swap(x->val, y->val);
}

ListNode *solution::mergesortList_recursion(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    // then find the middle node of the single-linked list
    ListNode *fast = head->next, *slow = head, *tmp;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    tmp = slow->next;
    slow->next = NULL;
    ListNode *left = mergesortList_recursion(head);
    ListNode *right = mergesortList_recursion(tmp);
    ListNode res = ListNode(0);
    ListNode *merge = &res;
    // merge two sorted list
    while (left != NULL && right != NULL)
    {
        if (left->val > right->val)
        {
            merge->next = right;
            right = right->next;
        }
        else
        {
            merge->next = left;
            left = left->next;
        }
        merge = merge->next;
    }
    merge->next = left ? left : right;
    return res.next;
}

ListNode *solution::mergesortList(ListNode *head)
{ //no-recursion of linked list merge sort
    int length, interval, l1, l2;
    interval = 1;
    length = 0;
    ListNode *tmp = head, *pre, *h1, *h2;
    while (tmp)
    {
        length++;
        tmp = tmp->next;
    }
    ListNode res(0);
    // to find the head of the list easily
    res.next = head;
    while (interval < length)
    {
        pre = &res;
        tmp = res.next;
        while (tmp)
        {
            int i = interval;
            h1 = tmp;
            while (i && tmp)
            {
                i--;
                tmp = tmp->next;
            }
            if (i)
            { // h2 is none
                break;
            }
            h2 = tmp;
            i = interval;
            while (i && tmp)
            {
                i--;
                tmp = tmp->next;
            }
            l1 = interval;
            l2 = interval - i;
            while (l1 && l2)
            {
                if (h1->val <= h2->val)
                {
                    pre->next = h1;
                    h1 = h1->next;
                    l1--;
                }
                else
                {
                    pre->next = h2;
                    h2 = h2->next;
                    l2--;
                }
                pre = pre->next;
            }
            if (l1)
            {
                pre->next = h1;
            }
            else
            {
                pre->next = h2;
            }
            while (l1 > 0 || l2 > 0)
            {
                pre = pre->next;
                l1--;
                l2--;
            }
            pre->next = tmp;
        }
        interval *= 2;
    }
    return res.next;
}

ListNode *solution::quicksortList(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    else if (head->next->next == NULL)
    {
        if (head->val > head->next->val)
        {
            ListNode *ret = head->next;
            ret->next = head;
            head->next = NULL;
            return ret;
        }
        else
        {
            return head;
        }
    }
    ListNode left(0);
    ListNode right(0);
    ListNode *pivot = head;
    ListNode *tmp = head->next;
    ListNode *pleft = &left;
    ListNode *pright = &right;
    while (tmp)
    {
        if (tmp->val <= pivot->val)
        {
            pleft->next = tmp;
            pleft = pleft->next;
        }
        else
        {
            pright->next = tmp;
            pright = pright->next;
        }
        tmp = tmp->next;
    }
    pleft->next = pivot;
    pivot->next = NULL;
    pright->next = NULL;
    pleft = quicksortList(left.next);
    pright = quicksortList(right.next);
    left.next = pleft;
    while (pleft->next)
    {
        pleft = pleft->next;
    }
    pleft->next = pright;
    return left.next;
}

unsigned gcd(unsigned a, unsigned b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

//naive solution: time: O(n^2), space: O(n)
int solution::maxPoints(vector<vector<int>> &points)
{
    int count = 0;
    size_t size = points.size();
    for (int i = 0; i < size; i++)
    {
        map<pair<int, int>, int> numbers;
        int cnt = 0;
        int same_point_cnt = 0;
        int same_vertical_line_cnt = 0;
        int same_horizontal_line_cnt = 0;
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (points[i][0] == points[j][0] && points[i][1] == points[j][1])
            {
                same_point_cnt++;
            }
            else if (points[i][0] == points[j][0])
            {
                same_vertical_line_cnt++;
            }
            else if (points[i][1] == points[j][1])
            {
                same_horizontal_line_cnt++;
            }
            else
            {
                int deltax = points[i][0] - points[j][0];
                int deltay = points[i][1] - points[j][1];
                int g;
                unsigned abs_deltax = abs(deltax);
                unsigned abs_deltay = abs(deltay);
                g = abs_deltax > abs_deltay ? gcd(abs_deltax, abs_deltay) : gcd(abs_deltay, abs_deltax);
                cnt = max(cnt, ++numbers[make_pair(deltax / g, deltay / g)]);
            }
        }
        int tmp = max(cnt, max(same_vertical_line_cnt, same_horizontal_line_cnt));
        count = max(count, tmp + same_point_cnt + 1);
    }
    return count;
}

//Don't consider big integer
int solution::evalRPN(vector<string> &tokens)
{
    stack<long> s;
    long oprand1, oprand2, result;
    for (string &token : tokens)
    {
        if (token == "+")
        {
            oprand2 = s.top();
            s.pop();
            oprand1 = s.top();
            s.pop();
            result = oprand1 + oprand2;
            s.push(result);
        }
        else if (token == "-")
        {
            oprand2 = s.top();
            s.pop();
            oprand1 = s.top();
            s.pop();
            result = oprand1 - oprand2;
            s.push(result);
        }
        else if (token == "*")
        {
            oprand2 = s.top();
            s.pop();
            oprand1 = s.top();
            s.pop();
            result = oprand1 * oprand2;
            s.push(result);
        }
        else if (token == "/")
        {
            oprand2 = s.top();
            s.pop();
            oprand1 = s.top();
            s.pop();
            result = oprand1 / oprand2;
            s.push(result);
        }
        else
        {
            long tmp = stol(token);
            s.push(tmp);
        }
    }
    result = s.top();
    s.pop();
    return result;
}

string solution::reverseWords(string s)
{
    stack<string> reverse_stack;
    auto left = s.begin();
    auto right = s.begin();
    while (true)
    {
        while (*left == ' ' && left != s.end())
        {
            left++;
        }
        right = left;
        while (right != s.end() && *right != ' ')
        {
            right++;
        }
        if (left != s.end())
        {
            reverse_stack.push(string(left, right));
        }
        else
        {
            break;
        }
        left = right;
    }
    string result;
    while (!reverse_stack.empty())
    {
        result += reverse_stack.top();
        reverse_stack.pop();
        if (!reverse_stack.empty())
        {
            result += " ";
        }
    }
    return result;
}

int solution::maxProduct(vector<int> &nums)
{
    // assmue nums at least has one element.
    int tmin = nums[0], tmax = nums[0], ret = nums[0];
    size_t length = nums.size();
    for (int i = 1; i < length; i++)
    {
        tmax = max(max(tmax * nums[i], tmin * nums[i]), nums[i]);
        tmin = min(min(tmax * nums[i], tmin * nums[i]), nums[i]);
        ret = max(ret, tmax);
    }
    return ret;
}

int solution::findMin(vector<int> &nums)
{
    // assume the nums has at least one element
    size_t len = nums.size();
    if (nums[len - 1] >= nums[0])
    {
        return nums[0];
    }
    size_t middle = len / 2;
    int pivot = nums[0];
    size_t left = 0;
    size_t right = len;
    while (middle > 0 && nums[middle] > nums[middle - 1])
    {
        if (nums[middle] > pivot)
        {
            left = middle;
            middle = (left + right) / 2;
        }
        else
        {
            right = middle;
            middle = (left + right) / 2;
        }
    }
    return nums[middle];
}

int solution::findMin2(vector<int> &nums)
{
    //  这个版本的代码过了，还很快，但是思路比较乱， 下面再给一个思路清晰的版本
    int pivot = 0, pivotval;
    size_t len = nums.size();
    if (nums[0] < nums[len - 1])
    {
        return nums[0];
    }
    else if (nums[0] == nums[len - 1])
    {
        int tmp = nums[len - 1];
        while (nums[pivot] == nums[len - 1] && pivot < len - 1)
        {
            pivot++;
        }
        if (pivot == len - 1)
        {
            return nums[0];
        }
    }
    int left = pivot, right = len - 1;
    int middle = (left + right) / 2;
    pivotval = nums[pivot];
    if (pivotval < nums[len - 1])
    {
        return pivotval;
    }
    while (middle > pivot && nums[middle] >= nums[middle - 1])
    {
        if (middle < len - 1 && nums[middle] > nums[middle + 1])
        {
            break;
        }
        if (nums[middle] >= pivotval)
        {
            left = middle;
            middle = (left + right) / 2;
        }
        else
        {
            right = middle;
            middle = (left + right) / 2;
        }
    }
    return min(nums[middle], nums[middle + 1]);
}

int findMin2_refine(vector<int> &nums)
{
    int left = 0, right = nums.size() - 1;
    int middle;
    if (nums[left] < nums[right])
    {
        return nums[left];
    }
    while (left < right)
    {
        if (nums[left] < nums[right])
        {
            return nums[left];
        }
        middle = (left + right) / 2;
        if (nums[middle] > nums[left])
        {
            left = middle + 1;
        }
        else if (nums[middle] < nums[left])
        {
            right = middle;
        }
        else
        {
            left++;
        }
    }
    return nums[left];
}

ListNode *solution::getIntersectionNode(ListNode *headA, ListNode *headB)
{
    unsigned long lenA = 0, lenB = 0;
    int gap;
    ListNode *tmpA = headA, *tmpB = headB;
    while (tmpA)
    {
        lenA++;
        tmpA = tmpA->next;
    }
    while (tmpB)
    {
        lenB++;
        tmpB = tmpB->next;
    }
    if (lenB > lenA)
    {
        gap = lenB - lenA;
        tmpB = headB;
        tmpA = headA;
        while (gap)
        {
            tmpB = tmpB->next;
            gap--;
        }
    }
    else
    {
        gap = lenA - lenB;
        tmpA = headA;
        tmpB = headB;
        while (gap)
        {
            tmpA = tmpA->next;
            gap--;
        }
    }
    while (tmpA != tmpB && tmpB && tmpA)
    {
        tmpA = tmpA->next;
        tmpB = tmpB->next;
    }
    return tmpA;
}

int solution::findPeakElement(vector<int> &nums)
{
    size_t len = nums.size();
    if (len == 1)
    {
        return 0;
    }
    else
    {
        if (nums[0] > nums[1])
        {
            return 0;
        }
        if (nums[len - 1] > nums[len - 2])
        {
            return len - 1;
        }
        int middle, middlel, middler;
        int left = 0, right = len - 1;
        middle = (left + right) / 2;
        while (middle > 0 && left < right && (nums[middle] < nums[middle - 1] || nums[middle] < nums[middle + 1]))
        {
            middlel = (left + middle) / 2;
            middler = (right + middle) / 2;
            if (nums[middlel] > nums[left] && nums[middlel] > nums[middle])
            {
                right = middle;
                middle = (left + right) / 2;
                continue;
            }
            else if (nums[middler] > nums[right] && nums[middler] > nums[middle])
            {
                left = middle;
                middle = (left + right) / 2;
                continue;
            }
            else
            {
                int tmp = left + 1;
                bool flag = false;
                while (tmp <= middle)
                {
                    if (nums[tmp] > nums[left] && nums[tmp] > nums[middle])
                    {
                        right = middle;
                        middle = (left + right) / 2;
                        flag = true;
                        break;
                    }
                    tmp++;
                }
                if (flag)
                {
                    continue;
                }
                tmp = right - 1;
                while (tmp >= middle)
                {
                    if (nums[tmp] > nums[right] && nums[tmp] > nums[middle])
                    {
                        left = middle;
                        middle = (left + right) / 2;
                        break;
                    }
                    tmp--;
                }
            }
        }
        return middle;
    }
}

//radixSort
int solution::maximumGap(vector<int> &nums)
{
    int n = nums.size();
    if (n < 2)
    {
        return 0;
    }
    int exp = 1;
    vector<int> buf(n);
    int max_val = *max_element(nums.begin(), nums.end());
    while (max_val >= exp)
    {
        vector<int> cnt(10);
        for (int i = 0; i < n; i++)
        {
            int digit = (nums[i] / exp) % 10;
            cnt[digit]++;
        }
        for (int i = 1; i < 10; i++)
        {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            int digit = (nums[i] / exp) % 10;
            buf[cnt[digit] - 1] = nums[i];
            cnt[digit]--;
        }
        copy(buf.begin(), buf.end(), nums.begin());
        exp *= 10;
    }
    int ret = 0;
    for (int i = 1; i < n; i++)
    {
        ret = max(ret, nums[i] - nums[i - 1]);
    }
    return ret;
}

int solution::compareVersion(string version1, string version2)
{
    const char *left1, *left2;
    const char *s1 = version1.c_str();
    const char *s2 = version2.c_str();
    long l1, l2;
    char *tmp1, *tmp2;
    left1 = s1;
    left2 = s2;
    while (*left1 && *left2)
    {
        l1 = strtol(left1, &tmp1, 10);
        l2 = strtol(left2, &tmp2, 10);
        if (*tmp1)
        {
            left1 = ++tmp1;
        }
        else
        {
            left1 = tmp1;
        }
        if (*tmp2)
        {
            left2 = ++tmp2;
        }
        else
        {
            left2 = tmp2;
        }
        if (l1 == l2)
        {
            continue;
        }
        return l1 > l2 ? 1 : -1;
    }
    if (!(*left1) && !(*left2))
    {
        return 0;
    }
    while (*left1)
    {
        if (*left1 != '0' && *left1 != '.')
        {
            return 1;
        }
        left1++;
    }
    while (*left2)
    {
        if (*left2 != '0' && *left2 != '.')
        {
            return -1;
        }
        left2++;
    }
    return 0;
}

string solution::fractionToDecimal(int numerator, int denominator)
{
    string ret;
    if (numerator == 0)
    {
        return string("0");
    }
    if ((numerator < 0) ^ (denominator < 0))
    {
        ret.push_back('-');
    }
    long num = (long)(numerator);
    long dom = (long)denominator;
    num = num < 0 ? -num : num;
    dom = dom < 0 ? -dom : dom;
    unordered_map<int, int> remain_location;
    long remainder;
    ret += to_string(num / dom);
    remainder = num % dom;
    if (remainder == 0)
    {
        return ret;
    }
    ret.push_back('.');
    while (remainder != 0)
    {
        if (remain_location.count(remainder) != 0)
        {
            ret = ret.substr(0, remain_location[remainder]) + "(" + ret.substr(remain_location[remainder]) + ")";
            break;
        }
        else
        {
            remain_location[remainder] = ret.size();
            remainder *= 10;
            ret += to_string(remainder / dom);
            remainder %= dom;
        }
    }
    return ret;
}

vector<int> solution::twoSum(vector<int> &numbers, int target)
{
    int left = 0, right = numbers.size() - 1;
    int sum;
    while ((sum = numbers[left] + numbers[right]) != target)
    {
        if (sum < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    vector<int> ret;
    ret.push_back(++left);
    ret.push_back(++right);
    return ret;
}

string solution::convertToTitle(int n)
{
    string ret;
    while (n > 0)
    {
        n -= 1;
        ret.push_back(n % 26 + 'A');
        n /= 26;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int solution::majorityElement(vector<int> &nums)
{
    int ret = nums[0];
    int count = 1;
    size_t size = nums.size();
    for (int i = 1; i < size; i++)
    {
        if (count == 0)
        {
            ret = nums[i];
            count = 1;
            continue;
        }
        if (nums[i] == ret)
        {
            count++;
        }
        else
        {
            count--;
        }
    }
    return ret;
}

int solution::titleToNumber(string s)
{
    int ret = 0;
    for (char c : s)
    {
        int t = c - 'A' + 1;
        ret = ret * 26 + t;
    }
    return ret;
}

int solution::trailingZeroes(int n)
{
    int order2, order5;
    order2 = order5 = 0;
    int i = 2;
    int t;
    while ((t = n / i) > 0)
    {
        order2 += t;
        i *= 2;
    }
    i = 5;
    while ((t = n / i) > 0)
    {
        order5 += t;
        i *= 5;
    }
    return order2 < order5 ? order2 : order5;
}

int solution::calculateMinimumHP(vector<vector<int>> &dungeon)
{
    if (dungeon.size() == 0 || dungeon[0].size() == 0)
    {
        return 0;
    }
    size_t rows = dungeon.size();
    size_t columns = dungeon[0].size();
    vector<vector<int>> dp(rows + 1, vector<int>(columns + 1, INT32_MAX));
    dp[rows - 1][columns] = dp[rows][columns - 1] = 1;
    for (ssize_t i = rows - 1; i >= 0; i--)
    {
        for (ssize_t j = columns - 1; j >= 0; j--)
        {
            int minn = min(dp[i + 1][j], dp[i][j + 1]);
            dp[i][j] = max(minn - dungeon[i][j], 1);
        }
    }
    return dp[0][0];
}

string solution::largestNumber(vector<int> &nums)
{
    vector<string> snums;
    for (int entry : nums)
    {
        snums.push_back(to_string(entry));
    }
    sort(snums.begin(), snums.end(), [](const string &a, const string &b) {
        string t1 = a + b;
        string t2 = b + a;
        if (t1 >= t2)
        {
            return false;
        }
        else
        {
            return true;
        }
    });
    string ret;
    for (auto i = snums.rbegin(); i != snums.rend(); i++)
    {
        ret += *i;
    }
    if (ret.size() > 1 && ret[0] == '0')
    {
        return "0";
    }
    return ret;
}

vector<string> solution::findRepeatedDnaSequences(string s)
{
    vector<string> ret;
    if (s.size() <= 10)
    {
        return ret;
    }
    auto i = s.begin();
    auto j = i + 10;
    unordered_map<string, int> hash;
    while (j <= s.end())
    {
        string tmp = string(i, j);
        if (hash.count(tmp) == 0)
        {
            hash[tmp] = 1;
        }
        else
        {
            hash[tmp]++;
        }
        i++;
        j++;
    }
    for (auto entry : hash)
    {
        if (entry.second > 1)
        {
            ret.push_back(entry.first);
        }
    }
    return ret;
}

void reverse(vector<int> &nums, int start, int end)
{
    while (start < end)
    {
        swap(nums[start], nums[end]);
        start++;
        end--;
    }
}

// reverse threee times
void solution::rotate(vector<int> &nums, int k)
{
    k %= nums.size();
    reverse(nums, 0, nums.size() - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, nums.size() - 1);
}

uint32_t solution::reverseBits(uint32_t n)
{
    uint32_t ret = 0;
    int count = 31;
    while (count > 0)
    {
        if (n & 1)
        {
            ret |= 1;
        }
        ret <<= 1;
        n >>= 1;
        count--;
    }
    if (n & 1)
    {
        ret |= 1;
    }
    return ret;
}

int solution::hammingWeight(uint32_t n)
{
    int ret = 0;
    while (n)
    {
        n &= (n - 1);
        ret++;
    }
    return ret;
}

int solution::rob(vector<int> &nums)
{
    size_t size = nums.size();
    if (size == 0)
    {
        return 0;
    }
    if (size == 1)
    {
        return nums[0];
    }
    int first, second;
    first = nums[0];
    second = max(nums[0], nums[1]);
    for (size_t i = 2; i < size; i++)
    {
        int tmp = second;
        second = max(nums[i] + first, second);
        first = tmp;
    }
    return second;
}

vector<int> solution::rightSideView(TreeNode *root)
{
    vector<int> ret;
    queue<TreeNode *> level_queue;
    if (root == NULL)
    {
        return ret;
    }
    level_queue.push(root);
    while (!level_queue.empty())
    {
        size_t size = level_queue.size();
        ret.push_back(level_queue.front()->val);
        for (int i = 0; i < size; i++)
        {
            auto tmp = level_queue.front();
            level_queue.pop();
            if (tmp->right)
            {
                level_queue.push(tmp->right);
            }
            if (tmp->left)
            {
                level_queue.push(tmp->left);
            }
        }
    }
    return ret;
}

struct island_set_node
{
    struct island_set_node *parent;
    int rank;
};

void island_union(struct island_set_node *a, struct island_set_node *b)
{
    if (a->rank > b->rank)
    {
        b->parent = a;
    }
    else
    {
        a->parent = b;
        if (a->rank == b->rank)
        {
            b->rank++;
        }
    }
}

struct island_set_node *find_set(struct island_set_node *x)
{
    if (x != x->parent)
    {
        x->parent = find_set(x->parent);
    }
    return x->parent;
}

int solution::numIslands(vector<vector<char>> &grid)
{
    int row = grid.size();
    if (row == 0)
    {
        return 0;
    }
    int column = grid[0].size();
    if (column == 0)
    {
        return 0;
    }
    struct island_set_node nodes[row][column];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (grid[i][j] == '1')
            {
                nodes[i][j].rank = 0;
                nodes[i][j].parent = &nodes[i][j];
                if (i > 0)
                {
                    if (grid[i - 1][j] == '1')
                    {
                        island_union(find_set(&nodes[i][j]), find_set(&nodes[i - 1][j]));
                    }
                }
                if (j > 0)
                {
                    if (grid[i][j - 1] == '1')
                    {
                        island_union(find_set(&nodes[i][j]), find_set(&nodes[i][j - 1]));
                    }
                }
            }
            else
            {
                nodes[i][j].rank = -1;
            }
        }
    }
    unordered_set<struct island_set_node *> sets;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (nodes[i][j].rank != -1)
            {
                if (sets.count(find_set(&nodes[i][j])) == 0)
                {
                    sets.insert(find_set(&nodes[i][j]));
                }
            }
        }
    }
    int ret = sets.size();
    return ret;
}

int solution::rangeBitwiseAnd(int m, int n)
{
    while (m < n)
    {
        n &= (n - 1);
    }
    return n;
}

bool solution::isHappy(int n)
{
    int r, m;
    unordered_set<int> present_numbers;
    present_numbers.insert(n);
    m = 0;
    while (m != 1)
    {
        if (present_numbers.find(m) != present_numbers.end())
        {
            return false;
        }
        present_numbers.insert(m);
        m = 0;
        while (n)
        {
            r = n % 10;
            m += r * r;
            n /= 10;
        }
        n = m;
    }
    return true;
}

ListNode *solution::removeElements(ListNode *head, int val)
{
    ListNode *ret = head;
    while (ret && ret->val == val)
    {
        ret = ret->next;
    }
    ListNode *tmp = ret;
    if (!tmp)
    {
        return ret;
    }
    while (tmp->next)
    {
        if (tmp->next->val == val)
        {
            tmp->next = tmp->next->next;
            continue;
        }
        tmp = tmp->next;
    }
    return ret;
}

int solution::countPrimes(int n)
{
    if (n <= 2)
    {
        return 0;
    }
    vector<char> is_prime(n, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i < n; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j < n; j += i)
            {
                is_prime[j] = 0;
            }
        }
    }
    return accumulate(is_prime.begin(), is_prime.end(), 0);
}

int solution::superEggDrop(int K, int N)
{
    //FIXME: not implement
    return 0;
}

bool solution::isIsomorphic(string s, string t)
{
    unordered_map<char, char> mapping;
    unordered_set<char> existed_value;
    if (s.length() != t.length())
    {
        return false;
    }
    size_t len = s.length();
    for (size_t i = 0; i < len; i++)
    {
        if (mapping.count(s[i]) != 0)
        {
            if (mapping[s[i]] != t[i])
            {
                return false;
            }
        }
        else
        {
            if (existed_value.count(t[i]) != 0)
            {
                return false;
            }
            else
            {
                mapping[s[i]] = t[i];
                existed_value.insert(t[i]);
            }
        }
    }
    return true;
}

bool solution::canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<int> in_degree(numCourses, 0);
    int count = 0;
    list<int> *adjacent_list = new list<int>[numCourses];
    for (auto prerequisite : prerequisites)
    {
        //prerequisite[1] before prerequisite[0]
        // out_degre[prerequisite[1]] ++;
        in_degree[prerequisite[0]]++;
        adjacent_list[prerequisite[1]].push_back(prerequisite[0]);
    }
    int i;
    while (true)
    {
        for (i = 0; i < numCourses; i++)
        {
            if (in_degree[i] == 0)
            {
                break;
            }
        }
        if (i == numCourses)
        {
            break;
        }
        in_degree[i] = -1;
        for (auto adjacent : adjacent_list[i])
        {
            in_degree[adjacent]--;
        }
        count++;
    }
    if (count == numCourses)
    {
        return true;
    }
    return false;
}

class Trie
{
public:
    /** Initialize your data structure here. */
    Trie()
    {
        for (int i = 0; i < 26; i++)
        {
            this->link[i] = nullptr;
        }
        this->flag = false;
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        bool ret = this->search(word);
        if (ret)
        {
            return;
        }
        else
        {
            Trie *t = this;
            for (char c : word)
            {
                c -= 'a';
                if (t->link[c] == nullptr)
                {
                    t->link[c] = new Trie();
                }
                t = t->link[c];
            }
            t->flag = true;
        }
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        Trie *t = this;
        for (char c : word)
        {
            c -= 'a';
            if (t->link[c] == nullptr)
            {
                return false;
            }
            else
            {
                t = t->link[c];
            }
        }
        return t->flag;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        Trie *t = this;
        for (char c : prefix)
        {
            c -= 'a';
            if (t->link[c] == nullptr)
            {
                return false;
            }
            else
            {
                t = t->link[c];
            }
        }
        return true;
    }

private:
    Trie *link[26];
    bool flag;
};

int solution::minSubArrayLen(int target, vector<int> &nums)
{
    if (nums.size() == 0)
    {
        return 0;
    }
    int start, end;
    start = end = 0;
    int len = nums.size();
    int sum = 0;
    int min_now = INT32_MAX;
    for (int i = 0; i < len; i++)
    {
        if (sum < target)
        {
            sum += nums[i];
            end = i;
        }
        else
        {
            if (end - start + 1 < min_now)
            {
                min_now = end - start + 1;
            }
            sum += nums[i];
            end = i;
            while ((sum - nums[start]) >= target)
            {
                sum -= nums[start++];
            }
        }
    }
    while ((sum - nums[start]) >= target)
    {
        sum -= nums[start++];
    }
    if (end - start + 1 < min_now && sum >= target)
    {
        min_now = end - start + 1;
    }
    if (min_now == INT32_MAX)
    {
        return 0;
    }
    return min_now;
}

vector<int> solution::findOrder(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<int> in_degree(numCourses, 0);
    vector<int> ret;
    int count = 0;
    list<int> *adjacent_list = new list<int>[numCourses];
    for (auto prerequisite : prerequisites)
    {
        //prerequisite[1] before prerequisite[0]
        // out_degre[prerequisite[1]] ++;
        in_degree[prerequisite[0]]++;
        adjacent_list[prerequisite[1]].push_back(prerequisite[0]);
    }
    int i;
    while (true)
    {
        for (i = 0; i < numCourses; i++)
        {
            if (in_degree[i] == 0)
            {
                break;
            }
        }
        if (i == numCourses)
        {
            break;
        }
        in_degree[i] = -1;
        ret.push_back(i);
        for (auto adjacent : adjacent_list[i])
        {
            in_degree[adjacent]--;
        }
        count++;
    }
    if (count == numCourses)
    {
        return ret;
    }
    return vector<int>();
}

bool backtrace(int x, int y, vector<vector<bool>>& visited, int count, string& word, vector<vector<char>>& board, int m, int n)
{
    if(count == word.size())
    {
        return true;
    }
    bool ret;
    if(x > 0 && !visited[x-1][y] && board[x-1][y] == word[count])
    {
        visited[x-1][y] = true;
        count += 1;
        ret = backtrace(x-1,y,visited,count, word, board, m, n);
        if(ret)
        {
            visited[x-1][y] = false;
            return true;
        }
        else
        {
            visited[x-1][y] = false;
            count -= 1;
        }
    }
    if(x < m - 1  && !visited[x+1][y] && board[x+1][y] == word[count])
    {
        visited[x+1][y] = true;
        count += 1;
        ret = backtrace(x+1,y,visited,count, word, board, m, n);
        if(ret)
        {
            visited[x+1][y] = false;
            return true;
        }
        else
        {
            visited[x+1][y] = false;
            count -= 1;
        }
    }
    if(y > 0  && !visited[x][y-1] && board[x][y-1] == word[count])
    {
        visited[x][y-1] = true;
        count += 1;
        ret = backtrace(x,y-1,visited,count, word, board, m, n);
        if(ret)
        {
            visited[x][y-1] = false;
            return true;
        }
        else
        {
            visited[x][y-1] = false;
            count -= 1;
        }
    }
    if(y < n - 1  && !visited[x][y+1] && board[x][y+1] == word[count])
    {
        visited[x][y+1] = true;
        count += 1;
        ret = backtrace(x,y+1,visited,count, word, board, m, n);
        if(ret)
        {
            visited[x][y+1] = false;
            return true;
        }
        else
        {
            visited[x][y+1] = false;
            count -= 1;
        }
    }
    return false;
}

vector<string> solution::findWords(vector<vector<char>> &board, vector<string> &words)
{
    int m = board.size();
    int n;
    if (m != 0)
    {
        n = board[0].size();
    }
    vector<vector<bool>> visited(m);
    unordered_map<char, vector<pair<int, int>>> fast_index;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fast_index.count(board[i][j]) == 0)
            {
                fast_index[board[i][j]] = vector<pair<int, int>>();
            }
            fast_index[board[i][j]].push_back(make_pair(i, j));
        }
    }
    for (int i = 0; i < m; i++)
    {
        visited[i] = vector<bool>(n);
    }
    vector<string> ret;
    for (auto word : words)
    {
        auto start_points = fast_index[word[0]];
        for(auto point : start_points)
        {
            int x = point.first;
            int y = point.second;
            visited[x][y] = true;
            if(backtrace(x,y,visited,1,word,board,m,n))
            {
                ret.push_back(word);
                visited[x][y] = false;
                break;
            }
            else
            {
                visited[x][y] = false;
            }
        }
    }
    return ret;
}

int solution::rob2(vector<int>& nums)
{
    if(nums.size() == 0)
    {
        return 0;
    }
    if(nums.size() == 1)
    {
        return nums[0];
    }
    if(nums.size() == 2)
    {
        return max(nums[0], nums[1]);
    }
    if(nums.size() == 3)
    {
        return max(nums[0], max(nums[1], nums[2]));
    }
    if(nums.size() == 4)
    {
        return max(nums[0] + nums[2], nums[1] + nums[3]);
    }
    int first, second;
    // select firset
    first = nums[2];
    second = max(nums[2], nums[3]);
    int len = nums.size();
    for(int i = 4; i < len - 1; i++)
    {
        int tmp = second;
        second = max(second, first + nums[i]);
        first = tmp; 
    }
    int a = second + nums[0];
    first = nums[1];
    second = max(nums[1], nums[2]);
    for(int i = 3; i < len; i++)
    {
        int tmp = second;
        second = max(second, first + nums[i]);
        first = tmp;
    }
    return max(a, second);
}