#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U
 /* Possible weaknesses found:
  *  test case 1 failed: expected 3, got <no output>
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  */

size_t length_of_last_word(const char *s)
{
    size_t len;
    size_t end;
    size_t count;

    if (s == NULL) {
        return 0U;
    }

    len = strnlen(s, MAX_INPUT_LEN);
    if (len == 0U) {
        return 0U;
    }

    end = len;
    while (end > 0U && isspace((unsigned char)s[end - 1U])) {
        end--;
    }

    count = 0U;
    while (end > 0U && !isspace((unsigned char)s[end - 1U])) {
        count++;
        end--;
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    size_t result;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        buffer[0] = '\0';
    }

    result = length_of_last_word(buffer);

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}