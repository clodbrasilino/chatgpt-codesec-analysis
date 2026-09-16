#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

/* Possible weaknesses found:
 *  'snake_to_camel' declared here
 */
char *snake_to_camel(const char *input) {
    static char output[512];
    memset(output, 0, sizeof(output));
    regex_t preg;
    regmatch_t pmatch[2];
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t dst = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (regexec(&preg, &input[i], 2, pmatch, 0) == 0) {
                output[dst++] = toupper((unsigned char)input[i+1]);
                i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
            } else {
                output[dst++] = input[i];
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
    /* Possible weaknesses found:
     *  did you mean 'snake_to_camel'?
     *  implicit declaration of function 'snake_to_camle'; did you mean 'snake_to_camel'? [-Wimplicit-function-declaration]
     *  incompatible integer to pointer conversion initializing 'char *' with an expression of type 'int' [-Wint-conversion]
     *  call to undeclared function 'snake_to_camle'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  initialization of 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    char *camel1 = snake_to_camle(test1);
    char *camel2 = snake_to_camel(test2);

    printf("Camel case 0: %s\n", camel0);
    printf("Camel case 1: %s\n", camel1);
    printf("Camel case 2: %s\n", camel2);

    return 0;
}