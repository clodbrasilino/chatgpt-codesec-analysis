#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <errno.h>

int find_words(const char *input, char *result, size_t result_size) {
    int reti;
    int nmatch = 10;
    regex_t re;
    regmatch_t pmatch[nmatch];

    const char *pattern = "\\b\\w{4,}\\b";
    if (regcomp(&re, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    reti = regexec(&re, input, nmatch, pmatch, 0);
    if (!reti) {
        for (int i = 0; pmatch[i].rm_so != -1; i++) {
            size_t len = pmatch[i].rm_eo - pmatch[i].rm_so;
            if (len + 1 < result_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, input + pmatch[i].rm_so, len);
                result[len] = '\0';
                printf("%s ", result);
                result += len + 1;
                result_size -= len + 1;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[100];
    int res = find_words(input, result, sizeof(result));
    if (res != 0) {
        fprintf(stderr, "Error in finding words\n");
        return 1;
    }
    return 0;
}