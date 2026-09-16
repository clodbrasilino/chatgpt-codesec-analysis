#include <stdio.h>
#include <stdlib.h>

int isInSequence(long long a, long long b, long long c, long long num) {
    if (c == 0) {
        if (a == num) {
            return 1;
        }
        if (b == num) {
            return 1;
        }
        return 0;
    }
    if ((c > 0 && num < a) || (c < 0 && num > a)) {
        return 0;
    }
    if ((num - a) % c != 0) {
        return 0;
    }
    long long n = (num - a) / c;
    if (n >= 0) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <a> <b> <c> <num>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2, *endptr3, *endptr4;
    long long a = strtoll(argv[1], &endptr1, 10);
    long long b = strtoll(argv[2], &endptr2, 10);
    long long c = strtoll(argv[3], &endptr3, 10);
    long long num = strtoll(argv[4], &endptr4, 10);
    
    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0' || *endptr4 != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (a != b) {
        c = b - a;
    }

    int result = isInSequence(a, b, c, num);
    if (result) {
        printf("%lld is in the sequence\n", num);
    } else {
        printf("%lld is not in the sequence\n", num);
    }
    return EXIT_SUCCESS;
}