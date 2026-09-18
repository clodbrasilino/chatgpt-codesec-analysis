#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string_value;
    int *list_value;
    size_t list_size;
} Tuple;

Tuple* create_tuple(const char *str, const int *list, size_t list_size);
void free_tuple(Tuple *tuple);

Tuple* create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL) {
        return NULL;
    }
    if (list == NULL && list_size > 0) {
        return NULL;
    }

    Tuple *new_tuple = (Tuple*)malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return NULL;
    }

    size_t str_len = strlen(str);
    new_tuple->string_value = (char*)malloc(str_len + 1);
    if (new_tuple->string_value == NULL) {
        free(new_tuple);
        return NULL;
    }
    memcpy(new_tuple->string_value, str, str_len + 1);

    if (list_size > 0) {
        new_tuple->list_value = (int*)malloc(list_size * sizeof(int));
        if (new_tuple->list_value == NULL) {
            free(new_tuple->string_value);
            free(new_tuple);
            return NULL;
        }
        memcpy(new_tuple->list_value, list, list_size * sizeof(int));
    } else {
        new_tuple->list_value = NULL;
    }

    new_tuple->list_size = list_size;

    return new_tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->string_value);
        free(tuple->list_value);
        free(tuple);
    }
}

int main(void) {
    const char *sample_string = "TupleString";
    int sample_list[] = {10, 20, 30, 40, 50};
    size_t sample_list_size = sizeof(sample_list) / sizeof(sample_list[0]);

    Tuple *my_tuple = create_tuple(sample_string, sample_list, sample_list_size);
    
    if (my_tuple == NULL) {
        fprintf(stderr, "Failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", my_tuple->string_value);
    printf("List: ");
    for (size_t i = 0; i < my_tuple->list_size; ++i) {
        printf("%d ", my_tuple->list_value[i]);
    }
    printf("\n");

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}