#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void split_string_at_lowercase(const char *str) {
    int len = strlen(str);
    char *token = (char *)malloc((len + 1) * sizeof(char));
    if (token == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    int i = 0, start = 0;
    while (i <= len) {
        if (i == len || (str[i] >= 'a' && str[i] <= 'z')) {
            memcpy(token, &str[start], i - start);
            token[i - start] = '\0';
            printf("%s\n", token);
            start = i + 1;
        }
        i++;
    }

    free(token);
}

int main() {
    const char *input = "HelloWorldExample";
    split_string_at_lowercase(input);
    return 0;
}