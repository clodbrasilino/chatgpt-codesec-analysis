#include <stdio.h>
#include <regex.h>
#include <string.h>

int check_start_end_same_char(const char *str) {
    regex_t re;
    int ret;

    if (regcomp(&re, "^(.).*\\1$", REG_EXTENDED) != 0)
        return 0;

    ret = regexec(&re, str, 0, NULL, 0);

    regfree(&re);

    return ret == 0;
}

int main() {
    const char *strings[] = {"helloh", "worldw", "abc", "bab", "a"};

    for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); ++i) {
        printf("%s: %s\n", strings[i], check_start_end_same_char(strings[i]) ? "True" : "False");
    }

    return 0;
}