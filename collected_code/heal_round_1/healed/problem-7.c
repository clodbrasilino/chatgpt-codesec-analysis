#include <stdio.h>
#include <regex.h>
#include <string.h>

void findLongWords(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int ret;

    ret = regcomp(&regex, "\\b\\w{4,}\\b", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex\n");
        return;
    }

    const char *cur_str = str;
    while (regexec(&regex, cur_str, 1, matches, 0) == 0) {
        char word[256];
        strncpy(word, &cur_str[matches[0].rm_so], matches[0].rm_eo - matches[0].rm_so);
        word[matches[0].rm_eo - matches[0].rm_so] = '\0';
        
        printf("%s\n", word);
        
        cur_str += matches[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    const char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    findLongWords(str);

    return 0;
}