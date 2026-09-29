#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct {
    int length;
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
    const char *str2 = "world";

    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    Tuple *t = (Tuple *)malloc(sizeof(Tuple) + 2 * sizeof(void *));
    t->length = 2;
    t->items[0] = (void *)str1;
    t->items[1] = (void *)str2;

    if (element_in_tuple(t, (const void *)"hello", strlen(str1) + 1)) {
        printf("Element found.\n");
    } else {
        printf("Element not found.\n");
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(t);
    return 0;
}