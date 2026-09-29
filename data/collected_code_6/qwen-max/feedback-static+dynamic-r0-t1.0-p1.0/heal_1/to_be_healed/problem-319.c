#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_five_char_words(const char *input) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status, offset = 0;

    const char *pattern = "\\b\\w{5}\\b";
    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return;
    }

    while (1) {
        status = regexec(&regex, input + offset, 1, pmatch, 0);
        if (status == REG_NOMATCH) {
            break;
        } else if (status != 0) {
            regfree(&regex);
            return;
        }

        for (int i = 0; i < 1; i++) {
            if (pmatch[i].rm_so == -1) {
                break;
            }
            printf("%.*s\n", pmatch[i].rm_eo - pmatch[i].rm_so, input + offset + pmatch[i].rm_so);
        }
        
        offset += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *input = "hello world quick brown fox jumps over the lazy dog";
    find_five_char_words(input);
    return 0;
}