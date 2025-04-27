/**
* main.cpp
* Bu kod Kullanıcıya terminal üzerinden listeyi gezme, seçilen ağacın simetrisini alma,düğümleri silme ve programdan çıkma gibi seçenekler sunar.
* 1.Öğretim B Grubu
* 2.Ödev
* 22.12.2024
* Eyüp Mutlu Erol / mutlu.erol@ogr.sakarya.edu.tr
*/
#include "ListNode.hpp"
#include "TreeDrawing.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

int main() {
    ifstream inputFile("agaclar.txt");
    if (!inputFile) {
        cerr << "Dosya acilamadi." << endl;
        return 1;
    }

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    string line;
    while (getline(inputFile, line)) {
        TreeNode* treeRoot = buildTreeFromLine(line);  // Her satır için ağacı oluşturdum
        ListNode* newNode = new ListNode(treeRoot);
        if (!head) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    inputFile.close();

    int highlightIndex = 0;
    int page = 0;
    const int pageSize = 10;

    while (true) {
        system("cls");

        
        vector<string> canvas(20, string(80, ' '));

        // Listeyi yazdırdım
        displayList(head, highlightIndex, page, pageSize);

        // Seçilen düğümün ağacını çizdim
        ListNode* current = head;
        int index = 0;
        while (current && index < highlightIndex) {
            current = current->next;
            index++;
        }
        if (current) {
            drawTree(current->treeRoot, 40, 0, canvas, 16);  // Ağacı çizdim
        }

        
        printCanvas(canvas);

        // Kullanıcıdan secim alma 
        cout << "\nSecim (a: sola git, d: saga git, w: aynalama, s: sil, q: cikis): ";
        char ch;
        cin >> ch;

        if (ch == 'd') {
            ++highlightIndex;
            if (highlightIndex >= pageSize * (page + 1)) {
                ++page;
            }
        } else if (ch == 'a' && highlightIndex > 0) {
            --highlightIndex;
            if (highlightIndex < pageSize * page) {
                --page;
            }
        } else if (ch == 'w') {
            // 'w' tuşuna basıldığında simetriyi uygulama
            ListNode* current = head;
            int index = 0;
            while (current && index < highlightIndex) {
                current = current->next;
                index++;
            }
            if (current) {
                mirrorTree(current->treeRoot);  
            }
        } else if (ch == 's') {
            // 's' tuşuna basıldığında seçili düğümü silme
            deleteListNode(head, highlightIndex);

            // Eğer silinen düğüm baştaysa ve başka düğümler varsa, imleci başa aldım
            if (highlightIndex == 0 && head) {
                highlightIndex = 0;
            } else {
                // Silinen düğümün bir öncekine geçiş yaptım
                --highlightIndex;
            }

            
            int totalNodes = 0;
            ListNode* temp = head;
            while (temp) {
                ++totalNodes;
                temp = temp->next;
            }
            page = highlightIndex / pageSize;
        } else if (ch == 'q') {
            break;
        }
    }

    // Bellek temizliği
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
