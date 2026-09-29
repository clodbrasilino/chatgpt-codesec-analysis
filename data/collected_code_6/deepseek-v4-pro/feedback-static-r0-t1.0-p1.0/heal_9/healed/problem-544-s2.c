#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct tuple {
    int32_t first;
    int32_t second;
    struct tuple *next;
} tuple_t;

static size_t int32_to_str(int32_t value, char *buffer, size_t buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }
    int written = snprintf(buffer, buffer_size, "%d", value);
    if (written < 0) {
        buffer[0] = '\0';
        return 0;
    }
    if ((size_t)written >= buffer_size) {
        buffer[buffer_size - 1] = '\0';
        return buffer_size - 1;
    }
    return (size_t)written;
}

static char *append_to_result(char *result, size_t *current_len, size_t *capacity,
                              const char *text, size_t text_len) {
    if (text_len == 0) {
        return result;
    }
    if (*current_len > SIZE_MAX - text_len - 1) {
        return NULL;
    }
    size_t required_size = *current_len + text_len + 1;
    if (required_size > *capacity) {
        size_t new_capacity = *capacity;
        if (new_capacity == 0) {
            new_capacity = 64;
        }
        while (new_capacity < required_size) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required_size;
                break;
            }
            new_capacity *= 2;
        }
        char *new_result = (char*)realloc(result, new_capacity);
        if (new_result == NULL) {
            return NULL;
        }
        result = new_result;
        *capacity = new_capacity;
    }
    if (text_len > *capacity - *current_len) {
        return NULL;
    }
    memcpy(result + *current_len, text, text_len);
    *current_len += text_len;
    result[*current_len] = '\0';
    return result;
}

char *flatten_tuple_list(tuple_t *head) {
    if (head == NULL) {
        char *empty = (char*)malloc(3);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '[';
        empty[1] = ']';
        empty[2] = '\0';
        return empty;
    }

    size_t capacity = 64;
    char *result = (char*)malloc(capacity);
    if (result == NULL) {
        return NULL;
    }
    size_t current_len = 0;
    result[0] = '\0';

    char *tmp = append_to_result(result, &current_len, &capacity, "[", 1);
    if (tmp == NULL) {
        free(result);
        return NULL;
    }
    result = tmp;

    char num_buffer[16];
    tuple_t *current = head;
    int first_iteration = 1;

    while (current != NULL) {
        if (!first_iteration) {
            tmp = append_to_result(result, &current_len, &capacity, ", ", 2);
            if (tmp == NULL) {
                free(result);
                return NULL;
            }
            result = tmp;
        }
        first_iteration = 0;

        tmp = append_to_result(result, &current_len, &capacity, "(", 1);
        if (tmp == NULL) {
            free(result);
            return NULL;
        }
        result = tmp;

        size_t len1 = int32_to_str(current->first, num_buffer, sizeof(num_buffer));
        if (len1 == 0 && current->first != 0) {
            free(result);
            return NULL;
        }
        if (len1 >= sizeof(num_buffer)) {
            free(result);
            return NULL;
        }
        tmp = append_to_result(result, &current_len, &capacity, num_buffer, len1);
        if (tmp == NULL) {
            free(result);
            return NULL;
        }
        result = tmp;

        tmp = append_to_result(result, &current_len, &capacity, ", ", 2);
        if (tmp == NULL) {
            free(result);
            return NULL;
        }
        result = tmp;

        size_t len2 = int32_to_str(current->second, num_buffer, sizeof(num_buffer));
        if (len2 == 0 && current->second != 0) {
            free(result);
            return NULL;
        }
        if (len2 >= sizeof(num_buffer)) {
            free(result);
            return NULL;
        }
        tmp = append_to_result(result, &current_len, &capacity, num_buffer, len2);
        if (tmp == NULL) {
            free(result);
            return NULL;
        }
        result = tmp;

        tmp = append_to_result(result, &current_len, &capacity, ")", 1);
        if (tmp == NULL) {
            free(result);
            return NULL;
        }
        result = tmp;

        current = current->next;
    }

    tmp = append_to_result(result, &current_len, &capacity, "]", 1);
    if (tmp == NULL) {
        free(result);
        return NULL;
    }
    result = tmp;

    return result;
}

int main(void) {
    tuple_t t3 = {30, 40, NULL};
    tuple_t t2 = {20, 30, &t3};
    tuple_t t1 = {10, 20, &t2};

    char *flat = flatten_tuple_list(&t1);
    if (flat == NULL) {
        printf("Error: failed to flatten list\n");
        return 1;
    }
    printf("%s\n", flat);
    free(flat);

    tuple_t single = {5, 6, NULL};
    char *flat_single = flatten_tuple_list(&single);
    if (flat_single == NULL) {
        printf("Error: failed to flatten single\n");
        return 1;
    }
    printf("%s\n", flat_single);
    free(flat_single);

    char *flat_empty = flatten_tuple_list(NULL);
    if (flat_empty == NULL) {
        printf("Error: failed to flatten empty\n");
        return 1;
    }
    printf("%s\n", flat_empty);
    free(flat_empty);

    return 0;
}