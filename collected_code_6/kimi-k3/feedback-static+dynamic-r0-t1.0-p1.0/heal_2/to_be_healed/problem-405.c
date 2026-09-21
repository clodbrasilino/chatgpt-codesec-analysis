#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[32];
    double value;
} Tuple;

bool tuple_contains(const Tuple *tuple, const char *search_name) {
    if (tuple == NULL || search_name == NULL) {
        return false;
    }
    return strncmp(tuple->name, search_name, sizeof(tuple->name)) == 0;
}

void tuple_init(Tuple *tuple, int id, const char *name, double value) {
    if (tuple == NULL) {
        return;
    }
    tuple->id = id;
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(tuple->name, name, sizeof(tuple->name) - 1);
        tuple->name[sizeof(tuple->name) - 1] = '\0';
    } else {
        tuple->name[0] = '\0';
    }
    tuple->value = value;
}

int main(void) {
    Tuple my_tuple;
    tuple_init(&my_tuple, 1, "example", 42.5);
    const char *search = "example";
    
    if (tuple_contains(&my_tuple, search)) {
        printf("Element exists in tuple\n");
    } else {
        printf("Element not found in tuple\n");
    }
    
    return 0;
}