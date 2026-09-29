#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

StringTuple string_tuple_concat(const StringTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        StringTuple empty = {NULL, 0};
        return empty;
    }

    size_t total_count = tuple1->count + tuple2->count;
    if (total_count == 0) {
        StringTuple empty = {NULL, 0};
        return empty;
    }

    if (total_count > SIZE_MAX / sizeof(char *)) {
        StringTuple empty = {NULL, 0};
        return empty;
    }

    char **new_items = calloc(total_count, sizeof(char *));
    if (new_items == NULL) {
        StringTuple empty = {NULL, 0};
        return empty;
    }

    size_t index = 0;
    size_t len;
    char *dest;

    for (size_t i = 0; i < tuple1->count; ++i) {
        if (tuple1->items[i] != NULL) {
            size_t max_safe_len = SIZE_MAX - 1;
            const char *str = tuple1->items[i];
            len = 0;
            while (len < max_safe_len && str[len] != '\0') {
                ++len;
            }
            if (len >= max_safe_len) {
                for (size_t j = 0; j < index; ++j) {
                    free(new_items[j]);
                }
                free(new_items);
                StringTuple empty = {NULL, 0};
                return empty;
            }

            dest = malloc(len + 1);
            if (dest == NULL) {
                for (size_t j = 0; j < index; ++j) {
                    free(new_items[j]);
                }
                free(new_items);
                StringTuple empty = {NULL, 0};
                return empty;
            }

            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dest, str, len);
            }
            dest[len] = '\0';
            new_items[index] = dest;
        } else {
            new_items[index] = NULL;
        }
        ++index;
    }

    for (size_t i = 0; i < tuple2->count; ++i) {
        if (tuple2->items[i] != NULL) {
            size_t max_safe_len = SIZE_MAX - 1;
            const char *str = tuple2->items[i];
            len = 0;
            while (len < max_safe_len && str[len] != '\0') {
                ++len;
            }
            if (len >= max_safe_len) {
                for (size_t j = 0; j < index; ++j) {
                    free(new_items[j]);
                }
                free(new_items);
                StringTuple empty = {NULL, 0};
                return empty;
            }

            dest = malloc(len + 1);
            if (dest == NULL) {
                for (size_t j = 0; j < index; ++j) {
                    free(new_items[j]);
                }
                free(new_items);
                StringTuple empty = {NULL, 0};
                return empty;
            }

            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dest, str, len);
            }
            dest[len] = '\0';
            new_items[index] = dest;
        } else {
            new_items[index] = NULL;
        }
        ++index;
    }

    StringTuple result = {new_items, total_count};
    return result;
}

void string_tuple_free(StringTuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; ++i) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    tuple->items = NULL;
    tuple->count = 0;
}

int main(void) {
    char *tuple1_items[] = {"hello", "world", NULL, "test"};
    char *tuple2_items[] = {"foo", "bar"};

    StringTuple tuple1 = {tuple1_items, sizeof(tuple1_items) / sizeof(tuple1_items[0])};
    StringTuple tuple2 = {tuple2_items, sizeof(tuple2_items) / sizeof(tuple2_items[0])};

    StringTuple concatenated = string_tuple_concat(&tuple1, &tuple2);

    if (concatenated.items != NULL) {
        for (size_t i = 0; i < concatenated.count; ++i) {
            if (concatenated.items[i] != NULL) {
                printf("%s\n", concatenated.items[i]);
            } else {
                printf("(null)\n");
            }
        }
        string_tuple_free(&concatenated);
    }

    return 0;
}