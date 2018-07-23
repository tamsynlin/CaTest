// C++ program to create a Complete Binary tree from its Linked List
// Representation
#include <iostream>
#include <string>
#include <queue>
using namespace std;
 
// Linked list node
struct ListNode
{
    int data;
    ListNode* next;
};
 
// Binary tree node structure
struct BinaryTreeNode
{
    int data;
    BinaryTreeNode *left, *right;
};
 
// Function to insert a node at the beginning of the Linked List
void push(struct ListNode** head_ref, int new_data)
{
    // allocate node and assign data
    struct ListNode* new_node = new ListNode;
    new_node->data = new_data;
 
    // link the old list off the new node
    new_node->next = (*head_ref);
 
    // move the head to point to the new node
    (*head_ref) = new_node;
}
 
// method to create a new binary tree node from the given data
BinaryTreeNode* newBinaryTreeNode(int data)
{
    BinaryTreeNode *temp = new BinaryTreeNode;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

BinaryTreeNode* convertList2Tree(std::vector<int> *array, int index, BinaryTreeNode* &root)
{
    // Base Case
    if (index >= array->size())
    {
        root = NULL; // Note that root is passed by reference
    }
    else
    {
        root  = newBinaryTreeNode(array->at(index));

        root->left = convertList2Tree(array, 2*index+1, root->left);
        root->right = convertList2Tree(array, 2*index+2, root->right);
    }

    return root;
}
 
// converts a given linked list representing a complete binary tree into the
// linked representation of binary tree.
void convertList2Binary(ListNode *head, BinaryTreeNode* &root)
{
    // queue to store the parent nodes
    queue<BinaryTreeNode *> q;
 
    // Base Case
    if (head == NULL)
    {
        root = NULL; // Note that root is passed by reference
        return;
    }
 
    // 1.) The first node is always the root node, and add it to the queue
    root = newBinaryTreeNode(head->data);
    q.push(root);
 
    // advance the pointer to the next node
    head = head->next;
 
    // until the end of linked list is reached, do the following steps
    while (head)
    {
        // 2.a) take the parent node from the q and remove it from q
        BinaryTreeNode* parent = q.front();
        q.pop();
 
        // 2.c) take next two nodes from the linked list. We will add
        // them as children of the current parent node in step 2.b. Push them
        // into the queue so that they will be parents to the future nodes
        BinaryTreeNode *leftChild = NULL, *rightChild = NULL;
        leftChild = newBinaryTreeNode(head->data);
        q.push(leftChild);
        head = head->next;
        if (head)
        {
            rightChild = newBinaryTreeNode(head->data);
            q.push(rightChild);
            head = head->next;
        }
 
        // 2.b) assign the left and right children of parent
        parent->left = leftChild;
        parent->right = rightChild;
    }
}
 
// Utility function to traverse the binary tree after conversion
void inorderTraversal(BinaryTreeNode* root)
{
    if (root)
    {
        inorderTraversal( root->left );
        cout << root->data << " ";
        inorderTraversal( root->right );
    }
}
 
// Driver program to test above functions
int main()
{
    // create a linked list shown in above diagram
    struct ListNode* head = NULL;
    push(&head, 36);  /* Last node of Linked List */
    push(&head, 30);
    push(&head, 25);
    push(&head, 15);
    push(&head, 12);
    push(&head, 10); /* First node of Linked List */
 
    BinaryTreeNode *root, *root2;
    convertList2Binary(head, root);

    std::vector<int> myvector (10);   // 10 zero-initialized ints

    // assign some values:
    for (unsigned i=0; i<myvector.size(); i++)
        myvector.at(i)=i;

    convertList2Tree(&myvector, 0, root2);
 
    cout << "Inorder Traversal of the constructed Binary Tree is: \n";
    inorderTraversal(root);
    cout << "\n\n";

    cout << "Inorder Traversal of the constructed Binary Tree is: \n";
    inorderTraversal(root2);
    cout << "\n\n";

    return 0;
}