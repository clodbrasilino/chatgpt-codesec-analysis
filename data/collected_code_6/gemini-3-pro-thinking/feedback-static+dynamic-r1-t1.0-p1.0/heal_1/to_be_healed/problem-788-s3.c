#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IntList {
    int *data;
    size_t size;
};

struct Tuple {
    char *str;
    struct IntList list;
};

char* duplicate_string(const char *src) {
    size_t len;
    char *dest;

    if (!src) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    dest = (char *)malloc(len + 1);
    if (!dest) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len + 1);
    return dest;
}

struct Tuple* create_tuple(const char *str, const int *list_data, size_t list_size) {
    struct Tuple *tuple;

    if (!str || (!list_data && list_size > 0)) {
        return NULL;
    }

    tuple = (struct Tuple *)malloc(sizeof(struct Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->str = duplicate_string(str);
    if (!tuple->str) {
        free(tuple);
        return NULL;
    }

    tuple->list.size = list_size;
    if (list_size > 0) {
        tuple->list.data = (int *)malloc(list_size * sizeof(int));
        if (!tuple->list.data) {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->list.data, list_data, list_size * sizeof(int));
    } else {
        tuple->list.data = NULL;
    }

    return tuple;
}

void free_tuple(struct Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->str) {
        free(tuple->str);
    }
    if (tuple->list.data) {
        free(tuple->list.data);
    }
    free(tuple);
}

int main(void) {
    const char *sample_string = "TupleString";
    int sample_list[] = {10, 20, 30, 40, 50};
    size_t list_size = sizeof(sample_list) / sizeof(sample_list[0]);
    struct Tuple *my_tuple;
    size_t i;

    my_tuple = create_tuple(sample_string, sample_list, list_size);
    if (!my_tuple) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", my_tuple->str);
    printf("List: ");
    for (i = 0; i < my_tuple->list.size; i++) {
        printf("%d ", my_tuple->list.data[i]);
    }
    printf("\n");

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}