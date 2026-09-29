#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_lucky_numbers(int n) {
    if (n <= 0 || n > INT_MAX / 10) {
        return;
    }

    int max_val = n * 10;
    int *numbers = (int *)malloc(max_val * sizeof(int));
    if (numbers == NULL) {
        return;
    }

    for (int i = 0; i < max_val; i++) {
        numbers[i] = i * 2 + 1;
    }

    int count = max_val;
    int step_index = 1;

    while (step_index < count && step_index < n) {
        int step = numbers[step_index];
        if (step <= 0) {
            break;
        }

        int write_index = 0;
        for (int read_index = 0; read_index < count; read_index++) {
            if ((read_index + 1) % step != 0) {
                numbers[write_index++] = numbers[read_index];
            }
        }
        count = write_index;
        step_index++;
    }

    int limit = (n < count) ? n : count;
    for (int i = 0; i < limit; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    print_lucky_numbers(n);
    return 0;
}