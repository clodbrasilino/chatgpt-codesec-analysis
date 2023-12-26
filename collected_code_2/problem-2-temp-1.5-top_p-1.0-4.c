#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 20

void getCommon(int a[], int b[], int n, int m) {
    int i, j;

    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
        {
           if (a[i] == b[j]) 
           {
              printf("%d ", a[i]); 
           }
        }
    }
}

int main()
{
    int a[MAX_SIZE] = {1, 2, 3, 4, 5};
    int b[MAX_SIZE] = {2, 4, 6, 8, 10};

    int n = sizeof(a)/sizeof(a[0]);
    int m = sizeof(b)/sizeof(b[0]);

    getCommon(a, b, n, m);
    
    printf("\n");
    
    return 0;
}
