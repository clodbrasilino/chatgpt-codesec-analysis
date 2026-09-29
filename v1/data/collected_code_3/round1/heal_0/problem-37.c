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

int main() {
    Element arr[] = {
        {0, .data.i = 5},
        {1, .data.s = "hello"},
        {0, .data.i = 3},
        {1, .data.s = "world"},
        {0, .data.i = 1},
        {1, .data.s = "c"},
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(Element), compare);

    for (int i = 0; i < n; i++) {
        if (arr[i].type == 0) {
            printf("%d ", arr[i].data.i);
        } else {
            printf("%s ", arr[i].data.s);
        }
    }

    return 0;
}