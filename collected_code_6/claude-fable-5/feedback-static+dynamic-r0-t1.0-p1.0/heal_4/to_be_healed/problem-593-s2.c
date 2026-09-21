#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IP_LEN 16

int remove_leading_zeroes(const char *input, char *output, size_t output_size)
{
    unsigned int octets[4];
    size_t pos = 0;
    int octet_index;
    int written;

    if (input == NULL || output == NULL || output_size < MAX_IP_LEN) {
        return -1;
    }

    for (octet_index = 0; octet_index < 4; octet_index++) {
        unsigned long value = 0;
        int digit_count = 0;

        while (input[pos] != '\0' && isdigit((unsigned char)input[pos])) {
            value = value * 10 + (unsigned long)(input[pos] - '0');
            digit_count++;
            pos++;
            if (digit_count > 3) {
                return -1;
            }
        }

        if (digit_count == 0 || value > 255UL) {
            return -1;
        }

        octets[octet_index] = (unsigned int)value;

        if (octet_index < 3) {
            if (input[pos] != '.') {
                return -1;
            }
            pos++;
        }
    }

    if (input[pos] != '\0') {
        return -1;
    }

    written = snprintf(output, output_size, "%u.%u.%u.%u",
                       octets[0], octets[1], octets[2], octets[3]);

    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    output[written] = '\0';

    return 0;
}

int main(void)
{
    const char *tests[] = {
        "192.068.001.010",
        "001.002.003.004",
        "255.255.255.255",
        "000.000.000.000",
        "10.0.0.1",
        "256.1.1.1",
        "1.2.3",
        "abc.def.ghi.jkl"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_IP_LEN];
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    memset(result, 0, sizeof(result));

    for (i = 0; i < count; i++) {
        if (tests[i] == NULL) {
            continue;
        }
        if (remove_leading_zeroes(tests[i], result, sizeof(result)) == 0) {
            result[sizeof(result) - 1] = '\0';
            if (printf("%s -> %s\n", tests[i], result) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Invalid IP address: %s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}