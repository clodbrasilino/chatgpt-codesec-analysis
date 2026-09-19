#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t match[1];
    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;

    if (regcomp(&regex, "\\b\\w+ly\\b", REG_EXTENDED|REG_NOSUB) != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    const size_t len = strlen(sentence);
    for (size_t i = 0; i <= len; i++) {
        reti = regexec(&regex, sentence + i, 1, match, 0);
        if (!reti) {
            match[0].rm_so += i;
            match[0].rm_eo += i;
            printf("Adverb: %.*s at position %ld to %ld\n", match[0].rm_eo - match[0].rm_so, sentence + match[0].rm_so, match[0].rm_so, match[0].rm_eo - 1);
            i += match[0].rm_eo - match[0].rm_so - 1;
        } else if (reti == REG_NOMATCH) {
            continue;
        } else {
            regfree(&regex);
            return;
        }
    }

    regfree(&regex);
}

int main() {
    const char *sentence = "He quickly and quietly walked away.";
    find_adverbs(sentence);
    return 0;
}