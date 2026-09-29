#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TUPLE_SIZE 10
#define MAX_ELEMENT_SIZE 32

typedef struct {
    char elements[MAX_TUPLE_SIZE][MAX_ELEMENT_SIZE];
    int size;
} Tuple;

static bool is_valid_string(const char *str, size_t max_size) {
    if (str == NULL) {
        return false;
    }
    size_t len = 0;
    while (len < max_size && str[len] != '\0') {
        len++;
    }
    if (len >= max_size) {
        return false;
    }
    return true;
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

    size_t element_len = 0;
    while (element_len < MAX_ELEMENT_SIZE && element[element_len] != '\0') {
        element_len++;
    }

    for (int i = 0; i < tuple->size; i++) {
        if (!is_valid_string(tuple->elements[i], MAX_ELEMENT_SIZE)) {
            continue;
        }

        size_t current_len = 0;
        while (current_len < MAX_ELEMENT_SIZE && tuple->elements[i][current_len] != '\0') {
            current_len++;
        }

        if (current_len == element_len) {
            bool match = true;
            for (size_t j = 0; j < element_len; j++) {
                if (tuple->elements[i][j] != element[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    Tuple my_tuple;
    my_tuple.size = 0;

    const char *fruits[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int num_fruits = sizeof(fruits) / sizeof(fruits[0]);

    for (int i = 0; i < num_fruits && i < MAX_TUPLE_SIZE; i++) {
        if (safe_strncpy(my_tuple.elements[i], fruits[i], MAX_ELEMENT_SIZE)) {
            my_tuple.size++;
        }
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