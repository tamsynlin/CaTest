#include <bits/stdc++.h>
using namespace std;

bool checknode()
{
    ;
}

int longpath(int *mat, int row, int column, int *path, int index)
{
    int longfromthis = 0;

    //left
    if (index%column != 0)
    {
        if (mat[index-1] == mat[index]+1)
        {
            if (-1 == path[index-1])
            {
                path[index-1] = longpath(mat, row, column, path, index-1);
            }

            longfromthis = 1+path[index-1];
        }
    }

    //right
    if (index%column != (column-1))
    {
        if (mat[index+1] == mat[index]+1)
        {
            if (-1 == path[index+1])
            {
                path[index+1] = longpath(mat, row, column, path, index+1);
            }

            longfromthis = longfromthis<(1+path[index+1])?(1+path[index+1]):longfromthis;
        }
    }

    //up
    if (index>=column)
    {
        if (mat[index-column] == mat[index]+1)
        {
            if (-1 == path[index-column])
            {
                path[index-column] = longpath(mat, row, column, path, index-column);
            }

            longfromthis = longfromthis<(1+path[index-column])?(1+path[index-column]):longfromthis;
        }
    }

    //down
    if (index<=(row*(column-1)))
    {
        if (mat[index+column] == mat[index]+1)
        {
            if (-1 == path[index+column])
            {
                path[index+column] = longpath(mat, row, column, path, index+column);
            }

            longfromthis = longfromthis<(1+path[index+column])?(1+path[index+column]):longfromthis;
        }
    }

    return longfromthis;
}

/*
Time complexity of the above solution is O(n2). 
It may seem more at first look. If we take a closer look, 
we can notice that all values of dp[i][j] are computed only once.
*/
int finLongestOverAll(int *mat, int row, int column)
{
    int longest = 0;
    int *path = new int[row*column];
    memset(path, -1, sizeof(int)*row*column);

    for (int r=0; r<row; r++)
    {
        for (int c=0; c< column; c++)
        {
            if (-1 == path[r*column+c])
            {
                path[r*column+c] = longpath(mat, row, column, path, r*column+c);
            }
            
            if (longest < path[r*column+c])
            {
                longest = path[r*column+c];
            }
        }
    }

    return longest;
}

int main()
{
    int n = 3;
    int mat[3][3] = {
                    {1, 2, 9},
                    {5, 3, 8},
                    {4, 6, 7}
                    };
    cout << "Length of the longest path is "
        << finLongestOverAll((int *)mat, n, n)
        << endl;
    
    return 0;
}