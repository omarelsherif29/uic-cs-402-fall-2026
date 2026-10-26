#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>

#include "Omar_Elsherif_project3.h"

using namespace std;

const string who_am_i() {
    return "Omar_Elsherif";
}

vector<int> weird_traversal(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return result;
 
    vector<int> odd_nodes;
    queue<TreeNode*> q;
    q.push(root);
    int layer = 0;

    while (!q.empty()) {
        size_t level_size = q.size();
        for (size_t i = 0; i < level_size; ++i) {
            TreeNode* curr = q.front();
            q.pop();
            if (layer % 2 == 0) result.push_back(curr->id);
            else odd_nodes.push_back(curr->id);
 
            for (TreeNode* c = curr->first_child; c != nullptr; c = c->next_sibling)
                q.push(c);
        }
        ++layer;
    }
    result.insert(result.end(), odd_nodes.rbegin(), odd_nodes.rend());

    return result;
}

TreeNode* bits_to_tree(const vector<bool>& bits) {
    if (bits.size() % 2 != 0) return nullptr;
    
    int balance = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
        balance += bits[i] ? 1 : -1;
        if (balance < 0) return nullptr;
    }
    if (balance != 0) return nullptr;
    
    int next_id = 0;
    TreeNode* root = new TreeNode{next_id++, nullptr, nullptr};
 
    stack<TreeNode*> path;       
    stack<TreeNode*> last_child; 
    path.push(root);
    last_child.push(nullptr);
 
    for (size_t i = 0; i < bits.size(); ++i) {
        if (bits[i]) {
            TreeNode* n = new TreeNode{next_id++, nullptr, nullptr};
            if (last_child.top() == nullptr) path.top()->first_child = n;
            else last_child.top()->next_sibling = n;
            last_child.top() = n;
            path.push(n);
            last_child.push(nullptr);
        } else {
            path.pop();
            last_child.pop();
        }
    }
    return root;
}

static ParseTreeNode* parse_expression(const string& s, size_t& pos);
static ParseTreeNode* parse_unary(const string& s, size_t& pos);
 
static ParseTreeNode* parse_expression(const string& s, size_t& pos) {
    ParseTreeNode* left = parse_unary(s, pos);
    while (pos < s.size() && (s[pos] == '|' || s[pos] == '^')) {
        char op = s[pos++];
        ParseTreeNode* right = parse_unary(s, pos);
        left = new ParseTreeNode{op, left, right};
    }
    return left;
}
 
static ParseTreeNode* parse_unary(const string& s, size_t& pos) {
    if (pos >= s.size()) return nullptr;
    char c = s[pos];
    if (c == '~') {
        ++pos;
        ParseTreeNode* child = parse_unary(s, pos);
        return new ParseTreeNode{'~', child, nullptr};
    }
    if (c == '(') {
        ++pos;
        ParseTreeNode* inner = parse_expression(s, pos);
        if (pos < s.size() && s[pos] == ')') ++pos;
        return inner;
    }
    ++pos;
    return new ParseTreeNode{c, nullptr, nullptr};
}
 
ParseTreeNode* build_parse_tree(const string& expr) {
    if (expr.empty()) return nullptr;
    size_t pos = 0;
    return parse_expression(expr, pos);
}

int main() {
    return 0;
}
