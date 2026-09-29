#include <stdio.h>
#include <stdlib.h>

#define MAX_TUPLES 100
#define MAX_ELEMENTS 100

typedef struct {
    int elements[MAX_ELEMENTS];
    int size;
} Tuple;

int join_tuples(Tuple *input, int input_count, Tuple *output) {
    if (input == NULL || output == NULL || input_count <= 0 || input_count > MAX_TUPLES) {
        return 0;
    }

    int output_count = 0;

    for (int i = 0; i < input_count; i++) {
        if (input[i].size <= 0 || input[i].size > MAX_ELEMENTS) {
            continue;
        }

        int found = -1;
        for (int j = 0; j < output_count; j++) {
            if (output[j].elements[0] == input[i].elements[0]) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            for (int k = 1; k < input[i].size; k++) {
                if (output[found].size < MAX_ELEMENTS) {
                    output[found].elements[output[found].size++] = input[i].elements[k];
                }
            }
        } else {
            if (output_count < MAX_TUPLES) {
                output[output_count] = input[i];
                output_count++;
            }
        }
    }

    return output_count;
}

int main(void) {
    Tuple input[MAX_TUPLES] = {
        {{1, 2}, 2},
        {{1, 3}, 2},
        {{2, 4}, 2},
        {{3, 5}, 2},
        {{2, 6, 7}, 3}
    };
    
    Tuple output[MAX_TUPLES];
    int input_count = 5;
    
    int output_count = join_tuples(input, input_count, output);

    for (int i = 0; i < output_count; i++) {
        printf("(");
        for (int j = 0; j < output[i].size; j++) {
            printf("%d", output[i].elements[j]);
            if (j < output[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    return 0;
}