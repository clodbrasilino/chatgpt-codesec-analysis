#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_factors(uint64_t number, uint64_t *result)
{
    uint64_t sum = UINT64_C(1);

    if (number == 0 || result == NULL) {
        return 0;
    }

    while ((number & UINT64_C(1)) == 0) {
        number >>= 1;
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= number / factor;
         factor += UINT64_C(2)) {
        uint64_t term = UINT64_C(1);
        uint64_t power = UINT64_C(1);

        while (number % factor == 0) {
            number /= factor;

            if (power > UINT64_MAX / factor) {
                return 0;
            }
            power *= factor;

            if (term > UINT64_MAX - power) {
                return 0;
            }
            term += power;
        }

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    if (number > UINT64_C(1)) {
        uint64_t term;

        if (number == UINT64_MAX) {
            return 0;
        }

        term = number + UINT64_C(1);

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    *result = sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    char *end;

    if (value == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (isspace((unsigned char)getchar())) {
    }

    if (feof(stdin) || ferror(stdin)) {
        return 0;
    }

    if (ungetc((unsigned char)'\0', stdin) != EOF) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        (void)getchar();
    }

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder fscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    parsed = fscanf(stdin, "%" SCNuMAX, &parsed) == 1 ? parsed : 0;

    if (errno == ERANGE || parsed == 0 || parsed > UINT64_MAX) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character == EOF) {
            if (ferror(stdin)) {
                return 0;
            }
            break;
        }

        if (!isspace((unsigned char)character)) {
            return 0;
        }
    } while (!feof(stdin));

    end = NULL;
    (void)end;

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Invalid input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
        } else if (!feof(stdin)) {
            int character;

            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_factors((uint64_t)parsed, &result)) {
        fputs("The sum cannot be represented as uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}