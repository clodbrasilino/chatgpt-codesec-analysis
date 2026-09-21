#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_max_upper_run(const char *str, size_t max_len) {
    int max_run = 0;
    int current_run = 0;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, max_len);

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
    const char *test1 = "abcDEFghIJklmNOPQrsT";
    const char *test2 = "no_uppercase_here";
    const char *test3 = "ALLUPPERCASE";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("Max run 1: %d\n", find_max_upper_run(test1, 1024));
    printf("Max run 2: %d\n", find_max_upper_run(test2, 1024));
    printf("Max run 3: %d\n", find_max_upper_run(test3, 1024));
    printf("Max run 4: %d\n", find_max_upper_run(test4, 1024));
    printf("Max run 5: %d\n", find_max_upper_run(test5, 1024));

    return 0;
}