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

int main() {
    size_t n = 5;
    Sublist *list = (Sublist *)malloc(n * sizeof(Sublist));
    if (list == NULL) {
        return 1;
    }

    list[0].first = 1; list[0].second = 9;
    list[1].first = 2; list[1].second = 5;
    list[2].first = 3; list[2].second = 7;
    list[3].first = 4; list[3].second = 1;
    list[4].first = 5; list[4].second = 3;

    sort_by_second(list, n);

    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d)\n", list[i].first, list[i].second);
    }

    free(list);
    list = NULL;

    return 0;
}