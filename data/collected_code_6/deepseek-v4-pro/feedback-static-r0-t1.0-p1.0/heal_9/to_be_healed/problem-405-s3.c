#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TUPLE_SIZE 10
#define MAX_ELEMENT_SIZE 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char elements[MAX_TUPLE_SIZE][MAX_ELEMENT_SIZE];
    int size;
} Tuple;

bool tuple_contains(const Tuple *tuple, const char *element) {
    if (tuple == NULL || element == NULL) {
        return false;
    }
    
    if (tuple->size <= 0 || tuple->size > MAX_TUPLE_SIZE) {
        return false;
    }

    for (int i = 0; i < tuple->size; i++) {
        if (strncmp(tuple->elements[i], element, MAX_ELEMENT_SIZE) == 0) {
            return true;
        }
    }
    return false;
}

size_t safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t src_len = strlen(src);
    size_t copy_len = (src_len < dest_size - 1) ? src_len : dest_size - 1;
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';

    return copy_len;
}

int main(void) {
    Tuple my_tuple;
    my_tuple.size = 5;

    safe_strncpy(my_tuple.elements[0], "apple", MAX_ELEMENT_SIZE);
    safe_strncpy(my_tuple.elements[1], "banana", MAX_ELEMENT_SIZE);
    safe_strncpy(my_tuple.elements[2], "cherry", MAX_ELEMENT_SIZE);
    safe_strncpy(my_tuple.elements[3], "date", MAX_ELEMENT_SIZE);
    safe_strncpy(my_tuple.elements[4], "elderberry", MAX_ELEMENT_SIZE);

    const char *search_element = "cherry";
    if (tuple_contains(&my_tuple, search_element)) {
        printf("Element \"%s\" exists in the tuple.\n", search_element);
    } else {
        printf("Element \"%s\" does not exist in the tuple.\n", search_element);
    }

    const char *missing_element = "fig";
    if (tuple_contains(&my_tuple, missing_element)) {
        printf("Element \"%s\" exists in the tuple.\n", missing_element);
    } else {
        printf("Element \"%s\" does not exist in the tuple.\n", missing_element);
    }

    return 0;
}