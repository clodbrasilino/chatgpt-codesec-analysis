#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    static char output[512];
    memset(output, 0, sizeof(output));
    size_t dst = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        if (i == 0 || (i > 0 && input[i-1] == '_')) {
            output[dst++] = toupper((unsigned char)input[i]);
        } else {
            output[dst++] = input[i];
        }
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