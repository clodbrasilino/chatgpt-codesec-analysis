#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces(const char *str) {
    size_t i, len, spaces, out_len, j;
    char *output;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    spaces = 0;
    for (i = 1; i < len; i++) {
        if (isupper((unsigned char)str[i]) && !isspace((unsigned char)str[i - 1])) {
            spaces++;
        }
    }

    out_len = len + spaces;
    output = malloc(out_len + 1);
    if (output == NULL) {
        return NULL;
    }

    j = 0;
    if (len > 0) {
        output[j++] = str[0];
    }
    for (i = 1; i < len; i++) {
        if (isupper((unsigned char)str[i]) && !isspace((unsigned char)str[i - 1])) {
            output[j++] = ' ';
        }
        output[j++] = str[i];
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    char input[1024];
    char *result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    result = insert_spaces(input);
    if (result == NULL) {
        fputs("Error processing string\n", stderr);
        return 1;
    }

    puts(result);
    free(result);
    return 0;
}