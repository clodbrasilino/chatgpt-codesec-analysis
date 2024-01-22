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
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        size_t length = end - start < strlen(string) - start ? end - start : strlen(string) - start;
        char* extractedValue = malloc(sizeof(char) * (length + 1));

        if (extractedValue) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(extractedValue, string + start, length);
            extractedValue[length] = '\0'; 
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