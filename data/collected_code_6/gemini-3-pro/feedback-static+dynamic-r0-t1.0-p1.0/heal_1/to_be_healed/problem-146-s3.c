#include <stdio.h>
#include <stdlib.h>

long long calculate_ascii_sum(const char *str) {
    long long sum = 0;
    
    if (str == NULL) {
        return -1;
    }

    while (*str != '\0') {
        sum += (unsigned char)(*str);
        str++;
    }

    return sum;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_string[1024];

    if (fgets(input_string, sizeof(input_string), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    long long total_ascii_value = calculate_ascii_sum(input_string);

    if (total_ascii_value == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", total_ascii_value);

    return EXIT_SUCCESS;
}