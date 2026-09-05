#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Sublist;

int compare(const void *a, const void *b) {
    const Sublist *sa = (const Sublist *)a;
    const Sublist *sb = (const Sublist *)b;
    return (sa->second > sb->second) - (sa->second < sb->second);
}

void sort_by_second(Sublist *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }
    qsort(list, size, sizeof(Sublist), compare);
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t size = (size_t)atoi(argv[1]);
    if (size == 0) {
        return 0;
    }

    Sublist *list = (Sublist *)malloc(size * sizeof(Sublist));
    if (list == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        list[i].first = (int)i;
        list[i].second = (int)(size - i);
    }

    sort_by_second(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d %d\n", list[i].first, list[i].second);
    }

    free(list);
    list = NULL;

    return 0;
}