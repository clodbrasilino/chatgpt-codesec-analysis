#include <stdio.h>
#include <regex.h>
#include <string.h>

int find_words(const char *input, char *result, size_t result_size) {
    int reti;
    int nmatch = 10; 
    regex_t re;
    regmatch_t pmatch[nmatch];

    const char *pattern = "\\b\\w{4,}\\b";
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return -1;
    }

    reti = regexec(&re, input, nmatch, pmatch, 0);
    if (!reti) {
        for (int i = 0; pmatch[i].rm_so != -1; i++) {
            size_t match_len = pmatch[i].rm_eo - pmatch[i].rm_so;
            if (match_len + 1 < result_size) {
                memcpy(result, input + pmatch[i].rm_so, match_len);
                result[match_len] = '\0';
                printf("%s ", result);
            } else {
                return -1;
            }
        }
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }

    regfree(&re);
    return 0;
}

int main() {
    const char *input = "This is a test string with some words longer than four characters";
    char result[50];
    int res = find_words(input, result, sizeof(result));
    if (res != 0) {
        fprintf(stderr, "Error in finding words\n");
        return 1;
    }
    return 0;
}