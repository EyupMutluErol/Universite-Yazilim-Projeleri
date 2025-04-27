/**
* ListNode.cpp
* Bu kod bağlı liste üzerinde silme , ekranda listeyi gösterme ve imleçle gösterme işlemlerini yapar
* 1.Öğretim B Grubu
* 2.Ödev
* 21.12.2024
* Eyüp Mutlu Erol / mutlu.erol@ogr.sakarya.edu.tr
*/

#include "ListNode.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

ListNode::ListNode(TreeNode* root) : treeRoot(root), next(nullptr) {}

void deleteListNode(ListNode*& head, int index) {
    if (!head) return;
    ListNode* current = head;
    ListNode* previous = nullptr;

    for (int i = 0; i < index && current != nullptr; ++i) {
        previous = current;
        current = current->next;
    }

    if (!current) return;

    if (!previous) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
}

void displayList(ListNode* head, int highlightIndex, int page, int pageSize) {
    const int COLUMN_WIDTH = 15;
    ListNode* current = head;
    vector<ListNode*> nodes;

    while (current) {
        nodes.push_back(current);
        current = current->next;
    }

    int start = page * pageSize;
    int end = min(start + pageSize, static_cast<int>(nodes.size()));

    for (int i = start; i < end; ++i) {
        auto addressValue = reinterpret_cast<uintptr_t>(nodes[i]) % 10000;
        cout << setw(COLUMN_WIDTH) << left << addressValue;
    }
    cout << "\n";

    for (int i = start; i < end; ++i) {
        int treeValue = calculateTreeValue(nodes[i]->treeRoot);
        cout << setw(COLUMN_WIDTH) << left << treeValue;
    }
    cout << "\n";

    for (int i = start; i < end; ++i) {
        if (nodes[i]->next) {
            auto nextAddressValue = reinterpret_cast<uintptr_t>(nodes[i]->next) % 10000;
            cout << setw(COLUMN_WIDTH) << left << nextAddressValue;
        } else {
            cout << setw(COLUMN_WIDTH) << left << "0";
        }
    }
    cout << "\n";

    if (highlightIndex >= start && highlightIndex < end) {
        for (int i = start; i < highlightIndex; ++i) {
            cout << setw(COLUMN_WIDTH) << " ";
        }
        cout << "^^^^^\n";
        for (int i = start; i < highlightIndex; ++i) {
            cout << setw(COLUMN_WIDTH) << " ";
        }
        cout << "|||||\n";
    }
}
