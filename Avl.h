#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

#pragma once

class AVLTree
{
public:
    struct avlNode
    {
        string name;
        string gatorId;

        int balanceFactor = 0;
        avlNode *left = nullptr;
        avlNode *right = nullptr;
    };

    avlNode* root = nullptr;
    vector<avlNode*> inorderArray;

    /*====== Insert, Remove and Search ======*/
    bool insert(string& name, string& gatorId);
    bool remove(string& gatorId);
    bool removeInorder(int n);
    vector<avlNode*>searchName(avlNode* node, string& name);
    avlNode* searchId(avlNode* node, string& gatorId);

    /*====== Print Functions ======*/
    void printInorder(avlNode* root);
    void printPreorder(avlNode* root);
    void printPostorder(avlNode* root);
    void printLevelCount(avlNode* root);

    /*====== Node Functions ======*/
    int height(avlNode* node);
    void updateBalanceFactor(avlNode* node);

    /*====== Tree Functions ======*/
    avlNode* balance(avlNode* node);
    void treeToInorderArray(avlNode* node);
    avlNode* minValue(avlNode* node);
    avlNode* maxValue(avlNode* node);

private:
    /*====== Recursive Insert and Remove ======*/
    avlNode* insertRecursive(avlNode* node, string& name, string& gatorId);
    avlNode* removeRecursive(avlNode* node, string& gatorId);

    /*====== Rotations ======*/
    avlNode* rotateLeft(avlNode* node);
    avlNode* rotateRight(avlNode* node);
    avlNode* rotateLeftRight(avlNode* node);
    avlNode* rotateRightLeft(avlNode* node);
};
