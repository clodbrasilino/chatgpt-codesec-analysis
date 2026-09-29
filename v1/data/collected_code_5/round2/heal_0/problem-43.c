#include <stdio.h>
#include <regex.h>

int matches_regex(const char* string, const char* pattern) {
    regex_t re;
    int res = regcomp(&re, pattern, REG_EXTENDED);
    if (res) {
        printf("Could not compile regex\n");
        return 0;
    }
    res = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (!res) {
        return 1;
    } else if (res == REG_NOMATCH) {
        return 0;
    } else {
        printf("There was an error running the regex\n");
        return 0;
    }
}

int main() {
    const char* string = "my_string";
    const char* pattern = "\\b[a-z]+(_[a-z]+)*\\b";
    int res = matches_regex(string, pattern);
    printf("%s matches pattern? %s\n", string, (res ? "Yes" : "No"));
    return 0;
}