#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntTuple;

IntTuple convert_string_to_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    
    if (str == NULL) {
        return tuple;
    }

    size_t count = 0;
    const char *temp = str;
    while (*temp != '\0') {
        if (*temp == ',' || *temp == ' ' || count == 0) {
            int val;
            int offset;
            if (sscanf(temp, "%d%n", &val, &offset) == 1) {
                count++;
            }
        }
        temp++;
    }

    if (count == 0) {
        return tuple;
    }

    tuple.data = (int *)malloc(count * sizeof(int));
    if (tuple.data == NULL) {
        return tuple;
    }

    tuple.size = count;

    size_t index = 0;
    const char *ptr = str;
    while (*ptr != '\0' && index < tuple.size) {
        int val;
        int offset;
        if (sscanf(ptr, "%d%n", &val, &offset) == 1) {
            tuple.data[index++] = val;
            ptr += offset;
        } else {
            ptr++;
        }
    }

    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple != NULL && tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    const char *input = "10, 20, 30, 42, 55";
    
    IntTuple my_tuple = convert_string_to_tuple(input);
    
    if (my_tuple.data != NULL) {
        printf("Tuple size: %zu\n", my_tuple.size);
        printf("Tuple elements: ");
        for (size_t i = 0; i < my_tuple.size; i++) {
            printf("%d ", my_tuple.data[i]);
        }
        printf("\n");
        
        free_tuple(&my_tuple);
    } else {
        printf("Failed to create tuple or empty input.\n");
    }

    return 0;
}