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

    delete path;

    return longest;
}

int min(int x, int y, int z);

int minCost(int cost[3][3], int m, int n)
{
     int i, j;

     // Instead of following line, we can use int tc[m+1][n+1] or
     // dynamically allocate memoery to save space. The following line is
     // used to keep te program simple and make it working on all compilers.
     int tc[3][3];

     tc[0][0] = cost[0][0];

     /* Initialize first column of total cost(tc) array */
     for (i = 1; i <= m; i++)
        tc[i][0] = tc[i-1][0] + cost[i][0];

     /* Initialize first row of tc array */
     for (j = 1; j <= n; j++)
        tc[0][j] = tc[0][j-1] + cost[0][j];

     /* Construct rest of the tc array */
     for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            tc[i][j] = min(tc[i-1][j-1],
                           tc[i-1][j],
                           tc[i][j-1]) + cost[i][j];

     return tc[m][n];
}

/* A utility function that returns minimum of 3 integers */
int min(int x, int y, int z)
{
   if (x < y)
      return (x < z)? x : z;
   else
      return (y < z)? y : z;
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
    
    printf("\n\n %d ", minCost(mat, 2, 2));

    return 0;
}
