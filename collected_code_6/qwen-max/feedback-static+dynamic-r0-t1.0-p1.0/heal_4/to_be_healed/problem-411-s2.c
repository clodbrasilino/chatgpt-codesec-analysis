#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char *snake_to_camel(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char output[512];
    memset(output, 0, sizeof(output));
    regex_t preg;
    regmatch_t pmatch[2];
    /* Possible weaknesses found:
     *  The scope of the variable 'nmatch' can be reduced. [variableScope]
     */
    int nmatch = 2;
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t dst = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (regexec(&preg, &input[i], nmatch, pmatch, 0) == 0) {
                output[dst++] = toupper((unsigned char)input[i + 1]);
                i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
            } else {
                output[dst++] = input[i];
            }
            if (dst >= sizeof(output) - 1) {
                break;
            }
        }
        regfree(&preg);
    }
    return output;
}

bool test_snake_to_camel(const char *input, const char *expected) {
    char *result = snake_to_camel(input);
    return strcmp(result, expected) == 0;
}

int main() {
    if (!test_snake_to_camel("android_tv", "AndroidTv")) {
        printf("Test 0 failed\n");
    }
    if (!test_snake_to_camel("apple_watch", "AppleWatch")) {
        printf("Test 1 failed\n");
    }
    if (!test_snake_to_camel("google_pixel", "GooglePixel")) {
        printf("Test 2 failed\n");
    }

    const char *snake = "this_is_snake_case";
    char *camel = snake_to_camel(snake);
    printf("Camel case: %s\n", camel);

    return 0;
}