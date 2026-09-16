#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for simple element, 1 for tuple
    union {
        /* Possible weaknesses found:
         *  union member 'Anonymous0::value' is never used. [unusedStructMember]
         */
        int value;
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
    /* Possible weaknesses found:
     *  Variable 'list' can be declared as const array [constVariable]
     */
    Element list[] = {
        {0, .data = {5}},
        {0, .data = {8}},
        {1, .data = {.a = 1, .b = 2}},
        {0, .data = {3}}
    };
    int result = count_until_tuple(list);
    printf("%d\n", result);
    return 0;
}