#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_len)
{
    Tuple *t;
    char *new_str;
    int *new_list;
    size_t str_len;

    if (str == NULL || (list == NULL && list_len > 0)) {
        return NULL;
    }

    t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    str_len = strnlen(str, 1024);
    if (str_len == 1024) {
        free(t);
        return NULL;
    }

    new_str = (char *)malloc(str_len + 1);
    if (new_str == NULL) {
        free(t);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, str, str_len + 1);

    new_list = NULL;
    if (list_len > 0) {
        if (list_len > SIZE_MAX / sizeof(int)) {
            free(new_str);
            free(t);
            return NULL;
        }
        new_list = (int *)malloc(list_len * sizeof(int));
        if (new_list == NULL) {
            free(new_str);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_list, list, list_len * sizeof(int));
    }

    t->str = new_str;
    t->list = new_list;
    t->list_len = list_len;

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

int main(void)
{
    const char *str = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    Tuple *t;
    size_t i;

    t = create_tuple(str, list, list_len);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", t->str);
    printf("List: ");
    for (i = 0; i < t->list_len; i++) {
        printf("%d ", t->list[i]);
    }
    printf("\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}