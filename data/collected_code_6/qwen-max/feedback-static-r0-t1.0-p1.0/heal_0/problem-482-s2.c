#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input) {
    regex_t re;
    int reti;
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
        regmatch_t pmatch[1];
        
        while (regexec(&re, input, 1, pmatch, 0) == 0) {
            for (int i = 0; i < 1; i++) {
                if (pmatch[i].rm_so == -1) {
                    break;
                }
                printf("%.*s\n", pmatch[i].rm_eo - pmatch[i].rm_so, input + pmatch[i].rm_so);
                input += pmatch[i].rm_eo;
            }
        }
    }

    regfree(&re);
}

int main() {
    const char *test_str = "HelloWorld isAnExample OfPattern Matching";
    find_sequences(test_str);
    return 0;
}