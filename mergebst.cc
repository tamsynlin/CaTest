/*
Method 2 (Merge Inorder Traversals) 
1) Do inorder traversal of first tree and store the traversal in one temp array arr1[]. This step takes O(m) time.
2) Do inorder traversal of second tree and store the traversal in another temp array arr2[]. This step takes O(n) time.
3) The arrays created in step 1 and 2 are sorted arrays. Merge the two sorted arrays into one array of size m + n. This step takes O(m+n) time.
4) Construct a balanced tree from the merged array using the technique discussed in this post. This step takes O(m+n) time.
*/
#include <stdio.h>
#include <stdlib.h>

/* A Binary Tree node */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}

void inorder(struct node* root, int *arr, int *index)
{
    if (root->left != NULL)
    {
        inorder(root->left, arr, index);
    }

    arr[*index] = root->data;
    (*index)++;

    if (root->right != NULL)
    {
        inorder(root->right, arr, index);
    }
}

int* Tree2Array(struct node* root, int length)
{
    int index = 0;
    int *array = new int[length];

    inorder(root, array, &index);
    
    return array;
}

int* MergeArray(int* arr1, int length1, int *arr2, int length2)
{
    int *array = new int[length1 + length2];

    int new_index=0, index1=0, index2=0;
    int compare_length = length1 > length2 ? length2 : length1;

    while (index1 < length1 && index2 < length2)
    {
        if (arr1[index1] > arr2[index2])
        {
            array[new_index] = arr2[index2];
            index2++;
        }
        else
        {
            array[new_index] = arr1[index1];
            index1++;
        }
        
        new_index++;
    }

    while (index1 < length1)
    {
        array[new_index] = arr1[index1];
        index1++;
        
        new_index++;
    }

    while (index2 < length2)
    {
        array[new_index] = arr2[index2];
        index2++;
        
        new_index++;
    }
    
    return array;
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct node* sortedArrayToBST(int arr[], int start, int end)
{
    /* Base Case */
    if (start > end)
    {
        return NULL;
    }
 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct node *root = newNode(arr[mid]);
 
    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);
 
    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);
 
    return root;
}

void preOrder(struct node* node)
{
    if (node == NULL)
    {
        return;
    }

    printf("%d ", node->data);

    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(struct node* node)
{
    if (node == NULL)
    {
        return;
    }

    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

int main()
{
    /* Create following tree as first balanced BST
           100
          /  \
        50    300
       / \
      20  70
    */
    struct node *root1  = newNode(100);
    root1->left         = newNode(50);
    root1->right        = newNode(300);
    root1->left->left   = newNode(20);
    root1->left->right  = newNode(70);

    int *tree1 = Tree2Array(root1, 5);
 
    /* Create following tree as second balanced BST
            80
           /  \
         40   120
    */
    struct node *root2  = newNode(80);
    root2->left         = newNode(40);
    root2->right        = newNode(120);

    int *tree2 = Tree2Array(root2, 3);

    int *newtree = MergeArray(tree1, 5, tree2, 3);

    delete []tree1;
    delete []tree2;

    for (int i=0; i<8; i++)
    {
        printf("node: %d\n", newtree[i]);
    }

    struct node *root = sortedArrayToBST(newtree, 0, 7);
    inOrder(root);
    printf("\n\n");
    preOrder(root);

    delete []newtree;
}
