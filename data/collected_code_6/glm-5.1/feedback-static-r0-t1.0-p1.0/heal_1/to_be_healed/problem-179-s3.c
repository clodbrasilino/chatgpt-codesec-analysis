#include <stdio.h>
#include <stdlib.h>

int is_keith_number(int num) {
    if (num < 10) {
        return 0;
    }

    int temp = num;
    int digits = 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    int *sequence = (int *)malloc(digits * sizeof(int));
    if (sequence == NULL) {
        return 0;
    }

    temp = num;
    int sum = 0;
    for (int i = 0; i < digits; i++) {
        sequence[digits - 1 - i] = temp % 10;
        sum += temp % 10;
        temp /= 10;
    }

    /* Possible weaknesses found:
     *  The scope of the variable 'next_value' can be reduced. [variableScope]
     */
    int next_value;
    while (sum <= num) {
        if (sum == num) {
            free(sequence);
            return 1;
        }

        next_value = sum;
        for (int i = 0; i < digits - 1; i++) {
            sum -= sequence[i];
            sequence[i] = sequence[i + 1];
            sum += sequence[i];
        }
        sequence[digits - 1] = next_value;
        sum += next_value;
    }

    free(sequence);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a valid integer between 0 and 2147483647\n");
        return 1;
    }

    int num = (int)val;

    if (is_keith_number(num)) {
        printf("%d is a Keith number\n", num);
    } else {
        printf("%d is not a Keith number\n", num);
    }

    return 0;
}