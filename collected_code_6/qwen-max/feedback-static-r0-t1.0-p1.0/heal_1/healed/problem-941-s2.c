#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for simple element, 1 for tuple
    union {
        struct { int a, b; };
    } data;
} Element;

int count_until_tuple(const Element *list) {
    int count = 0;
    while (list && list->type == 0) {
        count++;
        list++;
    }
    return count;
}

int main() {
    const Element list[] = {
        {0, .data = {.a = 5, .b = 0}},
        {0, .data = {.a = 8, .b = 0}},
        {1, .data = {.a = 1, .b = 2}},
        {0, .data = {.a = 3, .b = 0}}
    };
    int result = count_until_tuple(list);
    printf("%d\n", result);
    return 0;
}