#include<stdio.h>
#include<stdlib.h>
 
/* A Binary Tree node */
struct TNode
{
    int data;
    struct TNode* left;
    struct TNode* right;
};
 
struct TNode* newNode(int data);
 
/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(int arr[], int start, int end)
{
    /* Base Case */
    if (start > end)
    {
        return NULL;
    }
 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct TNode *root = newNode(arr[mid]);
 
    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);
 
    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);
 
    return root;
}
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int data)
{
    struct TNode* node = (struct TNode*)malloc(sizeof(struct TNode));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}
 
/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node)
{
    if (node == NULL)
    {
        return;
    }

    printf("%d ", node->data);

    preOrder(node->left);
    preOrder(node->right);
}

// A utility function to do inorder traversal of BST
void inorder(struct TNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct TNode * minValueNode(struct TNode* node)
{
    struct TNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
 
    return current;
}
 
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct TNode* deleteNode(struct TNode* root, int key)
{
    // base case
    if (root == NULL)
    {
        return root;
    }
 
    //first, we need to locate the target node
    if (key < root->data)
    {
        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
        root->right = deleteNode(root->right, key);
    }
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct TNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct TNode *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct TNode* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

/* returns maximum of two integers */
int max(int a, int b)
{
    return (a >= b)? a: b;
} 

/*  The function Compute the "height" of a tree. Height is the
    number of nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct TNode* node)
{
    /* base case tree is empty */
    if (node == NULL)
    {
        return 0;
    }

    /* If tree is not empty then height = 1 + max of left
    height and right heights */
    return 1 + max(height(node->left), height(node->right));
}

/* Returns true if binary tree with root as root is height-balanced */
bool isBalanced(struct TNode *root)
{
    int lh; /* for height of left subtree */
    int rh; /* for height of right subtree */ 

    /* If tree is empty then return true */
    if(root == NULL)
    {
        return true; 
    }

    /* Get the height of left and right sub trees */
    lh = height(root->left);
    rh = height(root->right);

    if (abs(lh-rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
    {
        return true;
    }

    /* If we reach here then tree is not height-balanced */
    return false;
}

/* Driver program to test above functions 
1) Get the Middle of the array and make it root.
2) Recursively do same for left half and right half.
      a) Get the middle of left half and make it left child of the root
          created in step 1.
      b) Get the middle of right half and make it right child of the
          root created in step 1.
*/
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
 
    /* Convert List to BST */
    struct TNode *root = sortedArrayToBST(arr, 0, n-1);
    printf("PreOrder Traversal of constructed BST ");
    preOrder(root);

    printf("\nDelete 3\n");
    root = deleteNode(root, 3);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    if(isBalanced(root))
      printf("Tree is balanced\n");
    else
      printf("Tree is not balanced\n");

    printf("\nDelete 2\n");
    root = deleteNode(root, 2);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    if(isBalanced(root))
      printf("Tree is balanced\n");
    else
      printf("Tree is not balanced\n");
    
    printf("\nDelete 1\n");
    root = deleteNode(root, 1);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    if(isBalanced(root))
      printf("Tree is balanced\n");
    else
      printf("Tree is not balanced\n");  
 
    return 0;
}