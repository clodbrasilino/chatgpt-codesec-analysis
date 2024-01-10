#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void extractValues(const char* string) {
    regex_t regex;
    regmatch_t matches[1];
    const char* pattern = "\"([^\"]+)\""; 

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex pattern\n");
        return;
    }

    int result = regexec(&regex, string, 1, matches, 0);
    if (result == 0) {
        int start = matches[0].rm_so + 1;
        int end = matches[0].rm_eo - 1;
        char* extractedValue = (char *)malloc(sizeof(char) * (end - start + 2));

        if (extractedValue) {
            strncpy(extractedValue, string + start, end - start + 1);
            extractedValue[end - start + 1] = '\0';
            printf("%s\n", extractedValue);
            free(extractedValue);
        } else {
            printf("Memory allocation failed.\n");
        }
    } else if (result == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        printf("Error executing regex\n");
    }

    regfree(&regex);
}

int main() {
    char string[] = "The value is \"example\".";
    extractValues(string);
    return 0;
}