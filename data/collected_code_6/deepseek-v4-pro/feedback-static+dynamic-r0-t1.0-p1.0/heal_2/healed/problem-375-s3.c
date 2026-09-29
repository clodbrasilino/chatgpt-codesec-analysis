#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int round_to_multiple(int num, int multiple) {
    if (multiple == 0) {
        return 0;
    }

    if (multiple < 0) {
        multiple = -multiple;
    }

    int half_multiple = multiple / 2;
    int remainder = num % multiple;
    if (remainder < 0) {
        remainder += multiple;
    }

    if (num > INT_MAX - half_multiple) {
        int max_safe = INT_MAX / multiple * multiple;
        if (num >= max_safe) {
            return max_safe;
        }
        if (num - max_safe >= half_multiple) {
            return max_safe + multiple > INT_MAX ? max_safe : max_safe + multiple;
        }
        return max_safe;
    }

    if (num < INT_MIN + half_multiple) {
        int min_safe = INT_MIN / multiple * multiple;
        if (num <= min_safe) {
            return min_safe;
        }
        if (min_safe - num >= half_multiple) {
            return min_safe - multiple < INT_MIN ? min_safe : min_safe - multiple;
        }
        return min_safe;
    }

    if (num > 0) {
        int quotient = (num + half_multiple) / multiple;
        if (quotient > INT_MAX / multiple) {
            return INT_MAX / multiple * multiple;
        }
        return quotient * multiple;
    } else if (num < 0) {
        int quotient = (num - half_multiple) / multiple;
        if (quotient < INT_MIN / multiple) {
            return INT_MIN / multiple * multiple;
        }
        return quotient * multiple;
    }

    return 0;
}

int main(void) {
    int num;
    int multiple;

    printf("Enter number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter multiple: ");
    if (scanf("%d", &multiple) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (multiple == 0) {
        fprintf(stderr, "Multiple cannot be zero\n");
        return EXIT_FAILURE;
    }

    printf("Result: %d\n", round_to_multiple(num, multiple));
    return EXIT_SUCCESS;
}