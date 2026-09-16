#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_FLOAT,
    TYPE_LONG,
    TYPE_SHORT,
    TYPE_CHAR
} DataType;

typedef struct Node {
    void *data;
    DataType type;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} HeterogeneousList;

HeterogeneousList *list_create(void) {
    HeterogeneousList *list = (HeterogeneousList *)malloc(sizeof(HeterogeneousList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_destroy(HeterogeneousList *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int list_append(HeterogeneousList *list, void *data, DataType type) {
    if (list == NULL || data == NULL) {
        return 0;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    new_node->data = data;
    new_node->type = type;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 1;
}

double node_to_double(Node *node) {
    if (node == NULL || node->data == NULL) {
        return 0.0;
    }
    switch (node->type) {
        case TYPE_INT:
            return (double)(*(int *)node->data);
        case TYPE_DOUBLE:
            return *(double *)node->data;
        case TYPE_FLOAT:
            return (double)(*(float *)node->data);
        case TYPE_LONG:
            return (double)(*(long *)node->data);
        case TYPE_SHORT:
            return (double)(*(short *)node->data);
        case TYPE_CHAR:
            return (double)(*(char *)node->data);
        default:
            return 0.0;
    }
}

double list_find_max(HeterogeneousList *list) {
    if (list == NULL || list->head == NULL || list->size == 0) {
        return 0.0;
    }
    Node *current = list->head;
    double max_value = node_to_double(current);
    
    while (current != NULL) {
        double current_value = node_to_double(current);
        if (current_value > max_value) {
            max_value = current_value;
        }
        current = current->next;
    }
    return max_value;
}

int *create_int(int value) {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return ptr;
}

double *create_double(double value) {
    double *ptr = (double *)malloc(sizeof(double));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return ptr;
}

float *create_float(float value) {
    float *ptr = (float *)malloc(sizeof(float));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return ptr;
}

long *create_long(long value) {
    long *ptr = (long *)malloc(sizeof(long));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return ptr;
}

short *create_short(short value) {
    short *ptr = (short *)malloc(sizeof(short));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return ptr;
}

char *create_char(char value) {
    char *ptr = (char *)malloc(sizeof(char));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return ptr;
}

int main(void) {
    HeterogeneousList *list = list_create();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    int *int_val = create_int(42);
    double *double_val = create_double(3.14);
    float *float_val = create_float(2.718f);
    long *long_val = create_long(100000L);
    short *short_val = create_short(50);
    char *char_val = create_char('A');

    if (int_val == NULL || double_val == NULL || float_val == NULL ||
        long_val == NULL || short_val == NULL || char_val == NULL) {
        list_destroy(list);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (!list_append(list, int_val, TYPE_INT) ||
        !list_append(list, double_val, TYPE_DOUBLE) ||
        !list_append(list, float_val, TYPE_FLOAT) ||
        !list_append(list, long_val, TYPE_LONG) ||
        !list_append(list, short_val, TYPE_SHORT) ||
        !list_append(list, char_val, TYPE_CHAR)) {
        list_destroy(list);
        fprintf(stderr, "Failed to append elements\n");
        return 1;
    }

    double max_value = list_find_max(list);
    printf("Maximum value in the list: %f\n", max_value);

    list_destroy(list);
    return 0;
}