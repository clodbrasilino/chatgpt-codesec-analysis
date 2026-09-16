#include <stdio.h>
#include <ctype.h>
#include <string.h>

int find_max_uppercase_run(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_run = 0;
    int current_run = 0;

    for (size_t i = 0; str[i] != '\0'; ++i) {
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
    const char *test_str = "abcABCDefgHIJKLMnoP";
    int max_run = find_max_uppercase_run(test_str);
    printf("%d\n", max_run);

    return 0;
}