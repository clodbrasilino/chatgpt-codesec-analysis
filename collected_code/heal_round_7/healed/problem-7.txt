#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 256

void findLongWords(const char *str, size_t str_length) {
    regex_t regex;
    regmatch_t matches[1];

    if (regcomp(&regex, "\\b\\w{4,}\\b", REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return;
    }

    const char *cur_str = str;
    while (regexec(&regex, cur_str, 1, matches, 0) == 0) {
        int length = matches[0].rm_eo - matches[0].rm_so;
        char *word = (char*)calloc(length + 1, sizeof(char));

        if(word == NULL) {
            printf("Couldn't allocate memory for word\n");
            regfree(&regex);
            return;
        }

        if (cur_str + matches[0].rm_so + length <= str + str_length){
            memmove(word, &cur_str[matches[0].rm_so], length);
            word[length] = '\0';
        } else {
            printf("Substring out of range\n");
            free(word);
            regfree(&regex);
            return;
        }

        printf("%s\n", word);

        free(word);
        cur_str += matches[0].rm_eo;
    }
    
    regfree(&regex);
}

int main() {
    const char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    size_t str_length = sizeof(str) / sizeof(char);
    findLongWords(str, str_length);

    return 0;
}