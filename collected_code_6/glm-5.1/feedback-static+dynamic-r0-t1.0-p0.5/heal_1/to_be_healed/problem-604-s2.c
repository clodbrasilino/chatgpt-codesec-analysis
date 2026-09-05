#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *start, char *end) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char* reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, str, len + 1);

    reverse(result, result + len - 1);

    char *word_start = result;
    char *current = result;

    while (*current) {
        if (*current == ' ') {
            reverse(word_start, current - 1);
            word_start = current + 1;
        }
        current++;
    }
    reverse(word_start, current - 1);

    return result;
}

int main() {
    char str[] = "Hello World from C";
    
    char *reversed = reverse_words(str);
    if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s\n", str);
    printf("Reversed: %s\n", reversed);

    free(reversed);
    reversed = NULL;

    return 0;
}