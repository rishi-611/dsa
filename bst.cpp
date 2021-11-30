#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

class BstNode;
void insert(BstNode **root, int data);
bool search(BstNode *root, int data);
int findMax(BstNode *root);
int findMin(BstNode *root);
int getHeight(BstNode *root);
void printInorder(BstNode *root);
void printPreorder(BstNode *root);

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
    friend int getHeight(BstNode *root);
    friend void printInorder(BstNode *root);
    friend void printPreorder(BstNode *root);
    friend void printPostorder(BstNode *root);

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

// returns height of tree (max distance from a leaf node)
int getHeight(BstNode *root)
{
    // for a tree with only root, height is zero as no further traversal is required to reach a leaf node
    // so for a null node, root will be -1
    if (root == nullptr)
        return -1;

    // otherwise height will be one plus the height of the maximum of heights bw left and right subtrees
    return (max(getHeight(root->right), getHeight(root->left)) + 1);
}

void printInorder(BstNode *root)
{
    if (root == nullptr)
        return;

    printInorder(root->left);
    std::cout << root->data << " ";
    printInorder(root->right);
}

void printPreorder(BstNode *root)
{
    if (root == nullptr)
        return;

    std::cout << root->data << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(BstNode *root)
{
    if (root == nullptr)
        return;

    printPostorder(root->left);
    printPostorder(root->right);
    std::cout << root->data << " ";
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

    // insert(&root, 1);
    // insert(&root, 2);
    // insert(&root, 3);
    // insert(&root, 4);
    // insert(&root, 5);

    cout << boolalpha << search(root, 7) << endl; // true
    cout << search(root, 3) << endl
         << endl; // false

    cout << "Maximum number in tree: " << findMax(root) << endl; // 10

    cout << "Minimum number in tree: " << findMin(root) << endl
         << endl; // 1

    cout << "Height of tree: " << getHeight(root) << endl
         << endl;

    printInorder(root);
    cout << endl;
    printPreorder(root);
    cout << endl;
    printPostorder(root);
    cout << endl;
    cout << endl;

    system("pause");
    return 0;
}