#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
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
    strncpy(t.name, "example", sizeof(t.name) - 1);
    t.name[sizeof(t.name) - 1] = '\0';
    t.value = 3.14;
    
    size = get_tuple_size(&t);
    printf("Size of tuple: %zu bytes\n", size);
    
    return 0;
}