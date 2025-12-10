#include <fstream>
#include <vector>
#include <string>

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

    node* findMin(node* nod)
    {
        while (nod && nod->left)
            nod = nod->left;
        return nod;
    }

    node* remove(node* nod, int key)
    {
        if (!nod) return nullptr;

        if (key < nod->key)
        {
            nod->left = remove(nod->left, key);
        }
        else if (key > nod->key)
        {
            nod->right = remove(nod->right, key);
        }
        else
        {
            if (!nod->left)
            {
                node* temp = nod->right;
                delete nod;
                return temp;
            }
            else if (!nod->right)
            {
                node* temp = nod->left;
                delete nod;
                return temp;
            }
            else
            {
                node* temp = findMin(nod->right);
                nod->key = temp->key;
                nod->right = remove(nod->right, temp->key);
            }
        }
        return nod;
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

    void remove(int key)
    {
        root = remove(root, key);
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree tree;
    int key, temp;
    string t;

    in >> key;
    getline(in, t); 
    getline(in, t);

    while (in >> temp)
    {
        tree.insert(temp);
    }

    tree.remove(key);
    vector<int> result = tree.preorderTravl();

    for (int k : result)
    {
        out << k << endl;
    }

    return 0;
}