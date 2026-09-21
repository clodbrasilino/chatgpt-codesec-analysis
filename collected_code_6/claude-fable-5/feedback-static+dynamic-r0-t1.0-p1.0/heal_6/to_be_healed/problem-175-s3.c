#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 4096

static size_t bounded_strlen(const char *s, size_t max)
{
    size_t i;

    for (i = 0; i < max; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return max;
}

static void trim_input(char *s)
{
    size_t len;
    size_t start = 0;

    if (s == NULL) {
        return;
    }

    len = bounded_strlen(s, MAX_INPUT_LEN);

    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }

    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }

    if (start > 0) {
        memmove(s, s + start, len - start + 1);
        len -= start;
    }

    if (len >= 2 &&
        ((s[0] == '"' && s[len - 1] == '"') ||
         (s[0] == '\'' && s[len - 1] == '\''))) {
        s[len - 1] = '\0';
        memmove(s, s + 1, len - 1);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool is_valid_parentheses(const char *s)
{
    size_t len;
    char *stack;
    size_t top = 0;
    size_t i;
    bool result = true;

    if (s == NULL) {
        return false;
    }

    len = bounded_strlen(s, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && s[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    if (len == 0) {
        return true;
    }

    stack = (char *)malloc(len);
    if (stack == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            if (top >= len) {
                result = false;
                break;
            }
            stack[top] = c;
            top++;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {
                result = false;
                break;
            }
            top--;
            if ((c == ')' && stack[top] != '(') ||
                (c == ']' && stack[top] != '[') ||
                (c == '}' && stack[top] != '{')) {
                result = false;
                break;
            }
        } else {
            result = false;
            break;
        }
    }

    if (result && top != 0) {
        result = false;
    }

    free(stack);
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    bool valid;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        buffer[0] = '\0';
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\r\n")] = '\0';

    trim_input(buffer);

    valid = is_valid_parentheses(buffer);

    if (printf("%s\n", valid ? "True" : "False") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}