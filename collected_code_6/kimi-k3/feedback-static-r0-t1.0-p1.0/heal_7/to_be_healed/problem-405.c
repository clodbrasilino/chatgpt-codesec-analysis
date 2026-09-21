#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[64];
} Tuple;

bool tuple_contains(const Tuple *tuple, const char *search_name) {
    if (tuple == NULL || search_name == NULL) {
        return false;
    }
    
    size_t tuple_len = strnlen(tuple->name, sizeof(tuple->name));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t search_len = strlen(search_name);
    
    if (tuple_len != search_len) {
        return false;
    }
    
    return memcmp(tuple->name, search_name, tuple_len) == 0;
}

int main(void) {
    Tuple my_tuple;
    snprintf(my_tuple.name, sizeof(my_tuple.name), "%s", "example");
    
    const char *search = "example";
    
    if (tuple_contains(&my_tuple, search)) {
        printf("Element exists in tuple\n");
    } else {
        printf("Element not found in tuple\n");
    }
    
    return 0;
}