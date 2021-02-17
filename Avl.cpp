#include "Avl.h"

/*====== Insert, Remove and Search ======*/
bool AVLTree::insert(string& name, string& gatorId)
{
    if (searchId(root, gatorId) != nullptr)
        return false;
    else
    {
        root = insertRecursive(root, name, gatorId);
        root = balance(root);
        updateBalanceFactor(root);
        return true;
    }
}
bool AVLTree::remove(string& gatorId)
{
    if (searchId(root, gatorId) == nullptr)
        return false;
    else
    {
        root = removeRecursive(root, gatorId);
        root = balance(root);
        updateBalanceFactor(root);
        return true;
    }
}
bool AVLTree::removeInorder(int n)
{
    treeToInorderArray(root);
    if (n > inorderArray.size() - 1 || n < 0)
        return false;
    return remove(inorderArray.at(n)->gatorId);
}
vector<AVLTree::avlNode*> AVLTree::searchName(avlNode* node, string& name)
{
    vector<AVLTree::avlNode*> matchingNames;
    inorderArray.clear();
    treeToInorderArray(root);
    for (int i = 0; i < inorderArray.size(); i++)
    {
        if (inorderArray.at(i)->name == name)
            matchingNames.push_back(inorderArray.at(i));
    }
    return matchingNames;
}
AVLTree::avlNode* AVLTree::searchId(avlNode* node, string& gatorId)
{
    if (node == nullptr)
        return nullptr;
    else if (gatorId < node->gatorId)
        return searchId(node->left, gatorId);
    else if (gatorId > node->gatorId)
        return searchId(node->right, gatorId);
    else
        return node;
}

/*====== Node Functions ======*/
int AVLTree::height(avlNode* node) // returns the height of a subtree given the root of that tree
{
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 1;
    else if (node->left == nullptr)
        return height(node->right) + 1;
    else if (node->right == nullptr)
        return height(node->left) + 1;
    else
        return std::max(height(node->left), height(node->right)) + 1;
}
void AVLTree::updateBalanceFactor(avlNode* node)
{
    // Preorder traversal
    if (node == nullptr)
        return;
    else
    {
        node->balanceFactor = height(node->left) - height(node->right);
        updateBalanceFactor(node->left);
        updateBalanceFactor(node->right);
    }
}

/*====== Tree Functions ======*/
AVLTree::avlNode* AVLTree::balance(avlNode* node)
{
    if (node == nullptr)
        return node;
    updateBalanceFactor(root);
    node->left = balance(node->left);
    node->right = balance(node->right);
    updateBalanceFactor(root);
    // check if unbalanced
    if (abs(node->balanceFactor) > 1)
    {
            if (node->balanceFactor == -2 && node->right->balanceFactor == -1) // Right Right Case
                node = rotateLeft(node);
            else if (node->balanceFactor == -2 && node->right->balanceFactor == 1) // Right Left Case
                node = rotateRightLeft(node);
            else if (node->balanceFactor == 2 && node->left->balanceFactor == 1) // Left Left Case
                node = rotateRight(node);
            else if (node->balanceFactor == 2 && node->left->balanceFactor == -1) // Left Right Case
                node = rotateLeftRight(node);
    }

    return node;
}
void AVLTree::treeToInorderArray(avlNode* node)
{
    if (node == nullptr)
        return;
    else
    {   // Inorder rehearsal
        treeToInorderArray(node->left);
        inorderArray.push_back(node);
        treeToInorderArray(node->right);
    }

}
AVLTree::avlNode* AVLTree::minValue(avlNode* node)
{
    if (node->left == nullptr)
        return node;
    else return minValue(node->left);
}
AVLTree::avlNode* AVLTree::maxValue(avlNode* node)
{
    if (node->right == nullptr)
        return node;
    else return maxValue(node->right);
}

/*====== Print Functions ======*/
void AVLTree::printInorder(avlNode* root)
{
    if (root == nullptr)
        return;
    else
    {
        printInorder(root->left);
        cout << root->name;
        // For purpose of last element
        if (root != maxValue(this->root))
            cout << ", ";
        else
            cout << endl;
        printInorder(root->right);
    }
}
void AVLTree::printPreorder(avlNode* root)
{
    if (root == nullptr)
        return;
    else
    {
        cout << root->name;
        // For purpose of last element
        if (root != maxValue(this->root))
            cout << ", ";
        else //root == max
        {
            if (root->left == nullptr)
                cout << endl;
            else
                cout << ", " << root->left->name << endl;
            return;
        }
        printPreorder(root->left);
        printPreorder(root->right);
    }
}
void AVLTree::printPostorder(avlNode* root)
{
    if (root == nullptr)
        return;
    else
    {
        printPostorder(root->left);
        printPostorder(root->right);
        cout << root->name;
        // For purpose of last element
        if (root != this->root)
            cout << ", ";
        else
            cout << endl;
    }
}
void AVLTree::printLevelCount(avlNode* root)
{
    queue<avlNode*> levels;
    int numLevels = 0;

    if (root != nullptr)
    {
        if (root->left != nullptr)
            levels.push(root->left);
        if (root->right != nullptr)
            levels.push(root->right);
        numLevels++;
    }
    else
    {
        cout << numLevels << endl;
        return;
    }
    while (!levels.empty())
    {
        int index = levels.size();
        for (int i = 0; i < index; i++)
        {
            if (levels.front()->left != nullptr)
                levels.push(levels.front()->left);
            if (levels.front()->right != nullptr)
                levels.push(levels.front()->right);
            levels.pop();
        }
        numLevels++;
    }
    cout << numLevels << endl;
}

/*====== Recursive Insert and Remove ======*/
AVLTree::avlNode* AVLTree::insertRecursive(avlNode* node, string& name, string& gatorId)
{
    if (node == nullptr)
    {
        node = new avlNode;
        node->name = name;
        node->gatorId = gatorId;
        return node;
    }
    else if (gatorId < node->gatorId) // traverse left side
        node->left = insertRecursive(node->left, name, gatorId);
    else // traverse right side
        node->right = insertRecursive(node->right, name, gatorId);
    return node;
}
AVLTree::avlNode* AVLTree::removeRecursive(avlNode* node, string& gatorId)
{
    if (node == nullptr)
        return node;
    if (gatorId < node->gatorId)
    {
        node->left = removeRecursive(node->left, gatorId);
        return node;
    }
    else if (gatorId > node->gatorId)
    {
        node->right = removeRecursive(node->right, gatorId);
        return node;
    }
    else // gatorId == node->gatorId
    {
        avlNode* temp = node;
        if (temp->left == nullptr)
        {
            delete node;
            node = temp->right;
            return node;
        }
        else if (temp->right == nullptr)
        {
            delete node;
            node = temp->left;
            return node;
        }
        else
        {
            // find leftmost node in right subtree, move to node, and delete this leftmost node
            temp = minValue(node->right);
            node->name = temp->name;
            node->gatorId = temp->gatorId;
            node->right = removeRecursive(node->right,temp->gatorId);
            return node;
        }
    }
}

/*====== Rotations ======*/
AVLTree::avlNode* AVLTree::rotateLeft(avlNode* node)
{
    avlNode* grandchild = node->right->left;
    avlNode* parent = node->right;
    node->right = grandchild;
    parent->left = node;
    return parent;
}
AVLTree::avlNode* AVLTree::rotateRight(avlNode* node)
{
    avlNode* grandchild = node->left->right;
    avlNode* parent = node->left;
    node->left = grandchild;
    parent->right = node;
    return parent;
}
AVLTree::avlNode* AVLTree::rotateLeftRight(avlNode* node)
{
    // Rotate Left
    avlNode* grandchild = node->left;
    avlNode* newLeft = grandchild->right;
    grandchild->right = newLeft->left;
    node->left = newLeft;
    node->left->left = grandchild;
    // Rotate Right
    return rotateRight(node);
}
AVLTree::avlNode* AVLTree::rotateRightLeft(avlNode* node)
{
    // Rotate Right
    avlNode* grandchild = node->right->left;
    node->right->left = grandchild->right;
    grandchild->right = node->right;
    node->right = grandchild;
    //Rotate Left
    return rotateLeft(node);
}
