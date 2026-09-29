#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    double value;
} Tuple;

size_t get_tuple_size(const Tuple *t) {
    if (t == NULL) {
        return 0;
    }
    return sizeof(*t);
}

int main(void) {
    Tuple t;
    size_t size;
    
    memset(&t, 0, sizeof(Tuple));
    t.id = 1;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(t.name, "example", sizeof(t.name) - 1);
    t.name[sizeof(t.name) - 1] = '\0';
    t.value = 3.14;
    
    size = get_tuple_size(&t);
    printf("Size of tuple: %zu bytes\n", size);
    
    return 0;
}