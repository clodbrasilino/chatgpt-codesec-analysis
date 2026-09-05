#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} List;

typedef struct {
    List *rows;
    int num_rows;
} NestedList;

NestedList remove_column(NestedList nested, int col) {
    if (col < 0) {
        return nested;
    }

    NestedList result;
    result.num_rows = nested.num_rows;
    result.rows = (List *)malloc(result.num_rows * sizeof(List));
    if (result.rows == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nested.num_rows; i++) {
        if (col >= nested.rows[i].size) {
            result.rows[i].data = (int *)malloc(nested.rows[i].size * sizeof(int));
            if (result.rows[i].data == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result.rows[j].data);
                }
                free(result.rows);
                exit(EXIT_FAILURE);
            }
            for (int k = 0; k < nested.rows[i].size; k++) {
                result.rows[i].data[k] = nested.rows[i].data[k];
            }
            result.rows[i].size = nested.rows[i].size;
        } else {
            int new_size = nested.rows[i].size - 1;
            result.rows[i].data = (int *)malloc(new_size * sizeof(int));
            if (result.rows[i].data == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result.rows[j].data);
                }
                free(result.rows);
                exit(EXIT_FAILURE);
            }
            for (int k = 0, m = 0; k < nested.rows[i].size; k++) {
                if (k != col) {
                    result.rows[i].data[m++] = nested.rows[i].data[k];
                }
            }
            result.rows[i].size = new_size;
        }
    }

    return result;
}

void free_nested_list(NestedList nested) {
    for (int i = 0; i < nested.num_rows; i++) {
        free(nested.rows[i].data);
    }
    free(nested.rows);
}

int main() {
    NestedList nested;
    nested.num_rows = 3;
    nested.rows = (List *)malloc(3 * sizeof(List));
    
    nested.rows[0].size = 3;
    nested.rows[0].data = (int *)malloc(3 * sizeof(int));
    nested.rows[0].data[0] = 1;
    nested.rows[0].data[1] = 2;
    nested.rows[0].data[2] = 3;

    nested.rows[1].size = 3;
    nested.rows[1].data = (int *)malloc(3 * sizeof(int));
    nested.rows[1].data[0] = 4;
    nested.rows[1].data[1] = 5;
    nested.rows[1].data[2] = 6;

    nested.rows[2].size = 3;
    nested.rows[2].data = (int *)malloc(3 * sizeof(int));
    nested.rows[2].data[0] = 7;
    nested.rows[2].data[1] = 8;
    nested.rows[2].data[2] = 9;

    NestedList result = remove_column(nested, 1);

    for (int i = 0; i < result.num_rows; i++) {
        for (int j = 0; j < result.rows[i].size; j++) {
            printf("%d ", result.rows[i].data[j]);
        }
        printf("\n");
    }

    free_nested_list(nested);
    free_nested_list(result);

    return 0;
}