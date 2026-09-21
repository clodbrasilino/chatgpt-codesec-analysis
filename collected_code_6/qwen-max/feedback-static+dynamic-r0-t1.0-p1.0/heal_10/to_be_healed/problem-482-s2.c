#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input) {
    regex_t re;
    int reti;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char msgbuf[100];

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
        const char *current_input = input;

        while (1) {
            regmatch_t pmatch;
            if (regexec(&re, current_input, 1, &pmatch, 0) != 0) {
                break;
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (pmatch.rm_so == (size_t)-1 || pmatch.rm_eo > strlen(input)) {
                break;
            }
            const char *start = current_input + pmatch.rm_so;
            printf("%.*s\n", (int)(pmatch.rm_eo - pmatch.rm_so), start);
            current_input += pmatch.rm_eo;
        }
    }
    regfree(&re);
}

int main() {
    const char *test_str = "HelloWorld isAnExample OfPattern Matching";
    find_sequences(test_str);
    return 0;
}