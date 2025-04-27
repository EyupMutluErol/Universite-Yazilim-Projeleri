#ifndef TREEDRAWING_HPP
#define TREEDRAWING_HPP

#include "TreeNode.hpp"
#include <vector>
#include <string>
using namespace std;

// Ağaçları ekranda çizme fonksiyonu
void drawTree(TreeNode* root, int x, int y, vector<string>& canvas, int offset = 8);

// Ekrandaki tüm çizimi yazdırma fonksiyonu
void printCanvas(const vector<string>& canvas);

#endif
