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
        List current = nested.rows[i];
        if (col >= current.size) {
            result.rows[i].data = (int *)malloc(current.size * sizeof(int));
            if (result.rows[i].data == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result.rows[j].data);
                }
                free(result.rows);
                exit(EXIT_FAILURE);
            }
            for (int k = 0; k < current.size; k++) {
                result.rows[i].data[k] = current.data[k];
            }
            result.rows[i].size = current.size;
        } else {
            int new_size = current.size - 1;
            result.rows[i].data = (int *)malloc(new_size * sizeof(int));
            if (result.rows[i].data == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result.rows[j].data);
                }
                free(result.rows);
                exit(EXIT_FAILURE);
            }
            for (int k = 0, m = 0; k < current.size; k++) {
                if (k != col) {
                    result.rows[i].data[m++] = current.data[k];
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
    
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9, 10};
    
    nested.rows[0].data = row0;
    nested.rows[0].size = 3;
    nested.rows[1].data = row1;
    nested.rows[1].size = 3;
    nested.rows[2].data = row2;
    nested.rows[2].size = 4;

    NestedList result = remove_column(nested, 1);

    for (int i = 0; i < result.num_rows; i++) {
        for (int j = 0; j < result.rows[i].size; j++) {
            printf("%d ", result.rows[i].data[j]);
        }
        printf("\n");
    }

    free_nested_list(result);
    free(nested.rows);

    return 0;
}