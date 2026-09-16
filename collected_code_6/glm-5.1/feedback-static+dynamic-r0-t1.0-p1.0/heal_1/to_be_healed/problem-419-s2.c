#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int calculate(int *numbers, size_t length) {
    if (numbers == NULL || length == 0) {
        return 0;
    }

    long long sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += llround(numbers[i]);
    }

    return (int)(sum * length);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t length = (size_t)argc - 1;
    int *numbers = (int *)malloc(length * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    for (size_t i = 0; i < length; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0') {
            free(numbers);
            return 1;
        }
        if (val > 2147483647 || val < -2147483648) {
            free(numbers);
            return 1;
        }
        numbers[i] = (int)val;
    }

    int result = calculate(numbers, length);
    printf("%d\n", result);

    free(numbers);
    return 0;
}