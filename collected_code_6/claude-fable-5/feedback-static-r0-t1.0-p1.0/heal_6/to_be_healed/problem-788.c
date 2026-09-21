#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096
#define MAX_LIST_SIZE 1024

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size)
{
    Tuple *t;
    size_t len;
    size_t str_bytes;
    size_t list_bytes;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    if (list_size > MAX_LIST_SIZE) {
        return NULL;
    }

    len = strnlen(str, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }
    str_bytes = len + 1;

    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    list_bytes = list_size * sizeof(int);

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->str = malloc(str_bytes);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }

    if (len > 0 && len < str_bytes) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->str, str, len);
    }
    t->str[len] = '\0';

    if (list_size > 0) {
        t->list = malloc(list_bytes);
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        if (list_bytes / sizeof(int) == list_size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(t->list, list, list_bytes);
        } else {
            free(t->list);
            free(t->str);
            free(t);
            return NULL;
        }
    } else {
        t->list = NULL;
    }

    t->list_size = list_size;
    return t;
}

void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

void print_tuple(const Tuple *t)
{
    size_t i;

    if (t == NULL || t->str == NULL) {
        return;
    }

    printf("(\"%s\", [", t->str);
    for (i = 0; i < t->list_size; i++) {
        if (t->list == NULL) {
            break;
        }
        printf("%d", t->list[i]);
        if (i + 1 < t->list_size) {
            printf(", ");
        }
    }
    printf("])\n");
}

int main(void)
{
    const char *s = "WEB";
    int values[] = {1, 2};
    Tuple *t;

    t = create_tuple(s, values, sizeof(values) / sizeof(values[0]));
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}