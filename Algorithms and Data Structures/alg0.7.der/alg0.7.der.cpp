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

        int height;
        int depth;

        node(int k, node* p = nullptr) : key(k), left(nullptr), right(nullptr), parent(p), height(0), depth(0) {}
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

    void postorderl(node* nod, vector<int>& result) const
    {
        if (nod)
        {
            postorderl(nod->left, result);
            postorderl(nod->right, result);
            result.push_back(nod->key);
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

    int vichHeigh(node* nod) const
    {
        if (!nod) return -1;

        int leftH = vichHeigh(nod->left);
        int rightH = vichHeigh(nod->right);

        nod->height = 1 + max(leftH, rightH);
        return nod->height;
    }

    void vichDepth(node* nod, int depth) const
    {
        if (!nod) return;

        nod->depth = depth;

        vichDepth(nod->left, depth + 1);
        vichDepth(nod->right, depth + 1);
    }

    void collectLevelNodes(node* nod, int level, vector<node*>& result) const
    {
        if (!nod) return;
        if (root->height - nod->depth == level)
        {
            result.push_back(nod);
        }
        collectLevelNodes(nod->left, level, result);
        collectLevelNodes(nod->right, level, result);
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

    vector<int> postorderTravl() const
    {
        vector<int> result;
        postorderl(root, result);
        return result;
    }

    void remove(int key)
    {
        root = remove(root, key);
    }

    void updHeigh()
    {
        vichHeigh(root);
    }

    void updDepth()
    {
        vichDepth(root, 0);
    }

    int getRootH() const
    {
        return root->height;
    }

    vector<int> balanced(int level) const
    {
        vector<node*> levelNodes;
        collectLevelNodes(root, level, levelNodes);

        vector<int> result;
        for (auto* n : levelNodes)
        {
            int hl = (n->left ? n->left->height : -1);
            int hr = (n->right ? n->right->height : -1);
            if (hl == hr)
            {
                result.push_back(n->key);
            }
        }
        return result;
    }

};

int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");

    Tree tree;
    int temp;

    while (in >> temp)
    {
        tree.insert(temp);
    }

    tree.updHeigh();
    tree.updDepth();

    int targetLevel = tree.getRootH() / 2;

    vector<int> balance = tree.balanced(targetLevel);

    if (balance.size() % 2 == 1)
    {
        int midKey = balance[balance.size() / 2];
        tree.remove(midKey);
    }

    vector<int> result = tree.preorderTravl();

    for (int k : result)
    {
        out << k << endl;
    }

    return 0;
}