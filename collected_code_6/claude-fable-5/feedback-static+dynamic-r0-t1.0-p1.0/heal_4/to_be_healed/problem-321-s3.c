#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t count_digits(size_t n)
{
    size_t d = 1;

    while (n >= 10) {
        n /= 10;
        d++;
    }
    return d;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected '12345654321', got <no output>
  *  test case 1 failed: expected '1234321', got <no output>
  *  test case 2 failed: expected '123456789101110987654321', got <no output>
  */

char *find_demlo(const char *str)
{
    size_t len;
    size_t i;
    size_t pos;
    size_t total;
    char *result;
    int written;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0 || len > 127) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    total = 0;
    for (i = 1; i <= len; i++) {
        total += 2 * count_digits(i);
    }
    total -= count_digits(len);

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= len; i++) {
        written = snprintf(result + pos, total + 1 - pos, "%zu", i);
        if (written < 0 || (size_t)written > total - pos) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
    }

    for (i = len - 1; i >= 1; i--) {
        written = snprintf(result + pos, total + 1 - pos, "%zu", i);
        if (written < 0 || (size_t)written > total - pos) {
            free(result);
            return NULL;
        }
        pos += (size_t)written;
        if (i == 1) {
            break;
        }
    }

    result[pos] = '\0';

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *demlo;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = '\0';

    demlo = find_demlo(input);
    if (demlo == NULL) {
        fprintf(stderr, "Invalid input: must be a repunit of ones\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", demlo);
    fflush(stdout);
    free(demlo);

    return EXIT_SUCCESS;
}