#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int z;
} Tuple;

char* tuple_to_string(const Tuple *t) {
    if (t == NULL) {
        return NULL;
    }
    
    int size = snprintf(NULL, 0, "(%d, %d, %d)", t->x, t->y, t->z);
    if (size < 0) {
        return NULL;
    }
    
    char *result = (char*)malloc((size_t)size + 1);
    if (result == NULL) {
        return NULL;
    }
    
    int written = snprintf(result, (size_t)size + 1, "(%d, %d, %d)", t->x, t->y, t->z);
    if (written < 0 || written > size) {
        free(result);
        return NULL;
    }
    
    return result;
}

int main(void) {
    Tuple t = {10, 20, 30};
    char *str = tuple_to_string(&t);
    
    if (str == NULL) {
        fprintf(stderr, "Error converting tuple to string\n");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", str);
    free(str);
    
    return EXIT_SUCCESS;
}