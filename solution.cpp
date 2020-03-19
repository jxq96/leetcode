#include "solution.h"
#include <algorithm>
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