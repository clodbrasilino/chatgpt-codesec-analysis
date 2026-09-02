#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Sublist;

int compare(const void *a, const void *b) {
    const Sublist *ia = (const Sublist *)a;
    const Sublist *ib = (const Sublist *)b;
    return ia->b - ib->b;
}

int main() {
    Sublist list[] = {{1, 3}, {4, 1}, {2, 2}};
    size_t n = sizeof(list) / sizeof(list[0]);

    qsort(list, n, sizeof(Sublist), compare);

    for (size_t i = 0; i < n; ++i) {
        printf("(%d, %d) ", list[i].a, list[i].b);
    }
    printf("\n");

    return 0;
}