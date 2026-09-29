#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
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
    size_t source_len;
    
    memset(&t, 0, sizeof(Tuple));
    t.id = 1;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    source_len = strlen(source);
    t.name = (char *)malloc(source_len + 1);
    if (t.name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(t.name, source);
    
    t.value = 3.14;
    
    size = get_tuple_size(&t);
    printf("Size of tuple: %zu bytes\n", size);
    
    free(t.name);
    
    return 0;
}