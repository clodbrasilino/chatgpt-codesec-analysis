#include <stdio.h>
#include <stdlib.h>

void rotate_list(int *list, int n, int k) {
    if (n <= 1 || k % n == 0) return;
    k = k % n;
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        temp[(i + k) % n] = list[i];
    }
    for (int i = 0; i < n; i++) {
        list[i] = temp[i];
    }
    free(temp);
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int n = sizeof(list) / sizeof(list[0]);
    int k = 2;
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    rotate_list(list, n, k);
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    return 0;
}