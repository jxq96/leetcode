#include "solution.h"
#include <algorithm>
#include <bitset>
#include <queue>
#include <map>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <utility>
using std::unordered_map;
using std::map;
using std::pair;
using std::bitset;
using std::queue;
using std::make_pair;
using std::find;
using std::unordered_set;
using std::min_element;
using std::minmax_element;
using std::stack;
using std::min;
using std::max;
using std::swap;
int solution::recurMaxPathSum(TreeNode* node){
    if(node == NULL){
        return 0;
    }
    int maxLeft = recurMaxPathSum(node->left);
    int maxRight = recurMaxPathSum(node->right);
    maxPathSumReturn = std::max(maxPathSumReturn, std::max(0,maxLeft)+std::max(0,maxRight) + node->val);
    return std::max(0,std::max(maxLeft,maxRight)+node->val);
}
int solution::maxPathSum(TreeNode* root){ //  #124
    maxPathSumReturn = -100000;
    recurMaxPathSum(root);
    return maxPathSumReturn;
}

bool solution::isPalindrome(string s){
    int len = s.size();
    int left = 0;
    int right = len - 1;
    int step = 'a' - 'A';
    while(left <= right){
        while(!isalnum(s[left]) && left <= right){
            left++;
        }
        while(!isalnum(s[right]) && left <= right){
            right--;
        }
        if(left >right){
            return true;
        }
        if(isupper(s[left])){
            s[left] += step;
        }
        if(isupper(s[right])){
            s[right] += step;
        }
        if(s[left] == s[right]){
            left++;
            right--;
            continue;
        }
        return false;
    }
    return true;
}



int distance(string& a, string&b){
    int len = a.size();
    int res = 0;
    for(int i = 0; i < len; i++){
        if(a[i] != b[i]){
            res ++;
        }
    }
    return res;
}
int ladderLengthRecur(string beginWord, string endWord, vector<string>& wordList, vector<bool>& bitmap){
    int min = INT32_MAX;
    if(beginWord == endWord){
        return 0;
    }
    int size = wordList.size();
    int i = 0;
    for(i = 0; i < size; i++){
        if(bitmap[i] && distance(beginWord, wordList[i]) == 1){
           bitmap[i] = false;
           min = std::min(min, ladderLengthRecur(wordList[i],endWord,wordList,bitmap));
           bitmap[i] = true; 
        }
    }
    if(min == INT32_MAX){
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

int solution::ladderLength(string beginWord, string endWord, vector<string>& wordList){
    int word_length = beginWord.size();
    map<string, vector<string>> dict;
    for(auto word : wordList){
        for(int i = 0; i < word_length; i++){
            string pattern_word = word.substr(0,i) + "*" + word.substr(i+1, word_length);
            vector<string> transformations;
            if(dict.count(pattern_word) != 0){
                dict[pattern_word].emplace_back(word);
            }
            else{
                dict[pattern_word] = vector<string>({word});
            }
        } 
    }

    queue<pair<string, int>> q;
    q.push(make_pair(beginWord,1));
    map<string,bool> visited;
    visited[beginWord] = true;
    while(!q.empty()){
        pair<string,int> entry = q.front();
        q.pop();
        string word = entry.first;
        int level = entry.second;
        for(int i = 0; i < word_length; i++){
            string pattern_word = word.substr(0,i) + "*" + word.substr(i+1, word_length);
            for(auto adjacent_word : dict[pattern_word]){
                if(adjacent_word == endWord){
                    return level + 1;
                }
                if(visited.count(adjacent_word) == 0){
                    visited[adjacent_word] = true;
                    q.push(make_pair(adjacent_word, level + 1));
                }
            }
        }
    }
    return 0;
}

vector<vector<string>> solution::findLadders(string beginWord, string endWord, vector<string>& wordList){
    int word_length = beginWord.size();
    map<string, vector<string>> dict;   
    vector<vector<string>> res;
    if(find(wordList.begin(),wordList.end(), endWord) == wordList.end()){
        return res;
    }
    for(auto word : wordList){
        for(int i = 0; i < word_length; i++){
            string pattern_word = word.substr(0,i) + "*" + word.substr(i+1, word_length);
            vector<string> transformations;
            if(dict.count(pattern_word) != 0){
                dict[pattern_word].emplace_back(word);
            }
            else{
                dict[pattern_word] = vector<string>({word});
            }
        } 
    }
    queue<vector<string>> q;
    bool found = false;
    map<string,bool> visited;
    q.push({beginWord});
    visited[beginWord] = true;
    while(!q.empty()){
        int size = q.size();
        unordered_set<string> sub_visited;
        for(int i = 0; i < size; i++){
            vector<string> path = q.front();
            q.pop();
            string word = path[path.size() - 1];
            for(int j = 0; j< word_length; j++){
                string pattern_word = word.substr(0,j) + "*" + word.substr(j+1, word_length);
                for(auto adjacent : dict[pattern_word]){
                    if(visited.count(adjacent) == 0){
                        if(adjacent == endWord){
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
        for(auto visited_word : sub_visited){
            visited[visited_word] = true;
        }
        sub_visited.clear();
        if(found){
            break;
        }
    }
    return res;
}

int solution::longestConsecutive(vector<int>& nums){
    int max = 0;
    unordered_set<int> num_set;
    for(auto i : nums){
        num_set.insert(i);
    }
    int current;
    for(auto i : nums){
        if(num_set.count(i-1) == 0){
            current = i;
            while(num_set.count(current) ==1){
                current += 1;
            }
            if(max < (current - i)){
                max = current-i;
            }
        }
    }
    return max;
}

int sumNumbersRecur(int upper, TreeNode* root){
    if(root->left == NULL && root->right == NULL){
        return upper*10 + root->val;
    }
    int res = 0;
    if(root->left){
        res += sumNumbersRecur(upper*10 + root->val,root->left);
    }
    if(root->right){
        res += sumNumbersRecur(upper*10 + root->val, root->right);
    }
    return res;
}
int solution::sumNumbers(TreeNode* root){
    if(root == NULL){
        return 0;
    }
    return sumNumbersRecur(0, root);
}

void solution::solve(vector<vector<char>> &board){
    int row = board.size();
    int column = row?board[0].size():0;
    stack<pair<int,int>> s;
    if(row == 0 || row == 1){
        return;
    }
    else{
        for(int i = 0; i < column;i++){
            if(board[0][i] == 'O'){
                board[0][i] = 'T';
                s.push(make_pair(0,i));
            }
            if(board[row - 1][i] == 'O'){
                board[row-1][i] = 'T';
                s.push(make_pair(row-1, i));
            }
        }
        for(int i = 0; i < row;i++){
            if(board[i][0] == 'O'){
                board[i][0] = 'T';
                s.push(make_pair(i,0));
            }
            if(board[i][column-1] == 'O'){
                board[i][column-1] = 'T';
                s.push(make_pair(i,column-1));
            }
        }
    }
    while(!s.empty()){
        auto position = s.top();
        s.pop();
        int i = position.first;
        int j = position.second;
        if(i!=0){
            if(board[i-1][j] == 'O'){
                board[i-1][j] = 'T';
                s.push(make_pair(i-1,j));
            }
        }
        if(i!=row-1){
            if(board[i+1][j] == 'O'){
                board[i+1][j] = 'T';
                s.push(make_pair(i+1,j));
            }
        }
        if(j!=0){
            if(board[i][j-1] == 'O'){
                board[i][j-1] = 'T';
                s.push(make_pair(i,j-1));
            }
        }
        if(j!=column-1){
            if(board[i][j+1] == 'O'){
                board[i][j+1] = 'T';
                s.push(make_pair(i,j+1));
            }
        }
    }
    for(int i = 0;i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == 'O'){
                board[i][j] = 'X';
            }
            if(board[i][j] == 'T'){
                board[i][j] = 'O';
            }
        }
    }
}

vector<vector<string>> solution::partition(string s){
    if(s.empty()){
        return vector<vector<string>>();
    }
    else if(s.size() == 1){
        return vector<vector<string>>{{s}};
    }
    else{
        vector<vector<string>> res;
        int len = s.size();
        for(int i = 0; i < len; i++){
            int j = i;
            int k = 0;
            while(j>=k){
                if(s[j] == s[k]){
                    j--;
                    k++;
                    continue;
                }
                break;
            }
            if(j < k){
                if(i < len - 1){
                auto tmp = partition(s.substr(i+1));
                for(auto& t : tmp){
                    t.insert(t.begin(),s.substr(0,i+1));
                    res.push_back(t);
                }
              }
              else{
                  res.push_back(vector<string>{s});
              }
            }
        }
        return res;
    }
}

bool is_palindrome(string& s, int start, int end){
    while(start < end){
        if(s[start] != s[end]){
            return false;
        }
        start ++;
        end --;
    }
    return true;
}

int solution::minCut(string s){
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
    if(s.empty() || s.size() == 1){
        return 0;
    }   
    int len = s.size();
    int *dp = new int[len];
    for(int i = 0; i < len; i++){
        dp[i] = i;
    }
    for(int i = 1; i < len; i++){
        if(is_palindrome(s,0,i)){
            dp[i] = 0;
            continue;
        }
        for(int j = 0; j < i; j++){
            if(is_palindrome(s,j+1,i)){
                dp[i] = min(dp[i],dp[j]+1);
            }
        }
    }
    return dp[len-1];
}

Node* solution::cloneGraph(Node* node){
    queue<Node*> q;
    queue<Node*> cloneq;
    if(!node){
        return NULL;
    }
    q.push(node);
    cloneq.push(new Node(node->val));
    Node* ret = cloneq.front();
    unordered_set<Node*> visited;
    unordered_map<Node*,Node*> nodemap;
    nodemap[node] = ret;
    while(!q.empty()){
        Node* front = q.front();
        q.pop();
        Node* clone_front = cloneq.front();
        cloneq.pop();
        if(visited.count(front) == 0){
            int neighbors_size = front->neighbors.size();
            for(int i = 0; i < neighbors_size;i++){
                q.push(front->neighbors[i]);
                if(nodemap.count(front->neighbors[i])==0){
                    clone_front->neighbors.push_back(new Node(front->neighbors[i]->val));
                    nodemap[front->neighbors[i]] = clone_front->neighbors[i];
                }
                else{
                    clone_front->neighbors.push_back(nodemap[front->neighbors[i]]);
                }
                cloneq.push(clone_front->neighbors[i]);
            }
            visited.insert(front);
        }
    }
    return ret;
}

int solution::singleNumber(vector<int>& nums){
    int ret = nums[0];
    int i = 1;
    int len = nums.size();
    while(i<len){
        ret ^= nums[i];
        i++;
    }
    return ret;
}

int solution::singleNumber2(vector<int>& nums){
    int one = 0, two = 0;
    for(auto num : nums){
        one = (one ^ num) & (~two);
        two = (two ^ num) & (~one);
    }
    return one;
}


// unknown error when submit?
vector<string> solution::wordBreak(string s, vector<string>& wordDict){
    vector<vector<vector<string>>> dp(s.length() + 1);
    dp[0] = vector<vector<string>>();
    dp[0].push_back(vector<string>(1,""));
    int len = s.length();
    for(int i = 1; i<= len; i++){
        for(int j = 0; j < i; j++){
            if(dp[j].size()>0 && find(wordDict.begin(),wordDict.end(),string(s.begin()+j,s.begin()+i))!=wordDict.end()){
                for(auto& v : dp[j]){
                    vector<string> t = v;
                    t.push_back(string(s.begin()+j,s.begin()+i));
                    dp[i].push_back(t);
                }
            }
        }
    }
    vector<string> res;
    for(auto& v: dp[len]){
        string t;
        for(auto& str : v){
            t += str;
            t += " ";
        }
        if(t.length() > 0){
            res.push_back(string(t.begin()+1,t.end()-1));
        }
    }
    return res;
}

bool solution::hasCycle(ListNode *head){ // two pointers: one fast, one slow
    if(head == NULL || head->next == NULL){
        return false;
    }
    ListNode *slow = head;
    ListNode *fast = head->next;
    while(slow != fast){
        if(fast == NULL || fast->next == NULL){
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}

ListNode* solution::detectCycle(ListNode *head){
    if(head == NULL || head->next == NULL){
        return NULL;
    }
    ListNode *fast, *slow;
    fast = head;
    slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){
            break;
        }
    }
    if(fast == NULL || fast->next == NULL){
        return NULL;
    }
    ListNode *pt1 = head;
    ListNode *pt2 = fast;
    while(pt1 != pt2){
        pt1 = pt1->next;
        pt2 = pt2->next;
    }
    return pt1;
}

ListNode* recur_reorder_list(ListNode *head, int n){
    if(n==1){
        ListNode* ret = head->next;
        head->next = nullptr;
        return ret;
    }
    if(n==2){
        ListNode* ret = head->next->next;
        head->next->next = nullptr;
        return ret;
    }
    ListNode *tail = recur_reorder_list(head->next,n-2);
    ListNode *sub_head = head->next;
    head->next = tail;
    ListNode *ret = tail->next;
    tail->next = sub_head;
    return ret;
}

ListNode* solution::reverse_list(ListNode *head){
    ListNode *pt, *prev, *next;
    if(head==nullptr || head->next == nullptr){
        return head;
    }
    prev = head;
    pt = head->next;
    while(pt){
        next = pt->next;
        pt->next = prev;
        prev = pt;
        pt = next;
    }
   head->next = nullptr;
   return prev;
}

void reorderListv2(ListNode* head){

}

void solution::reorderList(ListNode* head){
    int length = 0;
    ListNode* pt = head;
    while (pt)
    {
        length++;
        pt = pt->next;
    }
    recur_reorder_list(head,length);
}

vector<vector<int>> solution::levelOrderBottom(TreeNode *root){
        if(root == NULL){
            return vector<vector<int>>();
        }
        else{
            queue<TreeNode*> visit_queue;
            visit_queue.push(root);
            visit_queue.push(NULL);
            stack<vector<int>> reverse_res_stack;
            while (!visit_queue.empty() && visit_queue.front()!=NULL)
            {
                vector<int> level_nodes;
                while(visit_queue.front()!=NULL){
                    TreeNode* present_node = visit_queue.front();
                    visit_queue.pop();
                    if(present_node->left){
                        visit_queue.push(present_node->left);
                    }
                    if(present_node->right){
                        visit_queue.push(present_node->right);
                    }
                    level_nodes.push_back(present_node->val);
                }
                reverse_res_stack.push(level_nodes);
                visit_queue.push(NULL);
                visit_queue.pop(); // pop null node in the queue
            }
            vector<vector<int>>res;
            while (!reverse_res_stack.empty())
            {
                res.push_back(reverse_res_stack.top());
                reverse_res_stack.pop();
            }
            return res;
            
        }
}

TreeNode* solution::sortedListToBST(ListNode *head){
    if(head == NULL){
        return NULL;
    }
    if(head->next == NULL){
        return new TreeNode(head->val);
    }
    ListNode *slow, *fast, *prev;
    slow = fast = prev = head;
    while(fast!= NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    while(prev->next != slow){
        prev = prev->next;
    }
    TreeNode *root = new TreeNode(slow->val);
    prev->next = NULL;
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(slow->next);
    prev->next = slow;
    return root;
}

vector<int> solution::preorderTraversal(TreeNode *root){
    if(root == NULL){
        return vector<int>();
    }
    stack<TreeNode*> s;
    vector<int> res;
    TreeNode *entry;
    s.push(root);
    while(!s.empty()){
        entry = s.top();
        s.pop();
        res.emplace_back(entry->val);
        if(entry->right){
            s.push(entry->right);
        }
        if(entry->left){
            s.push(entry->left);
        }
    }
    return res;
}

vector<int> solution::inorderTraversal(TreeNode *root){
    if(root == NULL){
        return vector<int>();
    }
    vector<int> ret;
    TreeNode *p = root;
    stack<TreeNode*> s;
    while(p || !s.empty()){
        while(p){
            s.push(p);
            p = p->left;
        }
        if(!s.empty());
        {
            p = s.top();
            s.pop();
            ret.emplace_back(p->val);
            p = p->right;
        }
    }
    return ret;
}

vector<int> solution::postorderTraversal(TreeNode *root){
    if(root == NULL){
        return vector<int>();
    }
    TreeNode *cur = root;
    TreeNode *prev = NULL;
    stack<TreeNode*> s;
    vector<int> ret;
    while(cur || !s.empty()){
        while(cur){
            s.push(cur);
            cur = cur->left;
        }
        if(!s.empty()){
            cur = s.top();
            s.pop();
            if(cur->right == NULL || cur->right == prev){
                ret.emplace_back(cur->val);
                prev = cur;
                cur = NULL;
            }
            else{
                s.push(cur);
                cur = cur->right;
            }
        }
    }
    return ret;
}

ListNode* solution::insertionSortList(ListNode *head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    ListNode *outer = head;
    ListNode *inner = NULL;
    while(outer->next){
        inner = outer->next;
        outer->next = inner->next;
        if(inner->val >= outer->val){ //means inner is maximum
            inner->next = outer->next;
            outer->next = inner;
            outer = inner;
            continue;
        }
        if(head->val > inner->val){
            inner->next = head;
            head = inner;
        }
        else{
            ListNode *tmp1 = head;
            ListNode *tmp2 = head->next;
            while(tmp2 && tmp2->val <= inner->val && tmp2 != outer){
                tmp1 = tmp2;
                tmp2 = tmp2->next;
                if(tmp1->val > outer->val){
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

void solution::recoverTree(TreeNode *root){  //隐式中序遍历，需要注意两个异常node的顺序不同
    TreeNode* x, *y, *prev;
    TreeNode *p = root;
    stack<TreeNode*> s;
    prev = NULL;
    x = NULL;
    y = NULL;
    if(root == NULL){
        return;
    }
    while (p || !s.empty())
    {
        while (p)
        {
            s.push(p);
            p = p->left;
        }
        if(!s.empty()){
            if(!prev){
                prev = s.top();
                s.pop();
                p = prev->right;
                continue;
            }
            p = s.top();
            s.pop();
            if(prev->val > p->val){
                y = p;
                if(!x){
                    x = prev;
                }
                else{
                    break;
                }
            }
            prev = p;
            p = p->right;
        }
    }
    swap(x->val, y->val);
}

ListNode* solution::mergesortList_recursion(ListNode *head){
    if(head == NULL || head->next == NULL){
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
    ListNode  res = ListNode(0);
    ListNode *merge = &res;
    // merge two sorted list
    while(left != NULL && right != NULL){
        if(left->val > right->val){
            merge->next = right;
            right = right->next;
        }
        else{
            merge->next = left;
            left = left->next;
        }
        merge = merge->next;
    }
    merge->next = left?left:right;
    return res.next;
}

ListNode* solution::mergesortList(ListNode *head){

}