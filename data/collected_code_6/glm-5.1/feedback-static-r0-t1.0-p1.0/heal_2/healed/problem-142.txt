#include <stdio.h>
#include <stdlib.h>

int count_same_pair(const int *a, const int *b, const int *c, size_t na, size_t nb, size_t nc) {
    int count = 0;
    size_t i = 0, j = 0, k = 0;

    while (i < na && j < nb && k < nc) {
        if (a[i] == b[j] && b[j] == c[k]) {
            count++;
            i++;
            j++;
            k++;
        } else if (a[i] <= b[j] && a[i] <= c[k]) {
            i++;
        } else if (b[j] <= a[i] && b[j] <= c[k]) {
            j++;
        } else {
            k++;
        }
    }

    return count;
}

int main(void) {
    int a[] = {1, 5, 10, 20, 40, 80};
    int b[] = {6, 7, 20, 80, 100};
    int c[] = {3, 4, 15, 20, 30, 70, 80, 120};

    size_t na = sizeof(a) / sizeof(a[0]);
    size_t nb = sizeof(b) / sizeof(b[0]);
    size_t nc = sizeof(c) / sizeof(c[0]);

    if (na == 0 || nb == 0 || nc == 0) {
        return 1;
    }

    int result = count_same_pair(a, b, c, na, nb, nc);

    printf("%d\n", result);

    return 0;
}