#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits.h>
#include <queue>
using namespace std;

class BstNode;
void insert(BstNode **root, int data);
bool search(BstNode *root, int data);
int findMax(BstNode *root);
int findMin(BstNode *root);
int getHeight(BstNode *root);
void printInorder(BstNode *root);
void printPreorder(BstNode *root);
void printLevelOrder(BstNode *root);
void printLevHelper(BstNode *root, std::queue<BstNode *> q);
bool isBst(BstNode *root);
void inOrder(BstNode *root, vector<int> &v);
BstNode *remove(BstNode *root, int data);
BstNode *findElem(BstNode *root, int data);
BstNode *findMaxElem(BstNode *root);
void printAllPaths(BstNode *root);
void printPathsHelper(BstNode *root, vector<int> &path);

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
    friend void printLevelOrder(BstNode *root);
    friend void printLevHelper(BstNode *root, std::queue<BstNode *> q);
    friend bool isBst(BstNode *root);
    friend void inOrder(BstNode *root, vector<int> &v);
    friend BstNode *remove(BstNode *root, int data);
    friend BstNode *findElem(BstNode *root, int data);
    friend BstNode *findMaxElem(BstNode *root);
    friend void printAllPaths(BstNode *root);
    friend void printPathsHelper(BstNode *root, vector<int> &path);

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

// returns pointer to the found node
BstNode *findElem(BstNode *root, int data)
{
    if (root == nullptr)
        return root;
    cout << root->data << endl;
    if (data == root->data)
        return root;

    if (data > root->data)
        return findElem(root->right, data);

    return findElem(root->left, data);
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

// returns pointer to max element
BstNode *findMaxElem(BstNode *root)
{
    if (root == nullptr)
        return nullptr;

    while (root->right != nullptr)
    {
        root = root->right;
    }

    return root;
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

void printLevHelper(BstNode *root, std::queue<BstNode *> q)
{
    if (root == nullptr)
        return;

    if (q.empty())
        q.push(root);

    // q contains addresss of bst nodes, first print the front, then if it has left and right children, push them to end of queue, then pop front as this element is done, then move to the next frontmost element of queue
    cout << q.front()->data << " ";

    if (q.front()->left != nullptr)
        q.push(q.front()->left);
    if (q.front()->right != nullptr)
        q.push(q.front()->right);

    q.pop();
    if (!q.empty())
        printLevHelper(q.front(), q);

    return;
}

void printLevelOrder(BstNode *root)
{
    std::queue<BstNode *> q{};
    printLevHelper(root, q);
}

void inOrder(BstNode *root, vector<int> &v)
{
    if (root == nullptr)
        return;

    inOrder(root->left, v);
    v.push_back(root->data);
    inOrder(root->right, v);
}

// checks if a given binary tree is BST
bool isValidBST(BstNode *root)
{
    // since inorder traversal of bst gives ascending order, store all nodes in vector
    // check if vector is sorted
    //  o(N) time complexity
    vector<int> v{};

    inOrder(root, v);
    for (int i{0}; i < v.size() - 1; i++)
    {
        if (v.at(i) > v.at(i + 1))
            return false;
    };

    return true;
}

/*
find the node with data
if node is leaf (no left or right), just delete it
if node has only one child, (left or right) then, connect its child, to its parent, and free the node
if node has both left and right children:
    find node in left subtree with max value
    copy this value to the target node
    delete the duplicate node (since its max, it will always be at extreme right, so it will have at 0 or 1 child)
    this will work as all nodes in left subtree will be lower than target, and if target is replaced by the node just smaller than it, then bst properties will still hold
same can be done with right subtree, but then we will have to find min of right subtree
 */
BstNode *remove(BstNode *root, int data)
{
    if (root == nullptr)
        return root;

    else if (data > root->data)
    {
        // deletion will take place is right subtree
        root->right = remove(root->right, data);
    }

    else if (data < root->data)
    {
        root->left = remove(root->left, data);
    }

    // otherwise we have found the node to be deleted
    else if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        root = nullptr; // only the memory at which root was pointing is freed, root still holds its address, so need to make it null
    }
    else if (root->right == nullptr)
    {
        BstNode *temp = root;
        root = root->left;
        delete temp;
    }
    else if (root->left == nullptr)
    {
        BstNode *temp = root;
        root = root->right;
        delete temp;
    }
    else
    {

        BstNode *temp = findMaxElem(root->left);
        root->data = temp->data;

        // then delete that element from left subtree
        root->left = remove(root, root->data);
    }

    return root;
}

void printPathsHelper(BstNode *root, vector<int> &path)
{
    if (root == nullptr)
        return;

    // cout << root->data << endl;

    // print vec when a leaf node is reached
    if (root->left == nullptr && root->right == nullptr)
    {
        // path.push_back(root->data);
        cout << "leaf: " << root->data << endl;
        cout << path.size() << endl;
        // for (const auto &elem : path)
        // {
        //     cout << elem << " ";
        // }
        // cout << root->data << endl;

        return;
    }

    path.push_back(root->data);

    printAllPaths(root->left);
    printAllPaths(root->right);

    path.pop_back();
    return;
}
// general function (works for simple binary tree too)
// prints all path from root to leaf
void printAllPaths(BstNode *root)
{
    vector<int> path{};

    printPathsHelper(root, path);
}

int main()
{
    // initialize an empty binary tree
    BstNode *root = nullptr;

    vector<int> vals{5, 10, 1, 7, 1, 3, 6, 11};

    /*
                5
        1       |        10
     1     3    |      7     11
                |   6
     */

    for (auto num : vals)
    {
        insert(&root, num);
    }

    // insert(&root, 1);
    // insert(&root, 2);
    // insert(&root, 3);
    // insert(&root, 4);
    // insert(&root, 5);

    // cout << boolalpha << search(root, 7) << endl; // true
    // cout << search(root, 3) << endl
    //      << endl; // false

    // cout << "Maximum number in tree: " << findMax(root) << endl; // 10

    // cout << "Minimum number in tree: " << findMin(root) << endl
    //      << endl; // 1

    // cout << "Height of tree: " << getHeight(root) << endl
    //      << endl;

    // printInorder(root);
    // cout << endl;
    // printPreorder(root);
    // cout << endl;
    // printPostorder(root);
    // cout << endl;
    // cout << endl;

    // printLevelOrder(root);

    // cout << boolalpha << "\nis bst? " << isValidBST(root) << endl;

    // remove(&root, 1);
    // remove(&root, 7;
    // root = remove(root, 6);
    // printInorder(root);

    printAllPaths(root);

    system("pause");
    return 0;
}