#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    int length;
    /* Possible weaknesses found:
     *  initialized flexible array member 'items' is here
     */
    void *items[];
} Tuple;

bool element_in_tuple(Tuple *t, const void *element, size_t elem_size) {
    for (int i = 0; i < t->length; ++i) {
        if (memcmp(t->items[i], element, elem_size) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    const char *str1 = "hello";
    /* Possible weaknesses found:
     *  The scope of the variable 'str2' can be reduced. [variableScope]
     */
    const char *str2 = "world";
    /* Possible weaknesses found:
     *  non-static initialization of a flexible array member
     *  initialization of flexible array member is not allowed
     *  (near initialization for 't')
     */
    Tuple t = {2, (void *[]){str1, str2}};
    
    if (element_in_tuple(&t, (const void *)"hello", sizeof(str1))) {
        printf("Element found.\n");
    } else {
        printf("Element not found.\n");
    }

    return 0;
}