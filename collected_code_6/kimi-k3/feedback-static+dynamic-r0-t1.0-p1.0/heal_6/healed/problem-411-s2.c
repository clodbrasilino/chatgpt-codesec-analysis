#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    char *output;
    size_t output_len;
    size_t input_len;
    size_t i;
    int ret;
    int capitalize_next;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 1024);
    if (input_len == 1024) {
        return NULL;
    }

    output_len = input_len + 1;
    output = (char *)malloc(output_len);
    if (output == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        free(output);
        return NULL;
    }

    i = 0;
    cursor = input;
    capitalize_next = 1;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 2, matches, 0);
        if (ret == 0 && matches[1].rm_so >= 0) {
            size_t prefix_len = (size_t)matches[0].rm_so;
            char upper_char;
            size_t j;

            if (i + prefix_len >= output_len) {
                regfree(&regex);
                free(output);
                return NULL;
            }

            if (prefix_len > 0) {
                if (prefix_len > output_len - i - 1) {
                    regfree(&regex);
                    free(output);
                    return NULL;
                }
                for (j = 0; j < prefix_len; j++) {
                    if (capitalize_next && cursor[j] >= 'a' && cursor[j] <= 'z') {
                        output[i] = (char)(cursor[j] - 'a' + 'A');
                        capitalize_next = 0;
                    } else {
                        output[i] = cursor[j];
                        if (cursor[j] != '_') {
                            capitalize_next = 0;
                        }
                    }
                    i++;
                }
            }

            upper_char = cursor[matches[1].rm_so];
            if (upper_char >= 'a' && upper_char <= 'z') {
                upper_char = (char)(upper_char - 'a' + 'A');
            }

            if (i + 1 >= output_len) {
                regfree(&regex);
                free(output);
                return NULL;
            }

            output[i] = upper_char;
            i++;
            capitalize_next = 0;

            cursor += matches[0].rm_eo;
        } else {
            size_t remaining = strlen(cursor);
            size_t j;

            if (i + remaining >= output_len) {
                regfree(&regex);
                free(output);
                return NULL;
            }

            if (remaining > 0) {
                if (remaining > output_len - i - 1) {
                    regfree(&regex);
                    free(output);
                    return NULL;
                }
                for (j = 0; j < remaining; j++) {
                    if (capitalize_next && cursor[j] >= 'a' && cursor[j] <= 'z') {
                        output[i] = (char)(cursor[j] - 'a' + 'A');
                        capitalize_next = 0;
                    } else {
                        output[i] = cursor[j];
                        if (cursor[j] != '_') {
                            capitalize_next = 0;
                        }
                    }
                    i++;
                }
            }
            break;
        }
    }

    output[i] = '\0';
    regfree(&regex);
    return output;
}

int main(void)
{
    const char *input = "hello_world_this_is_c";
    char *result = snake_to_camel(input);

    if (result == NULL) {
        return 1;
    }

    printf("%s\n", result);
    free(result);
    return 0;
}