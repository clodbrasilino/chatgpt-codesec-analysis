#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_STR
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_value;
        char *str_value;
    } data;
} MixedValue;

int compare_values(const MixedValue *a, const MixedValue *b) {
    if (a->type == TYPE_INT && b->type == TYPE_INT) {
        return (a->data.int_value > b->data.int_value) - (a->data.int_value < b->data.int_value);
    } else if (a->type == TYPE_STR && b->type == TYPE_STR) {
        return strcmp(a->data.str_value, b->data.str_value);
    } else if (a->type == TYPE_INT && b->type == TYPE_STR) {
        return -1;
    } else {
        return 1;
    }
}

void sort_mixed_list(MixedValue *list, size_t size) {
    size_t i, j;
    MixedValue temp;

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (compare_values(&list[i], &list[j]) > 0) {
                memcpy(&temp, &list[i], sizeof(MixedValue));
                memcpy(&list[i], &list[j], sizeof(MixedValue));
                memcpy(&list[j], &temp, sizeof(MixedValue));
            }
        }
    }
}

void print_mixed_value(const MixedValue *value) {
    if (value->type == TYPE_INT) {
        printf("%d ", value->data.int_value);
    } else {
        printf("%s ", value->data.str_value);
    }
}

int main(void) {
    MixedValue list[] = {
        {TYPE_STR, .data.str_value = "banana"},
        {TYPE_INT, .data.int_value = 42},
        {TYPE_STR, .data.str_value = "apple"},
        {TYPE_INT, .data.int_value = 7},
        {TYPE_STR, .data.str_value = "cherry"},
        {TYPE_INT, .data.int_value = 100},
        {TYPE_STR, .data.str_value = "date"},
        {TYPE_INT, .data.int_value = 3}
    };

    size_t size = sizeof(list) / sizeof(list[0]);
    size_t i;

    sort_mixed_list(list, size);

    for (i = 0; i < size; i++) {
        print_mixed_value(&list[i]);
    }
    printf("\n");

    return 0;
}