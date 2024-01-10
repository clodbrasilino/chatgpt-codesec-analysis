#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b);
void lcs(const char *X, const char *Y, size_t m, size_t n);

int max(int a, int b) 
{
    return (a > b) ? a : b; 
}

void lcs(const char *X, const char *Y, size_t m, size_t n) 
{
    int **L = (int**)malloc((m + 1) * sizeof(int *));
    
    if(L == NULL)
    {
        return;
    }

    for (size_t i = 0; i <= m; i++)
    {
        L[i] = (int*)calloc(n + 1, sizeof(int));

        if(L[i] == NULL)
        {
            for(size_t j = 0; j < i; j++)
                free(L[j]);
            
            free(L);
            return;
        }
    }

    for (size_t i = 0; i <= m; i++) 
    {
        for (size_t j = 0; j <= n; j++) 
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    size_t index = L[m][n];
    char *lcs = (char*)calloc(index + 1, sizeof(char));

    if(lcs == NULL)
    {
        for(size_t i = 0; i <= m; i++)
            free(L[i]);
        
        free(L);
        return;
    }

    size_t i = m;
    size_t j = n;
    while (i > 0 && j > 0) 
    {
        if (X[i - 1] == Y[j - 1]) 
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    printf("Longest Common Subsequence: %s", lcs);
    free(lcs);

    for (i = 0; i <= m; i++)
        free(L[i]);

    free(L);
}

int main()
{
    const char X[] = "AGGTAB";
    const char Y[] = "GXTXAYB";
    lcs(X, Y, strlen(X), strlen(Y));

    return 0;
}