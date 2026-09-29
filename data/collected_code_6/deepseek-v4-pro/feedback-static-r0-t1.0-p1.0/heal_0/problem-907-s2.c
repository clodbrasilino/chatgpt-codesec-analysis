#include <stdio.h>
#include <stdlib.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int *numbers = (int *)malloc(n * sizeof(int));
    if (numbers == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }

    int step = 2;
    int remaining = n;

    while (step <= remaining) {
        int write_index = 0;
        for (int i = 0; i < remaining; i++) {
            if ((i + 1) % step != 0) {
                numbers[write_index] = numbers[i];
                write_index++;
            }
        }
        remaining = write_index;
        step++;
    }

    for (int i = 0; i < remaining; i++) {
        printf("%d", numbers[i]);
        if (i < remaining - 1) {
            printf(" ");
        }
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