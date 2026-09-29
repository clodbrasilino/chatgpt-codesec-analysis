#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} SubList;

int compare(const void *a, const void *b) {
    SubList *subListA = (SubList *)a;
    SubList *subListB = (SubList *)b;
    return subListA->second - subListB->second;
}

void sortList(SubList *list, int size) {
    qsort(list, size, sizeof(SubList), compare);
}

int main() {
    SubList list[] = {{1, 20}, {2, 10}, {3, 30}, {4, 40}};
    int size = sizeof(list) / sizeof(SubList);

    sortList(list, size);

    for(int i = 0; i < size; i++) {
        printf("%d %d\n", list[i].first, list[i].second);
    }

    return 0;
}