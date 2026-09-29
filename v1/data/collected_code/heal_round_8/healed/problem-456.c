#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        if(strings[i] == NULL)
            continue;

        size_t len = strlen(strings[i]);
        if(strings[i][len] != '\0' || len <= 0)
            continue;

        char* str = (char*)malloc(sizeof(char) * (len + 1));
        if(str == NULL)
            continue;

        strlcpy(str, strings[i], len + 1);

        for(int j = 0, k = len - 1; j < k; ++j, --k) {
            char temp = str[j];
            str[j] = str[k];
            str[k] = temp;
        }

        str[len] = '\0';

        char* temp = realloc(strings[i], len + 1);
        if(temp == NULL) {
            free(str);
            continue;
        }

        strings[i] = temp;
        strlcpy(strings[i], str, len + 1);
        free(str);
    }
}

int main(void) {
    const int numStrings = 3;
    char* strings[numStrings];
    strings[0] = strdup("hello");
    strings[1] = strdup("world");
    strings[2] = strdup("example");

    if(strings[0] && strings[1] && strings[2]){
        reverseStrings(strings, numStrings);

        for (int i = 0; i < numStrings; i++) {
            printf("%s\n", strings[i]);
            free(strings[i]);
        }
    }

    return 0;
}