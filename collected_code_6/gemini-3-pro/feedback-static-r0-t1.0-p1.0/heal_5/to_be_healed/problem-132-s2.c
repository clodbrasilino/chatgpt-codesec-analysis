#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    char *name;
} Tuple;

char* tuple_to_string(const Tuple* t) {
    if (t == NULL || t->name == NULL) {
        return NULL;
    }

    size_t size = snprintf(NULL, 0, "(%d, %.2f, %s)", t->id, t->value, t->name) + 1;
    char* str = (char*)malloc(size);

    if (str != NULL) {
        snprintf(str, size, "(%d, %.2f, %s)", t->id, t->value, t->name);
    }

    return str;
}

int main(void) {
    Tuple t;
    t.id = 1;
    t.value = 3.14;
    
    const char example_name[] = "Example";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t name_len = strlen(example_name) + 1;
    
    t.name = (char*)malloc(name_len);
    if (t.name == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(t.name, example_name, name_len);
    t.name[name_len - 1] = '\0';

    char* str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    free(t.name);

    return 0;
}