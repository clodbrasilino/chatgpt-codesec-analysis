#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;
    
    int result_index = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '_') {
            i++;
            if (i < len) {
                result[result_index++] = toupper(str[i]);
            }
        } else {
            result[result_index++] = str[i];
        }
    }
    result[result_index] = '\0';
    return result;
}

int main() {
    const char input[] = "this_is_snake_case";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}