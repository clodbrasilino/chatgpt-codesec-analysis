#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* join_tuples(Tuple* input, int n, int* out_size) {
    if (n == 0) {
        *out_size = 0;
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(n * sizeof(Tuple));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    int r_idx = 0;
    result[r_idx] = input[0];

    for (int i = 1; i < n; i++) {
        if (input[i].a == result[r_idx].a) {
            result[r_idx].b += input[i].b;
        } else {
            r_idx++;
            result[r_idx] = input[i];
        }
    }

    *out_size = r_idx + 1;

    Tuple* trimmed = (Tuple*)realloc(result, (*out_size) * sizeof(Tuple));
    if (trimmed != NULL) {
        result = trimmed;
    }

    return result;
}

int main() {
    Tuple data[] = {{1, 2}, {1, 5}, {2, 3}, {3, 1}, {3, 4}};
    int n = sizeof(data) / sizeof(data[0]);
    int out_size = 0;

    Tuple* joined = join_tuples(data, n, &out_size);

    if (joined != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("(%d, %d)\n", joined[i].a, joined[i].b);
        }
        free(joined);
    }

    return 0;
}