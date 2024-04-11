#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int type; // 0 for int, 1 for string
    union {
        int i;
        char s[50];
    } data;
} Element;

int compare(const void *a, const void *b) {
    Element *elementA = (Element *)a;
    Element *elementB = (Element *)b;

    if (elementA->type != elementB->type) {
        return elementA->type - elementB->type;
    } else if (elementA->type == 0) {
        return elementA->data.i - elementB->data.i;
    } else {
        return strcmp(elementA->data.s, elementB->data.s);
    }
}

void sortMixedList(Element *list, size_t size) {
    qsort(list, size, sizeof(Element), compare);
}

int main() {
    Element list[6] = {
        {0, .data.i = 5},
        {1, .data.s = "hello"},
        {0, .data.i = 3},
        {1, .data.s = "world"},
        {0, .data.i = 1},
        {1, .data.s = "c"}
    };

    sortMixedList(list, 6);

    for (int i = 0; i < 6; i++) {
        if (list[i].type == 0) {
            printf("%d\n", list[i].data.i);
        } else {
            printf("%s\n", list[i].data.s);
        }
    }

    return 0;
}