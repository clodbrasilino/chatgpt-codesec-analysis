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
    const char *source = "example";
    
    memset(&t, 0, sizeof(Tuple));
    t.id = 1;
    
    if (strlen(source) < sizeof(t.name)) {
        strcpy(t.name, source);
    } else {
        fprintf(stderr, "Error: Source string too long for buffer\n");
        return 1;
    }
    
    t.value = 3.14;
    
    size = get_tuple_size(&t);
    printf("Size of tuple: %zu bytes\n", size);
    
    return 0;
}