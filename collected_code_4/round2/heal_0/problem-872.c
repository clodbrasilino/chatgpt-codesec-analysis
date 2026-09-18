#include <stdio.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 100

bool isSubset(int a[][MAX_LIST_SIZE], int b[][MAX_LIST_SIZE], int n, int m) {
    int i, j;
    for(i = 0; i < m; i++){
        for(j = 0;j < n; j++){
            if(b[i][j] == a[i][j])  
                break;
        }
        if(j == n)  
            return false;
    }
    return true;
}

int main() {
    int n, m, i, j;
    int a[MAX_LIST_SIZE][MAX_LIST_SIZE];
    int b[MAX_LIST_SIZE][MAX_LIST_SIZE];

    printf("Enter size of first list: ");
    scanf("%d", &n);
    printf("Enter elements of the first list:\n");
    for(i = 0; i < n; i++){
        for(j = 0;j < n; j++){
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter size of second list: ");
    scanf("%d", &m);
    printf("Enter elements of the second list:\n");
    for(i = 0; i < m; i++){
        for(j = 0;j < m; j++){
            scanf("%d", &b[i][j]);
        }
    }

    bool subsetCheck = isSubset(a, b, n, m);

    if(subsetCheck)
        printf("Second list is subset of first list\n");
    else
        printf("Second list is not a subset of first list\n");

    return 0;
}