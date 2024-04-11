#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int extract_max_value(const char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    char* pattern = "([0-9]+)";
    int max = 0;

    regcomp(&regex, pattern, REG_EXTENDED);
    const char *p = str;
    while (!regexec(&regex, p, nmatch, pmatch, 0)) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        char* match = malloc(end - start + 1);
        strncpy(match, p + start, end - start);
        match[end - start] = '\0';
        int value = atoi(match);
        if (value > max) {
            max = value;
        }
        free(match);
        p += end;
    }
    regfree(&regex);
    return max;
}

int main() {
    const char *str = "abc123def456ghi789";
    int max = extract_max_value(str);
    printf("Max value: %d\n", max);
    return 0;
}