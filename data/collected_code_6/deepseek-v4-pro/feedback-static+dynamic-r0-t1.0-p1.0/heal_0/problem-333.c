#include <stdio.h>
#include <stdlib.h>

struct sublist {
    int first;
    int second;
};

int compare_sublists(const void *a, const void *b) {
    const struct sublist *sa = (const struct sublist *)a;
    const struct sublist *sb = (const struct sublist *)b;
    if (sa->second < sb->second) return -1;
    if (sa->second > sb->second) return 1;
    return 0;
}

void sort_by_second(struct sublist *list, size_t n) {
    if (list == NULL || n == 0) return;
    qsort(list, n, sizeof(struct sublist), compare_sublists);
}

int main(void) {
    struct sublist list[] = {
        {1, 5},
        {2, 3},
        {3, 9},
        {4, 1},
        {5, 7}
    };
    size_t n = sizeof(list) / sizeof(list[0]);

    sort_by_second(list, n);

    for (size_t i = 0; i < n; ++i) {
        printf("(%d, %d)\n", list[i].first, list[i].second);
    }

    return 0;
}