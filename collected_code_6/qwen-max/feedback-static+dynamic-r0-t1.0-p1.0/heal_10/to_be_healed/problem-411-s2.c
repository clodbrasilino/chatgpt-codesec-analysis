#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdbool.h>

char *snake_to_camel(const char *input, char *output, size_t output_size) {
    if (output_size == 0) return output;
    *output = '\0';
    regex_t preg;
    regmatch_t pmatch[2];
    int nmatch = 2;
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) != 0) return output;
    size_t dst = 0;
    for (int i = 0; input[i] != '\0' && dst < output_size - 1; ++i) {
        if (regexec(&preg, &input[i], nmatch, pmatch, 0) == 0) {
            output[dst++] = toupper((unsigned char)input[i + 1]);
            i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
        } else {
            output[dst++] = input[i];
        }
    }
    output[dst] = '\0';
    regfree(&preg);
    return output;
}

bool test_snake_to_camel(const char *input, const char *expected, size_t buffer_size) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len + 1 > buffer_size) return false;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[buffer_size];
    memset(output, 0, sizeof(output));
    char *result = snake_to_camel(input, output, buffer_size);
    return strcmp(result, expected) == 0;
}

int main() {
    if (!test_snake_to_camel("android_tv", "AndroidTv", 512)) {
        printf("Test 0 failed\n");
    }
    if (!test_snake_to_camel("apple_watch", "AppleWatch", 512)) {
        printf("Test 1 failed\n");
    }
    if (!test_snake_to_camel("google_pixel", "GooglePixel", 512)) {
        printf("Test 2 failed\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'snake="this_is_snake_case"', assigned value is "this_is_snake_case"
     */
    const char *snake = "this_is_snake_case";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'strlen(snake)+1>512' is always false [knownConditionTrueFalse]
     *  Condition 'strlen(snake)+1>512' is always false
     */
    if (strlen(snake) + 1 > 512) return 1;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char camel[513];
    memset(camel, 0, sizeof(camel));
    char *camel_result = snake_to_camel(snake, camel, 512);
    printf("Camel case: %s\n", camel_result);

    return 0;
}