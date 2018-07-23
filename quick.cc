#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<climits>
using namespace std;

void quickSort(int arr[], int left, int right)
{
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j) 
      {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;

            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

void quickSortL(int arr[], int left, int right)
{
    int i = left+1, j = right;
    int tmp;
    int pivot = arr[left];

    /* partition */
    while (i <= j) 
    {
        while (arr[i] < pivot)
        {
            i++;
            if (i > j)
            {
                break;
            }
        }

        while (arr[j] > pivot)
        {
            if (i > j)
            {
                break;
            }
            j--;
        }

        if (i <= j)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (left != j)
    {
        tmp = arr[left];
        arr[left] = arr[j];
        arr[j] = tmp;
    }

    /* recursion */
    if (left < j)
        quickSortL(arr, left, j);
    if (i < right)
        quickSortL(arr, i, right);
}

int partition(int arr[], int left, int right)
{
    int i = left, j = right-1;
    int tmp;
    int pivot = arr[right];

    /* partition */
    while (i <= j) 
    {
        while (arr[i] < pivot)
        {
            i++;
            if (i > j)
            {
                break;
            }
        }

        while (arr[j] > pivot)
        {
            if (i > j)
            {
                break;
            }
            j--;
        }

        if (i <= j)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (right != i)
    {
        tmp = arr[right];
        arr[right] = arr[i];
        arr[i] = tmp;
    }

    return i;
}

// This function returns k'th smallest element in arr[l..r] using
// QuickSort based method.  ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        // Partition the array around last element and get
        // position of pivot element in sorted array
        int pos = partition(arr, l, r);
 
        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left subarray
            return kthSmallest(arr, l, pos-1, k);
 
        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
 
    // If k is more than number of elements in array
    return INT_MAX;
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
// Driver program to test above functions
int main()
{
    int arr[] = {1, 5, 10, 11, 4, 7, 3, 6};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "K'th smallest element is " << kthSmallest(arr, 0, n-1, 6) << "\n";

    printf("Original array: \n");
    printArray(arr, n);

    quickSortL(arr, 0, n-1);

    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
