#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    float b;
    char c[20];
} Tuple;

char* flatten_tuple_list(Tuple *list, size_t length) {
    size_t total_size = 0;
    for (size_t i = 0; i < length; ++i) {
        total_size += snprintf(NULL, 0, "(%d, %.2f, %s)", list[i].a, list[i].b, list[i].c);
    }
    total_size += length - 1; // for commas
    if (length > 0) total_size += 1; // for trailing comma
    char *result = (char *)malloc(total_size + 1); // +1 for null terminator
    if (result == NULL) return NULL;
    char *ptr = result;
    for (size_t i = 0; i < length; ++i) {
        ptr += snprintf(ptr, total_size - (ptr - result), "(%d, %.2f, %s)", list[i].a, list[i].b, list[i].c);
        if (i < length - 1) {
            *ptr++ = ',';
        }
    }
    *ptr = '\0';
    return result;
}

int main() {
    Tuple t1 = {1, 2.5, "abc"};
    Tuple t2 = {4, 5.75, "def"};
    Tuple *list = (Tuple *)malloc(2 * sizeof(Tuple));
    if (list == NULL) return 1;
    memcpy(list, &t1, sizeof(Tuple));
    memcpy(list + 1, &t2, sizeof(Tuple));
    
    char *flattened = flatten_tuple_list(list, 2);
    if (flattened) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        printf("Failed to flatten the list.\n");
    }
    free(list);
    return 0;
}