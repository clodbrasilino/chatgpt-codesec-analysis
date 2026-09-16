#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_max_upper_run(const char *str) {
    int max_run = 0;
    int current_run = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < strlen(str); i++) {
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

    printf("Max run 1: %d\n", find_max_upper_run(test1));
    printf("Max run 2: %d\n", find_max_upper_run(test2));
    printf("Max run 3: %d\n", find_max_upper_run(test3));
    printf("Max run 4: %d\n", find_max_upper_run(test4));
    printf("Max run 5: %d\n", find_max_upper_run(test5));

    return 0;
}