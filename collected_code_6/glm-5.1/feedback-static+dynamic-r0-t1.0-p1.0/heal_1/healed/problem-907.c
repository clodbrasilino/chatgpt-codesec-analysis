#include <stdio.h>
#include <stdlib.h>

int* generate_lucky_numbers(int limit) {
    int* arr = (int*)malloc((limit + 1) * sizeof(int));
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i <= limit; i++) {
        arr[i] = i;
    }

    for (int step = 2; step <= limit;) {
        int surviving = 0;
        for (int i = 1; i <= limit; i++) {
            if (arr[i] != 0) {
                surviving++;
                if ((surviving % step) == 0) {
                    arr[i] = 0;
                }
            }
        }

        int next_step = 0;
        for (int i = step + 1; i <= limit; i++) {
            if (arr[i] != 0) {
                next_step = arr[i];
                break;
            }
        }

        step = next_step;
        if (step == 0) {
            break;
        }
    }

    return arr;
}

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int limit = n * 10;
    int* lucky_arr = NULL;

    while (1) {
        free(lucky_arr);
        lucky_arr = generate_lucky_numbers(limit);
        if (lucky_arr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }

        int count = 0;
        for (int i = 1; i <= limit; i++) {
            if (lucky_arr[i] != 0) {
                count++;
            }
        }

        if (count >= n) {
            break;
        }

        limit *= 2;
    }

    int printed = 0;
    for (int i = 1; i <= limit && printed < n; i++) {
        if (lucky_arr[i] != 0) {
            printf("%d ", lucky_arr[i]);
            printed++;
        }
    }
    printf("\n");

    free(lucky_arr);
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return 1;
    }

    print_lucky_numbers((int)val);

    return 0;
}