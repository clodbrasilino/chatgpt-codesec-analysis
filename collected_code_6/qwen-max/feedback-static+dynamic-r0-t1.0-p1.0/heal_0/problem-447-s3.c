#include <stdio.h>
#include <stdlib.h>

void find_cubes(int *list, int n) {
    for (int i = 0; i < n; i++) {
        list[i] = list[i] * list[i] * list[i];
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        fprintf(stderr, "Number of elements must be positive.\n");
        return 1;
    }

    int *list = (int *)malloc(n * sizeof(int));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }

    find_cubes(list, n);

    printf("Cubes of the elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}