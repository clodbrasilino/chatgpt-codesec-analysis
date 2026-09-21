#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 4096

static size_t bounded_len(const char *s, size_t max)
{
    size_t n = 0U;

    if (s == NULL) {
        return 0U;
    }

    while (n < max && s[n] != '\0') {
        n++;
    }

    return n;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count01;
    long count10;

    if (s1 == NULL || s2 == NULL) {
        return -1L;
    }

    len1 = bounded_len(s1, (size_t)MAX_LEN + 1U);
    len2 = bounded_len(s2, (size_t)MAX_LEN + 1U);

    if (len1 > (size_t)MAX_LEN || len2 > (size_t)MAX_LEN) {
        return -1L;
    }

    if (len1 != len2 || len1 == 0U) {
        return -1L;
    }

    count01 = 0L;
    count10 = 0L;

    for (i = 0U; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1L;
        }
        if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        }
    }

    if (count01 != count10) {
        return -1L;
    }

    return count01;
}

static int read_line(char *buf, size_t size)
{
    size_t len;

    if (buf == NULL || size < 2U) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    buf[size - 1U] = '\0';

    len = bounded_len(buf, size);

    if (len == size - 1U && buf[len - 1U] != '\n') {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getc(stdin);
        } while (ch != '\n' && ch != EOF);
    }

    while (len > 0U && (buf[len - 1U] == '\n' || buf[len - 1U] == '\r')) {
        buf[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char a[MAX_LEN + 2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char b[MAX_LEN + 2];
    long result;
    int status;

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    status = EXIT_SUCCESS;

    if (read_line(a, sizeof(a)) != 0 || read_line(b, sizeof(b)) != 0) {
        if (printf("Not Possible\n") < 0) {
            status = EXIT_FAILURE;
        }
        if (fflush(stdout) != 0) {
            status = EXIT_FAILURE;
        }
        return status;
    }

    result = min_swaps(a, b);

    if (result < 0L) {
        if (printf("Not Possible\n") < 0) {
            status = EXIT_FAILURE;
        }
    } else {
        if (printf("%ld\n", result) < 0) {
            status = EXIT_FAILURE;
        }
    }

    if (fflush(stdout) != 0) {
        status = EXIT_FAILURE;
    }

    return status;
}