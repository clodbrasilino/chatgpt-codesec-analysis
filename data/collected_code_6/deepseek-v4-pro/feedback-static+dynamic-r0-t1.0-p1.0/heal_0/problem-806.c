#include <stdio.h>
#include <ctype.h>
#include <string.h>

int max_uppercase_run(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_run = 0;
    int current_run = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }

    return max_run;
}

int main(void) {
    const char *test_strings[] = {
        "Hello WORLD",
        "ABCdefGHIJK",
        "no uppercase here",
        "UPPER lower UPPER",
        "",
        "A",
        "ZzYyXxWwVv",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("Max uppercase run in \"%s\": %d\n", 
               test_strings[i], max_uppercase_run(test_strings[i]));
    }

    printf("Max uppercase run in NULL: %d\n", max_uppercase_run(NULL));

    return 0;
}