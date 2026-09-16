#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Sublist;

int compare_sublists(const void *a, const void *b) {
    const Sublist *sub_a = (const Sublist *)a;
    const Sublist *sub_b = (const Sublist *)b;
    
    if (sub_a->second < sub_b->second) {
        return -1;
    }
    if (sub_a->second > sub_b->second) {
        return 1;
    }
    return 0;
}

void sort_by_second(Sublist *list, size_t count) {
    if (list == NULL || count == 0) {
        return;
    }
    qsort(list, count, sizeof(Sublist), compare_sublists);
}

int main(void) {
    Sublist list[] = {
        {1, 5},
        {2, 3},
        {3, 8},
        {4, 1},
        {5, 9}
    };
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t i;

    printf("Original list:\n");
    for (i = 0; i < count; i++) {
        printf("{%d, %d} ", list[i].first, list[i].second);
    }
    printf("\n");

    sort_by_second(list, count);

    printf("Sorted by second element:\n");
    for (i = 0; i < count; i++) {
        printf("{%d, %d} ", list[i].first, list[i].second);
    }
    printf("\n");

    return EXIT_SUCCESS;
}