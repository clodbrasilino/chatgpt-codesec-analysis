#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char* snake_to_camel(const char *input) {
    regex_t re;
    regmatch_t match[2];
    const char *p = input;
    char *output, *q;
    size_t len;

    if (regcomp(&re, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0)
        return NULL;

    len = strnlen(input, 1000);
    output = malloc(len + 2); // Allocate enough space for the potential uppercase letter
    if (!output)
        return NULL;
    q = output;

    if (islower((unsigned char)*p)) {
        *q++ = toupper((unsigned char)*p++);
    } else {
        *q++ = *p++;
    }

    while (*p) {
        if (regexec(&re, p, 2, match, 0) == 0 && match[1].rm_so == 0 && p[1] != '\0') {
            *q++ = toupper((unsigned char)p[1]);
            p += 2;
        } else {
            *q++ = *p++;
        }
    }
    *q = '\0';

    regfree(&re);
    return output;
}

int main() {
    const char *test_cases[] = {"android_tv", "google_pixel", "apple_watch"};
    const char *expected_outputs[] = {"AndroidTv", "GooglePixel", "AppleWatch"};
    int num_test_cases = 3;

    for (int i = 0; i < num_test_cases; i++) {
        char *output = snake_to_camel(test_cases[i]);

        if (output) {
            printf("Converted: %s\n", output);
            if (strcmp(output, expected_outputs[i]) == 0) {
                printf("Test case %d passed.\n", i);
            } else {
                printf("Test case %d failed. Expected: %s, Got: %s\n", i, expected_outputs[i], output);
            }
            free(output);
        } else {
            fprintf(stderr, "Error converting string for test case %d.\n", i);
        }
    }

    return 0;
}