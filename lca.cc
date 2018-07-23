// A recursive C program to find LCA of two nodes n1 and n2.
#include <stdio.h>
#include <stdlib.h>
 
struct node
{
    int data;
    struct node* left, *right;
};
 
/* Function to find LCA of n1 and n2. The function assumes that both
   n1 and n2 are present in BST */
struct node *lca(struct node* root, int n1, int n2)
{
    if (root == NULL) return NULL;
 
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);
 
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);
 
    return root;
}
 
/* Helper function that allocates a new node with the given data.*/
struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data  = data;
    node->left  = node->right = NULL;
    return(node);
}

int maxbetweennodes(struct node* root, int n1, int n2)
{
    struct node* lca_node = lca(root, n1, n2);
    int bigger = n1 > n2 ? n1: n2;
    int max_value = lca_node->data;

    while (lca_node->data < bigger)
    {
        max_value = lca_node->data;
        lca_node = lca_node->right;
    }

    printf("LCA of %d and %d is %d \n", n1, n2, max_value);
    return max_value;
}

/* Driver program to test lca() 
The idea is to find Lowest Common Ancestor of node ‘a’ and node ‘b’. 
Then search maximum node between LCA and ‘a’, also find maximum node 
between LCA and ‘b’. Answer will be maximum node of two.
*/
int main()
{
    // Let us construct the BST shown in the above figure
    struct node *root        = newNode(20);
    root->left               = newNode(8);
    root->right              = newNode(22);
    root->left->left         = newNode(4);
    root->left->right        = newNode(12);
    root->left->right->left  = newNode(10);
    root->left->right->right = newNode(14);
 
    int n1 = 10, n2 = 14;
    maxbetweennodes(root, n1, n2);
 
    n1 = 14, n2 = 4;
    maxbetweennodes(root, n1, n2);
 
    n1 = 10, n2 = 22;
    maxbetweennodes(root, n1, n2);
 
    return 0;
}
