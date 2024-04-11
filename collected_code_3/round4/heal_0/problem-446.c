#include <stdio.h>

#define MAX 100

void countOccurrence(int list[], int tuple[], int n, int m) {
    int i, j, count;
    for(i = 0; i < n; i++) {
        count = 0;
        for(j = 0; j < m; j++) {
            if(list[i] == tuple[j]) {
                count++;
            }
        }
        printf("Element %d occurs %d times\n", list[i], count);
    }
}

int main() {
    int list[MAX], tuple[MAX], n, m, i;
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);
    printf("Enter the elements of the list: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    printf("Enter the number of elements in the tuple: ");
    scanf("%d", &m);
    printf("Enter the elements of the tuple: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &tuple[i]);
    }
    countOccurrence(list, tuple, n, m);
    return 0;
}