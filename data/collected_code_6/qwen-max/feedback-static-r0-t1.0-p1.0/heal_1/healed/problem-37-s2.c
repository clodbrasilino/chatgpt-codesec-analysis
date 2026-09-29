#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { INT, STRING } Type;

typedef struct {
    Type type;
    union {
        int i;
        char* s;
    };
} Element;

int compare(const void* a, const void* b) {
    const Element *el1 = (const Element*)a;
    const Element *el2 = (const Element*)b;

    if (el1->type == INT && el2->type == INT) {
        return (el1->i - el2->i);
    } else if (el1->type == STRING && el2->type == STRING) {
        return strcmp(el1->s, el2->s);
    } else if (el1->type == INT) {
        return -1;
    } else {
        return 1;
    }
}

void free_elements(Element* elements, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (elements[i].type == STRING) {
            free(elements[i].s);
        }
    }
    free(elements);
}

int main() {
    Element elements[] = {
        {INT, .i = 3},
        {STRING, .s = "apple"},
        {INT, .i = 1},
        {STRING, .s = "banana"},
        {STRING, .s = "cherry"},
        {INT, .i = 2}
    };
    size_t count = sizeof(elements) / sizeof(elements[0]);

    qsort(elements, count, sizeof(Element), compare);

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].type == INT) {
            printf("%d\n", elements[i].i);
        } else {
            printf("%s\n", elements[i].s);
        }
    }

    free_elements(elements, count);
    return 0;
}