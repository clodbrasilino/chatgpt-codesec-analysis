#include <stdio.h>
#include <string.h>

int min_flips_to_alternate(const char *str, size_t len) {
    int flips_start0 = 0;
    int flips_start1 = 0;

    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != '0') flips_start0++;
            if (str[i] != '1') flips_start1++;
        } else {
            if (str[i] != '1') flips_start0++;
            if (str[i] != '0') flips_start1++;
        }
    }

    return flips_start0 < flips_start1 ? flips_start0 : flips_start1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1001];

    printf("Enter binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("0\n");
        return 0;
    }

    if (len >= sizeof(input)) {
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            fprintf(stderr, "Invalid input: only '0' and '1' allowed\n");
            return 1;
        }
    }

    int result = min_flips_to_alternate(input, len);
    printf("%d\n", result);

    return 0;
}