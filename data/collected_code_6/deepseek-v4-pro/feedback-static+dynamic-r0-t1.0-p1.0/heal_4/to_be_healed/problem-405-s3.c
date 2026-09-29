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

static bool is_valid_string(const char *str, size_t max_size) {
    if (str == NULL) {
        return false;
    }
    size_t len = strnlen(str, max_size);
    return len < max_size;
}

bool tuple_contains(const Tuple *tuple, const char *element) {
    if (tuple == NULL || element == NULL) {
        return false;
    }

    if (tuple->size <= 0 || tuple->size > MAX_TUPLE_SIZE) {
        return false;
    }

    if (!is_valid_string(element, MAX_ELEMENT_SIZE)) {
        return false;
    }

    size_t element_len = strnlen(element, MAX_ELEMENT_SIZE);

    for (int i = 0; i < tuple->size; i++) {
        if (!is_valid_string(tuple->elements[i], MAX_ELEMENT_SIZE)) {
            continue;
        }

        if (strncmp(tuple->elements[i], element, MAX_ELEMENT_SIZE) == 0 &&
            strnlen(tuple->elements[i], MAX_ELEMENT_SIZE) == element_len) {
            return true;
        }
    }
    return false;
}

int main(void) {
    Tuple my_tuple;
    my_tuple.size = 5;

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(my_tuple.elements[0], "apple", MAX_ELEMENT_SIZE - 1);
    my_tuple.elements[0][MAX_ELEMENT_SIZE - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(my_tuple.elements[1], "banana", MAX_ELEMENT_SIZE - 1);
    my_tuple.elements[1][MAX_ELEMENT_SIZE - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(my_tuple.elements[2], "cherry", MAX_ELEMENT_SIZE - 1);
    my_tuple.elements[2][MAX_ELEMENT_SIZE - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(my_tuple.elements[3], "date", MAX_ELEMENT_SIZE - 1);
    my_tuple.elements[3][MAX_ELEMENT_SIZE - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(my_tuple.elements[4], "elderberry", MAX_ELEMENT_SIZE - 1);
    my_tuple.elements[4][MAX_ELEMENT_SIZE - 1] = '\0';

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