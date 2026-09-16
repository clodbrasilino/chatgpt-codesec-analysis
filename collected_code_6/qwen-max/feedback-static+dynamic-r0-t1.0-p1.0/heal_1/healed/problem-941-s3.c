#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_tuple;
} Element;

int count_until_tuple(Element *list, int length) {
    for (int i = 0; i < length; ++i) {
        if (list[i].is_tuple) {
            return i;
        }
    }
    return length;
}

int main() {
    Element list[] = {{0}, {0}, {1}, {0}};
    int length = sizeof(list) / sizeof(list[0]);
    int result = count_until_tuple(list, length);
    printf("Count until tuple: %d\n", result);
    return 0;
}