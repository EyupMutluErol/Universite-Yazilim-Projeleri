#include <string>
#ifndef TREENODE_HPP
#define TREENODE_HPP

using namespace std;

struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char value);
};

// Ağaç yapısına yeni karakteri ekleyen fonksiyon
TreeNode* insertToBST(TreeNode* root, char value);

// Her bir satırdaki verileri alıp ağacı oluşturma fonksiyonu
TreeNode* buildTreeFromLine(const string& line);

// Ağaç değerini hesaplama fonksiyonu
int calculateTreeValue(TreeNode* node, bool isLeft = false);

// Ağaçta simetriyi gerçekleştiren fonksiyon
void mirrorTree(TreeNode* node);

#endif
