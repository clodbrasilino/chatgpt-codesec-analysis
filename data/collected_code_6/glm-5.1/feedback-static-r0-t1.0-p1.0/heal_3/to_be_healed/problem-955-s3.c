#include <stdio.h>
#include <stdlib.h>

int is_abundant(int num) {
    if (num <= 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    return sum > num;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 2 || val > 2147483647) {
        printf("Invalid input. Please provide an integer between 2 and 2147483647.\n");
        return 1;
    }
    int number = (int)val;
    if (is_abundant(number)) {
        printf("%d is abundant.\n", number);
    } else {
        printf("%d is not abundant.\n", number);
    }
    return 0;
}