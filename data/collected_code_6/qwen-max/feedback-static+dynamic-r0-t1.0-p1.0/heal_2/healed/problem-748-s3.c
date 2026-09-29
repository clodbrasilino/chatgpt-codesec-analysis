#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    char *src = str, *dest = str;
    size_t len = strlen(str);

    while (regexec(&regex, src, 1, pmatch, 0) == 0) {
        size_t distance = pmatch[0].rm_so;
        dest += memmove(dest, src, distance);
        *dest++ = ' ';
        src += distance + 1;
    }
    strcpy(dest, src);

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