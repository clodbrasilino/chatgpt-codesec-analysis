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
    if (len >= max_size) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\0') {
            return true;
        }
    }
    return str[len] == '\0';
}

static bool safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    if (src[i] != '\0') {
        return false;
    }

    return true;
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
    my_tuple.size = 0;

    if (safe_strncpy(my_tuple.elements[0], "apple", MAX_ELEMENT_SIZE)) {
        my_tuple.size++;
    }
    if (safe_strncpy(my_tuple.elements[1], "banana", MAX_ELEMENT_SIZE)) {
        my_tuple.size++;
    }
    if (safe_strncpy(my_tuple.elements[2], "cherry", MAX_ELEMENT_SIZE)) {
        my_tuple.size++;
    }
    if (safe_strncpy(my_tuple.elements[3], "date", MAX_ELEMENT_SIZE)) {
        my_tuple.size++;
    }
    if (safe_strncpy(my_tuple.elements[4], "elderberry", MAX_ELEMENT_SIZE)) {
        my_tuple.size++;
    }

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