#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Element;

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'elemA' can be declared as pointer to const [constVariablePointer]
     */
    Element *elemA = (Element *)a;
    /* Possible weaknesses found:
     *  Variable 'elemB' can be declared as pointer to const [constVariablePointer]
     */
    Element *elemB = (Element *)b;
    return (elemA->second - elemB->second);
}

void sortList(Element *list, size_t length) {
    qsort(list, length, sizeof(Element), compare);
}

int main() {
    Element list[] = {{3, 5}, {1, 2}, {4, 4}, {2, 3}};
    size_t length = sizeof(list) / sizeof(list[0]);

    sortList(list, length);

    for (size_t i = 0; i < length; ++i) {
        printf("(%d, %d) ", list[i].first, list[i].second);
    }
    printf("\n");

    return 0;
}