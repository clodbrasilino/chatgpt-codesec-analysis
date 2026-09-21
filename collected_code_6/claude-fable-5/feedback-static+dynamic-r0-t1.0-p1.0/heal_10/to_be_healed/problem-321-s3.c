#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t count_digits(size_t n)
{
    size_t d = 1;

    while (n >= 10) {
        n /= 10;
        d++;
    }
    return d;
}

static size_t write_number(char *dst, size_t avail, size_t n)
{
    size_t d = count_digits(n);
    size_t i = d;

    if (d > avail) {
        return 0;
    }

    while (i > 0) {
        dst[i - 1] = (char)('0' + (n % 10));
        n /= 10;
        i--;
    }
    return d;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected '123456789101110987654321', got (null)
  */

char *find_demlo(const char *str)
{
    size_t len;
    size_t i;
    size_t pos;
    size_t total;
    size_t written;
    size_t n;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    if (len == 0) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '1') {
            return NULL;
        }
    }

    n = len;

    total = 0;
    for (i = 1; i <= n; i++) {
        total += count_digits(i);
    }
    for (i = n; i > 1; i--) {
        total += count_digits(i - 1);
    }

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 1; i <= n; i++) {
        written = write_number(result + pos, total - pos, i);
        if (written == 0) {
            free(result);
            return NULL;
        }
        pos += written;
    }
    for (i = n; i > 1; i--) {
        written = write_number(result + pos, total - pos, i - 1);
        if (written == 0) {
            free(result);
            return NULL;
        }
        pos += written;
    }

    result[pos] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    const char *input;
    char *demlo;

    if (argc > 1) {
        input = argv[1];
    } else {
        input = "1111";
    }

    demlo = find_demlo(input);
    if (demlo == NULL) {
        fprintf(stderr, "invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", demlo);
    free(demlo);
    return EXIT_SUCCESS;
}