#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char *regreplace(const char *str, regex_t *regex, const char *replacement, int cflags){
    char *result;
    size_t maxMatchSize;
    regmatch_t matchPointer;
    const char *cursor;
    char *resCursor;

    if (regexec(regex, str, 1, &matchPointer, 0) != 0) {
        return strdup(str);
    }
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    maxMatchSize = strlen(str) + strlen(replacement) + 1;

    result = malloc(maxMatchSize);
    if (result == NULL) {
        return NULL;
    }    
    cursor = str;
    resCursor = result;

    while (*cursor != '\0') {
        if (!regexec(regex, cursor, 1, &matchPointer, 0)) {
            int size = matchPointer.rm_eo - matchPointer.rm_so;
            
            cursor += matchPointer.rm_so;
            resCursor += matchPointer.rm_so;

            /* Possible weaknesses found:
             *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
             */
            strcpy(resCursor, replacement);
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            resCursor += strlen(replacement);
            cursor += size;
        } 
        else {
            *resCursor++ = *cursor++;
        }
    }
    *resCursor = '\0';
    return result;
}

void removeWhitespace(char *str) {
    regex_t regex;
    const char *pattern = "[[:space:]]";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex pattern\n");
        return;
    }
    
    char *output = regreplace(str, &regex, "", REG_EXTENDED);
    printf("%s", output);
    regfree(&regex);
    free(output);
}

int main() {
    char str[] = "Hello World! How are you?";
    removeWhitespace(str);
    return 0;
}