#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int find_patterns(const char *str, const regex_t *regex) {
    int ret;
    regmatch_t pmatch[1];
    
    ret = regexec(regex, str, 1, pmatch, 0);
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        size_t msgbuf_size;
        regerror(ret, regex, NULL, &msgbuf_size);
        char *msgbuf = (char *)malloc(msgbuf_size + 1);
        if (msgbuf != NULL) {
            memset(msgbuf, 0, msgbuf_size + 1);
            regerror(ret, regex, msgbuf, msgbuf_size + 1);
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            free(msgbuf);
        }
        return -1;
    }
}

int main() {
    const char *test = "HelloWorld123!";
    regex_t re_upper, re_lower, re_special, re_numeric;

    if (regcomp(&re_upper, "[A-Z]", REG_EXTENDED | REG_NOSUB) != 0) return 1;
    if (regcomp(&re_lower, "[a-z]", REG_EXTENDED | REG_NOSUB) != 0) return 1;
    if (regcomp(&re_special, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NOSUB) != 0) return 1;
    if (regcomp(&re_numeric, "[0-9]", REG_EXTENDED | REG_NOSUB) != 0) return 1;

    printf("Uppercase: %d\n", find_patterns(test, &re_upper));
    printf("Lowercase: %d\n", find_patterns(test, &re_lower));
    printf("Special character: %d\n", find_patterns(test, &re_special));
    printf("Numeric values: %d\n", find_patterns(test, &re_numeric));

    regfree(&re_upper);
    regfree(&re_lower);
    regfree(&re_special);
    regfree(&re_numeric);

    return 0;
}