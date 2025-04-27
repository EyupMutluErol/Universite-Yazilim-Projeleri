/**
* TreeDrawing.cpp
* Bu kod ağaç çizdirme işlemini yapar
* 1.Öğretim B Grubu
* 2.Ödev
* 22.12.2024
* Eyüp Mutlu Erol / mutlu.erol@ogr.sakarya.edu.tr
*/
#include "TreeDrawing.hpp"
#include <iostream>
using namespace std;

void drawTree(TreeNode* root, int x, int y, vector<string>& canvas, int offset) {
    if (!root || x < 0 || x >= canvas[0].size() || y >= canvas.size()) return;

    canvas[y][x] = root->data; // Ağacın düğümünü yerleştirdim

    int newOffset = offset > 4 ? offset / 2 : 4; // Daha geniş bir ofset belirledim

    if (root->left) {
        int leftX = x - offset;
        int leftY = y + 2;

        // Noktaları daha geniş yerleştirmek için aradaki mesafeyi artırdım
        for (int i = 1; i <= offset; ++i) {
            if (x - i >= 0 && y + 1 < canvas.size())
                canvas[y + 1][x - i] = '.';
        }
        drawTree(root->left, leftX, leftY, canvas, newOffset);
    }

    if (root->right) {
        int rightX = x + offset;
        int rightY = y + 2;

        // Sağ bağlantıdaki noktaların mesafesini artırdım
        for (int i = 1; i <= offset; ++i) {
            if (x + i < canvas[0].size() && y + 1 < canvas.size())
                canvas[y + 1][x + i] = '.';
        }
        drawTree(root->right, rightX, rightY, canvas, newOffset);
    }
}


void printCanvas(const vector<string>& canvas) {
    for (const auto& line : canvas) {
        std::cout << line << '\n';
    }
}
