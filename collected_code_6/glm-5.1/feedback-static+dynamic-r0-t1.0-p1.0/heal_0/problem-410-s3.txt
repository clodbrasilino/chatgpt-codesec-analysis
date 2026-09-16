#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum node_type { INTEGER_NODE, FLOAT_NODE };

struct heterogeneous_node {
    enum node_type type;
    union {
        int int_val;
        float float_val;
    } data;
};

float find_minimum(struct heterogeneous_node *list, size_t size) {
    if (list == NULL || size == 0) {
        return (float)INT_MAX;
    }

    float min_val;

    if (list[0].type == INTEGER_NODE) {
        min_val = (float)list[0].data.int_val;
    } else {
        min_val = list[0].data.float_val;
    }

    for (size_t i = 1; i < size; i++) {
        float current_val;
        
        if (list[i].type == INTEGER_NODE) {
            current_val = (float)list[i].data.int_val;
        } else if (list[i].type == FLOAT_NODE) {
            current_val = list[i].data.float_val;
        } else {
            continue;
        }

        if (current_val < min_val) {
            min_val = current_val;
        }
    }

    return min_val;
}

int main(void) {
    struct heterogeneous_node list[] = {
        {INTEGER_NODE, .data.int_val = 42},
        {FLOAT_NODE, .data.float_val = 3.14f},
        {INTEGER_NODE, .data.int_val = -7},
        {FLOAT_NODE, .data.float_val = 19.5f},
        {INTEGER_NODE, .data.int_val = 0}
    };

    size_t size = sizeof(list) / sizeof(list[0]);
    float min_val = find_minimum(list, size);
    
    printf("%f\n", min_val);

    return 0;
}