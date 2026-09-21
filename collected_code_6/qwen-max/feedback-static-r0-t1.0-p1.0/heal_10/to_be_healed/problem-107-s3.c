#include <stdio.h>
#include <inttypes.h>
#include <string.h>

int count_hex_numbers(int from, int to) {
    if (from > to) return 0;
    int count = 0;
    for (int i = from; i <= to; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buf[32];
        snprintf(buf, sizeof(buf), "%x", i);
        size_t len = strnlen(buf, sizeof(buf) - 1);
        if (strspn(buf, "0123456789abcdef") == len && len > 0) count++;
    }
    return count;
}

int main() {
    int from, to;
    printf("Enter the range (from to): ");
    if (scanf("%d %d", &from, &to) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int result = count_hex_numbers(from, to);
    printf("Count: %d\n", result);
    return 0;
}