#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    double b;
    char c;
} Tuple;

char *tuple_to_string(const Tuple *t) {
    if (t == NULL) {
        return NULL;
    }

    size_t buffer_size = 64;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return NULL;
    }

    int written = snprintf(buffer, buffer_size, "(%d, %f, %c)", t->a, t->b, t->c);
    if (written < 0) {
        free(buffer);
        return NULL;
    }

    if ((size_t)written >= buffer_size) {
        size_t new_size = (size_t)written + 1;
        char *new_buffer = (char *)realloc(buffer, new_size);
        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }
        buffer = new_buffer;
        snprintf(buffer, new_size, "(%d, %f, %c)", t->a, t->b, t->c);
    }

    return buffer;
}

int main(void) {
    Tuple t = {42, 3.14, 'A'};
    char *str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    } else {
        fprintf(stderr, "Failed to convert tuple to string\n");
        return 1;
    }

    return 0;
}