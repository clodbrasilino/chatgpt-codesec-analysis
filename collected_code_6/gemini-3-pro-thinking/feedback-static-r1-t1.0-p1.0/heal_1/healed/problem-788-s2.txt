#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple->list);
        free(tuple);
    }
}

Tuple* create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    Tuple *new_tuple = (Tuple*)malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return NULL;
    }

    size_t str_len = 0;
    while (str_len < MAX_STR_LEN && str[str_len] != '\0') {
        str_len++;
    }

    new_tuple->str = (char*)malloc(str_len + 1);
    if (new_tuple->str == NULL) {
        free(new_tuple);
        return NULL;
    }

    for (size_t i = 0; i < str_len; i++) {
        new_tuple->str[i] = str[i];
    }
    new_tuple->str[str_len] = '\0';

    new_tuple->list_size = list_size;
    if (list_size > 0) {
        new_tuple->list = (int*)calloc(list_size, sizeof(int));
        if (new_tuple->list == NULL) {
            free(new_tuple->str);
            free(new_tuple);
            return NULL;
        }
        
        for (size_t i = 0; i < list_size; i++) {
            new_tuple->list[i] = list[i];
        }
    } else {
        new_tuple->list = NULL;
    }

    return new_tuple;
}

int main(void) {
    const char *sample_string = "ExampleData";
    int sample_list[] = {10, 20, 30, 40, 50};
    size_t list_size = sizeof(sample_list) / sizeof(sample_list[0]);

    Tuple *my_tuple = create_tuple(sample_string, sample_list, list_size);
    if (my_tuple == NULL) {
        fprintf(stderr, "Failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", my_tuple->str);
    printf("List: ");
    for (size_t i = 0; i < my_tuple->list_size; i++) {
        printf("%d ", my_tuple->list[i]);
    }
    printf("\n");

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}