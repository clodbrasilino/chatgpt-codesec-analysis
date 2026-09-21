#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING,
    TYPE_TUPLE
} ElementType;

typedef struct {
    ElementType type;
    void *data;
} Element;

typedef struct {
    Element *elements;
    size_t count;
    size_t capacity;
} List;

int list_init(List *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    if (initial_capacity > SIZE_MAX / sizeof(Element)) {
        return -1;
    }
    list->elements = malloc(initial_capacity * sizeof(Element));
    if (list->elements == NULL) {
        return -1;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

int list_add_int(List *list, int value) {
    if (list == NULL || list->count >= list->capacity) {
        return -1;
    }
    int *data = malloc(sizeof(int));
    if (data == NULL) {
        return -1;
    }
    *data = value;
    list->elements[list->count].type = TYPE_INT;
    list->elements[list->count].data = data;
    list->count++;
    return 0;
}

int list_add_string(List *list, const char *value, size_t max_len) {
    if (list == NULL || value == NULL || list->count >= list->capacity) {
        return -1;
    }
    if (max_len == 0) {
        return -1;
    }
    size_t len = strnlen(value, max_len);
    if (len == max_len && value[len] != '\0') {
        return -1;
    }
    if (len == SIZE_MAX) {
        return -1;
    }
    char *data = malloc(len + 1);
    if (data == NULL) {
        return -1;
    }
    if (len > 0) {
        memcpy(data, value, len);
    }
    data[len] = '\0';
    list->elements[list->count].type = TYPE_STRING;
    list->elements[list->count].data = data;
    list->count++;
    return 0;
}

int list_add_tuple(List *list) {
    if (list == NULL || list->count >= list->capacity) {
        return -1;
    }
    list->elements[list->count].type = TYPE_TUPLE;
    list->elements[list->count].data = NULL;
    list->count++;
    return 0;
}

size_t count_until_tuple(const List *list) {
    if (list == NULL) {
        return 0;
    }
    size_t count = 0;
    for (size_t i = 0; i < list->count; i++) {
        if (list->elements[i].type == TYPE_TUPLE) {
            break;
        }
        count++;
    }
    return count;
}

void list_free(List *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->elements[i].data);
    }
    free(list->elements);
    list->elements = NULL;
    list->count = 0;
    list->capacity = 0;
}

int main(void) {
    List list;
    if (list_init(&list, 10) != 0) {
        fprintf(stderr, "Failed to initialize list\n");
        return EXIT_FAILURE;
    }

    if (list_add_int(&list, 42) != 0 ||
        list_add_string(&list, "hello", 256) != 0 ||
        list_add_int(&list, 100) != 0 ||
        list_add_tuple(&list) != 0 ||
        list_add_int(&list, 200) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        list_free(&list);
        return EXIT_FAILURE;
    }

    size_t result = count_until_tuple(&list);
    printf("Elements before tuple: %zu\n", result);

    list_free(&list);
    return EXIT_SUCCESS;
}