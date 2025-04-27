/**
* TreeNode.cpp
* Bu kod ikili arama ağacını oluşturma , ağaç verisini hesaplama , aynalama işlemlerini yapar
* 1.Öğretim B Grubu
* 2.Ödev
* 22.12.2024
* Eyüp Mutlu Erol / mutlu.erol@ogr.sakarya.edu.tr
*/
#include "TreeNode.hpp"
using namespace std;

TreeNode::TreeNode(char value) : data(value), left(nullptr), right(nullptr) {}

TreeNode* insertToBST(TreeNode* root, char value) {
    if (!root) return new TreeNode(value);
    if (value <= root->data)
        root->left = insertToBST(root->left, value);
    else
        root->right = insertToBST(root->right, value);
    return root;
}

TreeNode* buildTreeFromLine(const string& line) {
    TreeNode* root = nullptr;
    for (char ch : line) {
        root = insertToBST(root, ch);
    }
    return root;
}

int calculateTreeValue(TreeNode* node, bool isLeft) {
    if (!node) return 0;
    int multiplier = isLeft ? 2 : 1;
    int nodeValue = node->data * multiplier;
    int leftValue = calculateTreeValue(node->left, true);
    int rightValue = calculateTreeValue(node->right, false);
    return nodeValue + leftValue + rightValue;
}

void mirrorTree(TreeNode* node) {
    if (!node) return;
    swap(node->left, node->right);
    mirrorTree(node->left);
    mirrorTree(node->right);
}
