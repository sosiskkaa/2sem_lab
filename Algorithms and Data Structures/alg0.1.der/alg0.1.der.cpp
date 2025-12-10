#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Tree 
{
private:
    struct node 
    {
        int key;
        node* left;
        node* right;
        node* parent;

        node(int k, node* p = nullptr) : key(k), left(nullptr), right(nullptr), parent(p) {}
    };

    node* root;

    node* insert(node* nod, int key, node* parent) 
    {
        if (!nod)
            return new node(key, parent);
        if (key < nod->key)
            nod->left = insert(nod->left, key, nod);
        else if (key > nod->key)
            nod->right = insert(nod->right, key, nod);
        return nod;
    }

    void preorderl(node* nod, vector<int>& result) const 
    {
        if (nod) 
        {
            result.push_back(nod->key);
            preorderl(nod->left, result);
            preorderl(nod->right, result);
        }
    }

    void destroy(node* nod) 
    {
        if (nod) 
        {
            destroy(nod->left);
            destroy(nod->right);
            delete nod;
        }
    }

public:
    Tree() : root(nullptr) {}

    ~Tree() 
    {
        destroy(root);
    }

    void insert(int key) 
    {
        root = insert(root, key, nullptr);
    }

    vector<int> preorderTravl() const 
    {
        vector<int> result;
        preorderl(root, result);
        return result;
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree tree;
    int key;

    while (in >> key) 
    {
        tree.insert(key);
    }

    vector<int> result = tree.preorderTravl();

    for (int k : result) 
    {
        out << k << endl;
    }

    return 0;
}