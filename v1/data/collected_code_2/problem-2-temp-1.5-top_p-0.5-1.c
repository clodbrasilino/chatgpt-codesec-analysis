#include <stdio.h>

#define MAX_SIZE 100

void find_similar(int a[], int n, int b[], int m) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(a[i] == b[j]) {
                printf("%d ", a[i]);
                break;
            }
        }
    }
}

int main() {
    int a[MAX_SIZE], b[MAX_SIZE];
    int n, m, i;

    printf("Enter size of first array : ");
    scanf("%d", &n);
    printf("Enter elements in first array : ");
    for(i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter size of second array : ");
    scanf("%d", &m);
    printf("Enter elements in second array : ");
    for(i=0; i<m; i++) {
        scanf("%d", &b[i]);
    }

    printf("Similar elements in both arrays : ");
    find_similar(a, n, b, m);

    return 0;
}