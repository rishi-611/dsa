#include <iostream>
using namespace std;

class BstNode;
void insert(BstNode **root, int data);
bool search(BstNode *root, int data);
int findMax(BstNode *root);
int findMin(BstNode *root);

class BstNode
{
private:
    int data;
    BstNode *left;
    BstNode *right;

public:
    BstNode(int val) : data{val}, left{nullptr}, right{nullptr} {};

    friend void insert(BstNode **, int);
    friend bool search(BstNode *, int);
    friend int findMax(BstNode *root);
    friend int findMin(BstNode *root);
    int getData()
    {
        return data;
    }
};

// since root is a local variable here, we cant manipulate main's root in this function, as it will be only a copy of main's root
// so we pass the address of root function from main, and in the function, we receive a pointer to the root pointer
void insert(BstNode **root, int data)
{
    // create new node in heap
    BstNode *temp = new BstNode(data);

    if (*root == nullptr)
    {
        *root = temp;
        return;
    }
    if (data > (*root)->data)
    {
        // we need to pass address of the local root->right
        insert(&((*root)->right), data);
    }
    else
    {
        insert(&((*root)->left), data);
    }
}

// since we dont need to modify root, we dont need a double pointer
bool search(BstNode *root, int data)
{
    if (root == nullptr)
        return false;

    if (data == root->data)
        return true;

    if (data > root->data)
        return search(root->right, data);

    return search(root->left, data);
}

int findMax(BstNode *root)
{
    if (root == nullptr)
        return INT_MIN;

    while (root->right != nullptr)
    {
        root = root->right;
    }

    return root->data;
}

int findMin(BstNode *root)
{
    if (root == nullptr)
        return INT_MIN;

    while (root->left != nullptr)
    {
        root = root->left;
    }

    return root->data;
}

int main()
{
    // initialize an empty binary tree
    BstNode *root = nullptr;

    // insertion
    insert(&root, 5);
    insert(&root, 10);
    insert(&root, 1);
    insert(&root, 7);
    insert(&root, 1);

    cout << boolalpha << search(root, 7) << endl; // true
    cout << search(root, 3) << endl
         << endl; // false

    cout << "Maximum number in tree: " << findMax(root) << endl; // 10

    cout << "Minimum number in tree: " << findMin(root) << endl
         << endl; // 1

    system("pause");
    return 0;
}