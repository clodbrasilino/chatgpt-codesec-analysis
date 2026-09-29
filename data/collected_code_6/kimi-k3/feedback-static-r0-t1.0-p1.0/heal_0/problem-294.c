#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_FLOAT
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        double d;
        float f;
    } value;
} HeterogeneousElement;

typedef struct {
    HeterogeneousElement *elements;
    size_t count;
    size_t capacity;
} HeterogeneousList;

bool list_init(HeterogeneousList *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return false;
    }
    list->elements = malloc(initial_capacity * sizeof(HeterogeneousElement));
    if (list->elements == NULL) {
        return false;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return true;
}

void list_destroy(HeterogeneousList *list) {
    if (list != NULL) {
        free(list->elements);
        list->elements = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

bool list_add_int(HeterogeneousList *list, int value) {
    if (list == NULL || list->count >= list->capacity) {
        return false;
    }
    list->elements[list->count].type = TYPE_INT;
    list->elements[list->count].value.i = value;
    list->count++;
    return true;
}

bool list_add_double(HeterogeneousList *list, double value) {
    if (list == NULL || list->count >= list->capacity) {
        return false;
    }
    list->elements[list->count].type = TYPE_DOUBLE;
    list->elements[list->count].value.d = value;
    list->count++;
    return true;
}

bool list_add_float(HeterogeneousList *list, float value) {
    if (list == NULL || list->count >= list->capacity) {
        return false;
    }
    list->elements[list->count].type = TYPE_FLOAT;
    list->elements[list->count].value.f = value;
    list->count++;
    return true;
}

bool find_max(const HeterogeneousList *list, double *max_value) {
    if (list == NULL || max_value == NULL || list->count == 0) {
        return false;
    }

    double current_max;
    bool first = true;

    for (size_t i = 0; i < list->count; i++) {
        double current_value;
        switch (list->elements[i].type) {
            case TYPE_INT:
                current_value = (double)list->elements[i].value.i;
                break;
            case TYPE_DOUBLE:
                current_value = list->elements[i].value.d;
                break;
            case TYPE_FLOAT:
                current_value = (double)list->elements[i].value.f;
                break;
            default:
                continue;
        }

        if (first || current_value > current_max) {
            current_max = current_value;
            first = false;
        }
    }

    if (first) {
        return false;
    }

    *max_value = current_max;
    return true;
}

int main(void) {
    HeterogeneousList list;
    double max_value;

    if (!list_init(&list, 10)) {
        fprintf(stderr, "Failed to initialize list\n");
        return EXIT_FAILURE;
    }

    if (!list_add_int(&list, 42)) {
        fprintf(stderr, "Failed to add element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    if (!list_add_double(&list, 3.14159)) {
        fprintf(stderr, "Failed to add element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    if (!list_add_float(&list, 2.5f)) {
        fprintf(stderr, "Failed to add element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    if (!list_add_int(&list, 100)) {
        fprintf(stderr, "Failed to add element\n");
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    if (find_max(&list, &max_value)) {
        printf("Maximum value: %f\n", max_value);
    } else {
        printf("List is empty or error occurred\n");
    }

    list_destroy(&list);
    return EXIT_SUCCESS;
}