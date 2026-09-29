#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_tuple;
    /* Possible weaknesses found:
     *  struct member 'Element::data' is never used. [unusedStructMember]
     */
    void *data;
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
    Element list[] = {{0, NULL}, {0, NULL}, {1, NULL}, {0, NULL}};
    int length = sizeof(list) / sizeof(list[0]);
    int result = count_until_tuple(list, length);
    printf("Count until tuple: %d\n", result);
    return 0;
}