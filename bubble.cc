// CPP code for bubble sort
// using template function
#include <iostream>
using namespace std;

//Templates are expanded at compiler time. This is like macros. The difference is, compiler does type checking before template expansion.
template <class T>
// A function to implement bubble sort
void bubbleSort(T a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; i < j; j--)
            if (a[j] < a[j - 1])
  
        // calls template function
        swap(a[j], a[j - 1]);
}
  
template <class X>
  
// A Function to perform swapping
void swap(X &a, X &b) {
    X temp = a;
    a = b;
    b = temp;
}

#include <iostream>
using namespace std;
 
template <typename T = int>
class Array {
private:
    T *ptr;
    int size;
public:
    Array(T arr[], int s);
    void print();
};
 
template <typename T>
Array<T>::Array(T arr[], int s) {
    ptr = new T[s];
    size = s;
    for(int i = 0; i < size; i++)
        ptr[i] = arr[i];
}
 
template <typename T>
void Array<T>::print() {
    for (int i = 0; i < size; i++)
        cout<<" "<<*(ptr + i);
    cout<<endl;
}

template <class T, int max>
int arrMin(T arr[], int n)
{
   int m = max;
   for (int i = 0; i < n; i++)
      if (arr[i] < m)
         m = arr[i];
  
   return m;
}
  
// Driver Code
int main() {
    int a[5] = {10, 50, 30, 40, 20};
    int n = sizeof(a) / sizeof(a[0]);
  
    // calls template function 
    bubbleSort<int>(a, 5);
  
    cout << " Sorted array : ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    Array<int> arr(a, n);
    Array<> arr_default(a, n);
    arr_default.print();

    int arr1[]  = {10, 20, 15, 12};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);

    char arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

    // Second template parameter to arrMin must be a constant
    cout << arrMin<int, 10000>(arr1, n1) << endl;
    cout << arrMin<char, 256>(arr2, n2);
    cout<<endl;
  
    return 0;
}
