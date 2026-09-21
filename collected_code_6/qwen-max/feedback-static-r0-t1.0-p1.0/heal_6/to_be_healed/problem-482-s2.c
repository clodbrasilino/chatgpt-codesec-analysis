#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input, size_t input_len) {
    regex_t re;
    int reti;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char msgbuf[128];

    if (regcomp(&re, "[A-Z][a-z]+", 0) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    if ((reti = regexec(&re, input, 0, NULL, 0)) == REG_NOMATCH) {
        printf("No matches found\n");
    } else if (reti != 0) {
        regerror(reti, &re, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    } else {
        regmatch_t pmatch[1];

        while (regexec(&re, input, 1, pmatch, 0) == 0) {
            for (int i = 0; i < 1; i++) {
                if (pmatch[i].rm_so == -1) {
                    break;
                }
                size_t len = pmatch[i].rm_eo - pmatch[i].rm_so;
                if (len > 0 && pmatch[i].rm_eo <= input_len) {
                    printf("%.*s\n", (int)len, input + pmatch[i].rm_so);
                    input += pmatch[i].rm_eo;
                    input_len -= pmatch[i].rm_eo;
                }
            }
        }
    }

    regfree(&re);
}

int main() {
    const char *test_str = "HelloWorld isAnExample OfPattern Matching";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test_len = strlen(test_str);
    find_sequences(test_str, test_len);
    return 0;
}