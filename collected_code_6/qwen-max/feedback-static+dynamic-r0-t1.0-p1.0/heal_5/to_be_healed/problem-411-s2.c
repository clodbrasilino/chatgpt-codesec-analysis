#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got ADODTv
  *  test case 2 failed: expected 'AppleWatch', got APEWatch
  *  test case 1 failed: expected 'GooglePixel', got GOL_Pixel
  */

char *snake_to_camel(const char *input) {
    static char output[512];
    memset(output, 0, sizeof(output));
    regex_t preg;
    regmatch_t pmatch[2];
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t dst = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (i == 0 || input[i-1] == '_') {
                output[dst++] = toupper((unsigned char)input[i]);
            } else {
                if (regexec(&preg, &input[i], 2, pmatch, 0) == 0) {
                    output[dst++] = toupper((unsigned char)input[i+1]);
                    i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
                } else {
                    output[dst++] = input[i];
                }
            }
        }
        regfree(&preg);
    }
    return output;
}

int main() {
    const char *test0 = "android_tv";
    const char *test1 = "google_pixel";
    const char *test2 = "apple_watch";

    char *camel0 = snake_to_camel(test0);
    char *camel1 = snake_to_camel(test1);
    char *camel2 = snake_to_camel(test2);

    printf("Camel case 0: %s\n", camel0);
    printf("Camel case 1: %s\n", camel1);
    printf("Camel case 2: %s\n", camel2);

    return 0;
}