#include <stdio.h>
#include <stdlib.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int max_estimate = n * 20; 
    int *numbers = (int *)malloc(max_estimate * sizeof(int));
    if (numbers == NULL) {
        return;
    }

    for (int i = 0; i < max_estimate; i++) {
        numbers[i] = i * 2 + 1;
    }

    int current_lucky_index = 1;
    int count = max_estimate;

    while (current_lucky_index < n) {
        if (current_lucky_index >= count) {
            break;
        }

        int step = numbers[current_lucky_index];
        int new_count = 0;

        for (int i = 0; i < count; i++) {
            if ((i + 1) % step != 0) {
                numbers[new_count++] = numbers[i];
            }
        }
        count = new_count;
        current_lucky_index++;
    }

    for (int i = 0; i < n && i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}

int main(void) {
    int n = 20;
    print_lucky_numbers(n);
    return 0;
}