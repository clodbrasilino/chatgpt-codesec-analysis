#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int len;
} StringTuple;

StringTuple* string_to_tuple(const char *input) {
    if (input == NULL) return NULL;
    
    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) return NULL;

    tuple->len = strlen(input);
    tuple->str = malloc((tuple->len + 1) * sizeof(char));
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    for (int i = 0; input[i] != '\0'; i++) {
        tuple->str[i] = input[i];
    }
    tuple->str[tuple->len] = '\0';

    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple);
    }
}

int main() {
    const char *inputs[] = {"python 3.0", "15.10", "item1"};
    const char *expecteds[][8] = {{"p", "y", "t", "h", "o", "n", "3", "."}, {"1", "5", ".", "1", "0", "\0", "\0", "\0"}, {"i", "t", "e", "m", "1", "\0", "\0", "\0"}};
    
    for (int i = 0; i < 3; i++) {
        StringTuple *tuple = string_to_tuple(inputs[i]);
        if (tuple != NULL) {
            printf("String: %s\n", tuple->str);
            printf("Length: %d\n", tuple->len);

            for (int j = 0; j < tuple->len && j < 8; j++) {
                if (tuple->str[j] != expecteds[i][j]) {
                    printf("Test case %d failed: expected [%s], got [%s]\n", i, (char *)expecteds[i], tuple->str);
                    break;
                }
            }

            free_tuple(tuple);
        } else {
            printf("Failed to create tuple.\n");
        }
    }

    return 0;
}