#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_INITIAL_CAPACITY 5

typedef struct {
    char **elements;
    size_t count;
    size_t capacity;
} StringList;

StringList* create_string_list() {
    StringList *list = (StringList*)malloc(sizeof(StringList));
    if (list == NULL) return NULL;
    list->elements = (char**)malloc(LIST_INITIAL_CAPACITY * sizeof(char*));
    if (list->elements == NULL) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = LIST_INITIAL_CAPACITY;
    return list;
}

void free_string_list(StringList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        free(list->elements[i]);
    }
    free(list->elements);
    free(list);
}

int add_to_list(StringList *list, const char *str) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        char **temp = (char**)realloc(list->elements, list->capacity * sizeof(char*));
        if (temp == NULL) {
            return -1;
        }
        list->elements = temp;
    }

    list->elements[list->count] = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (list->elements[list->count] == NULL) {
        return -1;
    }
    strcpy(list->elements[list->count], str);
    ++list->count;
    return 0;
}

StringList* convert_string_to_list(const char *str, const char *delimiter) {
    StringList *list = create_string_list();
    if (list == NULL) return NULL;
    char *mutable_str = strdup(str);
    if (mutable_str == NULL) {
        free_string_list(list);
        return NULL;
    }
    char *token = strtok(mutable_str, delimiter);

    while (token != NULL) {
        if (add_to_list(list, token) != 0) {
            free(mutable_str);
            free_string_list(list);
            return NULL;
        }
        token = strtok(NULL, delimiter);
    }

    free(mutable_str);
    return list;
}

int main() {
    const char *input = "apple,banana,cherry,date";
    const char *delimiter = ",";
    StringList *result = convert_string_to_list(input, delimiter);

    if (result != NULL) {
        for (size_t i = 0; i < result->count; ++i) {
            printf("%s\n", result->elements[i]);
        }
        free_string_list(result);
    } else {
        printf("Failed to convert string to list.\n");
    }

    return 0;
}