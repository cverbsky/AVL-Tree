#include "Avl.h"

using namespace std;

// Helper functions
bool validName(string& name);
bool validId(string& gatorId);

int main()
{
    string command;
    string name;
    string gatorId;
    AVLTree avlTree;

    int numCommands = 0;
    cin >> numCommands; // initial input is # of commands
    for (int i = 0; i < numCommands; i++)
    {
       cin >> command;

        /*====== Insert "Name" ID into AVL ======*/
        if (command == "insert")
        {
            string space;
            getline(cin, space, '\"');
            getline(cin, name, '\"');
            cin >> gatorId;

            if (validName(name) && validId(gatorId))
            {
                if (avlTree.insert(name, gatorId)) {
                    cout << "successful" << endl;
                }
                else
                    cout << "unsuccessful" << endl;
            }
            else
                cout << "unsuccessful" << endl;
        }

        /*====== Remove ID from AVL ======*/
        else if (command == "remove")
        {
            cin >> gatorId;
            if (validId(gatorId))
            {
                if (avlTree.remove(gatorId))
                    cout << "successful" << endl;
                else
                    cout << "unsuccessful" << endl;
            }
            else
                cout << "unsuccessful" << endl;
        }

        /*====== Remove node at Inorder location n ======*/
        else if (command == "removeInorder")
        {
            int n = 0;
            cin >> n;
            if (avlTree.removeInorder(n))
                cout << "successful" << endl;
            else
                cout << "unsuccessful" << endl;
        }

        /*====== Search "Name" or ID ======*/
        else if (command == "search")
        {
            string space;
            getline(cin, space, ' ');
            string nameOrId;
            getline(cin, nameOrId);
            if (isalpha(nameOrId[1])) // might be name
            {
                name = nameOrId.substr(1, nameOrId.size()-2);
                if (validName(name))
                {
                    vector<AVLTree::avlNode*> matchingNames = avlTree.searchName(avlTree.root, name);
                    if (!matchingNames.empty())
                        for (int j = 0; j < matchingNames.size(); j++)
                            cout << matchingNames.at(j)->gatorId << endl;
                    else
                        cout << "unsuccessful" << endl;
                }
                else
                    cout << "unsuccessful" << endl;
            }
            else // nameOrId is something other than alphabetic char
            {
                gatorId = nameOrId;
                if (validId(gatorId))
                {
                    AVLTree::avlNode* matchingNode = avlTree.searchId(avlTree.root, gatorId);
                    if (matchingNode != nullptr)
                            cout << matchingNode->name << endl;
                    else
                        cout << "unsuccessful" << endl;
                }
                else
                    cout << "unsuccessful" << endl;
            }
        }

        /*====== Print Commands ======*/
        else if (command == "printInorder")
            avlTree.printInorder(avlTree.root);

        else if (command == "printPreorder")
            avlTree.printPreorder(avlTree.root);

        else if (command == "printPostorder")
            avlTree.printPostorder(avlTree.root);

        else if (command == "printLevelCount")
            avlTree.printLevelCount(avlTree.root);
    }

    return 0;
}

bool validName(string& name)
{
    for (int i = 0; i < name.size(); i++)
    {
        if (!isalpha(name[i]) && !isblank(name[i]))
            return false;
    }
    return true;
}

bool validId(string& gatorId)
{
    if (gatorId.size() != 8)
        return false;

    for (int i = 0; i < gatorId.size(); i++)
    {
        if (!isdigit(gatorId[i]))
            return false;
    }
    return true;
}
