#include <stdio.h>
#include <stdlib.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int max_size = 30000;
    int *sequence = (int *)malloc(max_size * sizeof(int));
    if (sequence == NULL) {
        return;
    }

    int current_length = 0;
    for (int i = 1; i <= max_size; i += 2) {
        if (current_length < max_size) {
            sequence[current_length++] = i;
        }
    }

    int step = 1;
    while (step < current_length) {
        int survive = step;
        int next_step = sequence[survive - 1];

        if (next_step > current_length) {
            break;
        }

        int write_index = 0;
        for (int read_index = 0; read_index < current_length; read_index++) {
            if ((read_index + 1) % next_step != 0) {
                sequence[write_index++] = sequence[read_index];
            }
        }

        current_length = write_index;
        step = survive + 1;
    }

    for (int i = 0; i < n; i++) {
        if (i < current_length) {
            printf("%d ", sequence[i]);
        } else {
            break;
        }
    }
    printf("\n");

    free(sequence);
}

int main(int argc, char *argv[]) {
    int n = 20;
    
    if (argc > 1) {
        long val = strtol(argv[1], NULL, 10);
        if (val > 0 && val <= 1000) {
            n = (int)val;
        }
    }

    print_lucky_numbers(n);

    return 0;
}