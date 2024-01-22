#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char *regreplace(const char *str, regex_t *regex, const char *replacement, int cflags) {
    if(!str || !*str || !replacement) return NULL;
    char *result;
    size_t maxMatchSize;
    regmatch_t matchPointer;
    const char *cursor;
    char *resCursor;
    if (regexec(regex, str, 1, &matchPointer, 0) != 0) {
        return strdup(str);
    }
    maxMatchSize = strlen(str) + strlen(replacement) + 1;
    result = (char *)calloc(maxMatchSize, sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    cursor = str;
    resCursor = result;
    while (*cursor != '\0') {
        if (!regexec(regex, cursor, 1, &matchPointer, 0)) {
            if(resCursor - result + strlen(replacement) < maxMatchSize){
                memcpy(resCursor, replacement, strlen(replacement));
                resCursor += strlen(replacement);
                cursor += matchPointer.rm_eo;
            } else break;
        } else {
            if(resCursor - result + 1 < maxMatchSize){
                *resCursor++ = *cursor++;
            } else break;
        }
    }
    *resCursor = '\0';
    return result;
}

void removeWhitespace(const char *str) {
    if (!str || !*str) return;
    regex_t regex;
    const char *pattern = "[[:space:]]";
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex pattern\n");
        return;
    }
    char *output = regreplace(str, &regex, "", REG_EXTENDED);
    if(output != NULL){
        printf("%s", output);
        free(output);
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello World! How are you?";
    removeWhitespace(str);
    return 0;
}