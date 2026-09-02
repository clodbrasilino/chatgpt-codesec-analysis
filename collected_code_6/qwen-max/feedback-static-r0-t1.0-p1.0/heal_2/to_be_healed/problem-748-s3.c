#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     *  Unused variable: buffer [unusedVariable]
     */
    char buffer[1024];
    regmatch_t pmatch[1];
    
    int reti = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        memmove(str + pmatch[0].rm_eo + 1, str + pmatch[0].rm_eo, strlen(str + pmatch[0].rm_eo) + 1);
        str[pmatch[0].rm_eo] = ' ';
        str += pmatch[0].rm_so + 1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (add_spaces_between_capital_words(str) != -1) {
        printf("%s\n", str);
    } else {
        perror("Regex error");
        exit(EXIT_FAILURE);
    }
    return 0;
}