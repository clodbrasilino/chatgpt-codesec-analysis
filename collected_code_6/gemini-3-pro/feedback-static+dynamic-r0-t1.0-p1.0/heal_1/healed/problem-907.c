#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_lucky_numbers(int n) {
    if (n <= 0 || n > INT_MAX / 10) {
        return;
    }

    int max_size = n * 10;
    if (max_size < 100) {
        max_size = 100;
    }

    int *numbers = (int *)malloc(max_size * sizeof(int));
    if (numbers == NULL) {
        return; 
    }

    for (int i = 0; i < max_size; i++) {
        numbers[i] = i * 2 + 1;
    }

    int count = max_size;
    int step_index = 1;

    while (step_index < count) {
        int step = numbers[step_index];
        if (step > count) {
            break;
        }

        int new_count = 0;
        for (int i = 0; i < count; i++) {
            if ((i + 1) % step != 0) {
                numbers[new_count++] = numbers[i];
            }
        }
        count = new_count;
        step_index++;
    }

    for (int i = 0; i < n && i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    print_lucky_numbers(n);

    return EXIT_SUCCESS;
}