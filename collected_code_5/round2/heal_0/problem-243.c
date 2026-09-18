#include <stdio.h>
#include <stdlib.h>

typedef struct Pair {
    int key;
    int value;
} Pair;

int compare(const void* a, const void* b)
{
    return ((Pair*)a)->key - ((Pair*)b)->key;
}

void sort_pairs(Pair* pairs, size_t size)
{
    if (pairs == NULL) {
        printf("Error: NULL pointer passed to function.\n");
        return;
    }

    qsort(pairs, size, sizeof(Pair), compare);
}

int main()
{
    Pair pairs[] = {{2, 20}, {1, 10}, {3, 30}};
    size_t size = sizeof(pairs) / sizeof(Pair);

    sort_pairs(pairs, size);

    for (size_t i = 0; i < size; ++i) {
        printf("{%d, %d}\n", pairs[i].key, pairs[i].value);
    }

    return 0;
}