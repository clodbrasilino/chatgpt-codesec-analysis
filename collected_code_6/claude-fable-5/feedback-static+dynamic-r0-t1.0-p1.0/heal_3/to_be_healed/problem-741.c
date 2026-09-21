#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STR_LEN 4096
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool all_chars_same(const char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, MAX_STR_LEN);
    if (len == 0) {
        return false;
    }

    for (i = 1; i < len; i++) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_STR_LEN + 2];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("False\n");
        return 0;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (all_chars_same(buffer)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}