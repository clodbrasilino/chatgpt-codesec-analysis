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
    if (tuple == NULL || element == NULL || tuple->size <= 0 || tuple->size > MAX_TUPLE_SIZE) {
        return false;
    }

    for (int i = 0; i < tuple->size; i++) {
        if (strncmp(tuple->elements[i], element, MAX_ELEMENT_SIZE - 1) == 0) {
            return true;
        }
    }
    return false;
}

size_t safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return i;
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