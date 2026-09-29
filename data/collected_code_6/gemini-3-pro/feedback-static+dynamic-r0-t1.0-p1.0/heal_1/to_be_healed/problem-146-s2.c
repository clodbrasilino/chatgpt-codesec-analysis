#include <stdio.h>
#include <stdlib.h>

long long int calculate_ascii_sum(const char *str) {
    if (str == NULL) {
        return 0;
    }

    long long int total_ascii_value = 0;
    while (*str != '\0') {
        total_ascii_value += (unsigned char)*str;
        str++;
    }

    return total_ascii_value;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    size_t i = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
        i++;
    }

    long long int result = calculate_ascii_sum(buffer);
    printf("%lld\n", result);

    return 0;
}