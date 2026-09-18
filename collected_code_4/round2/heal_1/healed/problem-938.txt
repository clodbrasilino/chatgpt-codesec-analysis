#include <stdio.h>
#include <limits.h>

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int min(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}

void findClosest(int ar1[], int ar2[], int ar3[], int n1, int n2, int n3)
{
    int diff = INT_MAX;
    int res_i = 0, res_j = 0, res_k = 0;

    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2 && k < n3)
    {
        int minimum = min(ar1[i], min(ar2[j], ar3[k]));
        int maximum = max(ar1[i], max(ar2[j], ar3[k]));

        if (maximum - minimum < diff)
        {
            res_i = i;
            res_j = j;
            res_k = k;
            diff = maximum - minimum;
        }

        if (diff == 0) break;
        
        if (ar1[i] == minimum) i++;
        else if (ar2[j] == minimum) j++;
        else k++;
    }

    printf("%d, %d, %d", ar1[res_i], ar2[res_j], ar3[res_k]);
}

int main()
{
    int ar1[] = {5, 20, 30};
    int ar2[] = {10, 15, 25};
    int ar3[] = {1, 5, 20, 30};
    
    int n1 = sizeof(ar1) / sizeof(ar1[0]);
    int n2 = sizeof(ar2) / sizeof(ar2[0]);
    int n3 = sizeof(ar3) / sizeof(ar3[0]);

    findClosest(ar1, ar2, ar3, n1, n2, n3);
    
    return 0;
}