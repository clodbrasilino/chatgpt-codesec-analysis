#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Tuple;

int tuple_init(Tuple *t, size_t capacity) {
    if (t == NULL || capacity == 0) {
        return -1;
    }
    t->data = malloc(capacity * sizeof(int));
    if (t->data == NULL) {
        return -1;
    }
    t->size = 0;
    t->capacity = capacity;
    return 0;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
        t->capacity = 0;
    }
}

int tuple_contains(const Tuple *t, int value) {
    if (t == NULL || t->data == NULL) {
        return 0;
    }
    for (size_t i = 0; i < t->size; i++) {
        if (t->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

int tuple_add(Tuple *t, int value) {
    if (t == NULL || t->data == NULL) {
        return -1;
    }
    if (t->size >= t->capacity) {
        size_t new_capacity = t->capacity * 2;
        int *new_data = realloc(t->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return -1;
        }
        t->data = new_data;
        t->capacity = new_capacity;
    }
    t->data[t->size] = value;
    t->size++;
    return 0;
}

int remove_duplicates(const Tuple *input, Tuple *output) {
    if (input == NULL || output == NULL || input->data == NULL) {
        return -1;
    }
    
    if (tuple_init(output, input->size) != 0) {
        return -1;
    }
    
    for (size_t i = 0; i < input->size; i++) {
        if (!tuple_contains(output, input->data[i])) {
            if (tuple_add(output, input->data[i]) != 0) {
                tuple_free(output);
                return -1;
            }
        }
    }
    
    return 0;
}

void tuple_print(const Tuple *t) {
    if (t == NULL || t->data == NULL) {
        printf("()\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        printf("%d", t->data[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple input = {0};
    Tuple output = {0};
    int values[] = {1, 2, 2, 3, 4, 4, 5, 1, 6};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    
    if (tuple_init(&input, num_values) != 0) {
        fprintf(stderr, "Failed to initialize input tuple\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < num_values; i++) {
        if (tuple_add(&input, values[i]) != 0) {
            fprintf(stderr, "Failed to add value to tuple\n");
            tuple_free(&input);
            return EXIT_FAILURE;
        }
    }
    
    printf("Original tuple: ");
    tuple_print(&input);
    
    if (remove_duplicates(&input, &output) != 0) {
        fprintf(stderr, "Failed to remove duplicates\n");
        tuple_free(&input);
        return EXIT_FAILURE;
    }
    
    printf("Tuple without duplicates: ");
    tuple_print(&output);
    
    tuple_free(&input);
    tuple_free(&output);
    
    return EXIT_SUCCESS;
}