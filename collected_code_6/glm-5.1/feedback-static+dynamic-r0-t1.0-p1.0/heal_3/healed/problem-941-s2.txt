#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define TYPE_INT 0
#define TYPE_TUPLE 1

typedef struct {
    int data;
} Tuple;

typedef union {
    int type;
    Tuple tuple;
} Element;

size_t count_until_tuple(Element *list, size_t size) {
    size_t count = 0;
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (list[i].type == TYPE_TUPLE) {
            return count;
        }
        count++;
    }
    return count;
}

int main(void) {
    Element list[] = {
        {TYPE_INT},
        {TYPE_INT},
        {TYPE_TUPLE},
        {TYPE_INT}
    };
    Tuple t = {42};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t result = count_until_tuple(list, size);
    printf("%zu\n", result);
    printf("%d\n", t.data);
    return 0;
}