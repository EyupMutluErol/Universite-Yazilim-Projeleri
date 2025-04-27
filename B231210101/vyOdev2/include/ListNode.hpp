#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include "TreeNode.hpp"
#include <vector>
#include <string>
using namespace std;

struct ListNode {
    TreeNode* treeRoot;
    ListNode* next;
    ListNode(TreeNode* root);
};

// Seçilen düğümü silme fonksiyonu
void deleteListNode(ListNode*& head, int index);

// List node'ları yazdırma fonksiyonu
void displayList(ListNode* head, int highlightIndex, int page, int pageSize);

#endif
