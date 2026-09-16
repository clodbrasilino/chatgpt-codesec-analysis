#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Sublist;

int compare(const void *a, const void *b) {
    const Sublist *sa = (const Sublist *)a;
    const Sublist *sb = (const Sublist *)b;
    if (sa->second < sb->second) return -1;
    if (sa->second > sb->second) return 1;
    return 0;
}

void sort_by_second(Sublist *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }
    qsort(list, size, sizeof(Sublist), compare);
}

int main(void) {
    Sublist list[] = {{1, 5}, {2, 2}, {3, 8}, {4, 1}};
    size_t size = sizeof(list) / sizeof(list[0]);

    sort_by_second(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d)\n", list[i].first, list[i].second);
    }

    return 0;
}