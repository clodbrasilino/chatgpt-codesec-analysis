#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_words(char** list, int count, char* substring) {
    int i = 0;
    while(i < count) {
        /* Possible weaknesses found:
         *  use of possibly-NULL '*list_31(D) + _2' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
         */
        if(strstr(list[i], substring) != NULL) {
            free(list[i]);
            for(int j = i; j < count - 1; j++) {
                list[j] = list[j + 1];
            }

            list[count - 1] = NULL;
            count--;
        } else {
            i++;
        }
    }
}

int main() {
    int count = 5;
    char* list[count];
    list[0] = strdup("Hello, World!");
    list[1] = strdup("Hello");
    list[2] = strdup("Hi");
    list[3] = strdup("World");
    list[4] = strdup("C-World");

    remove_words(list, count, "World");

    for(int i = 0; i < count; i++) {
        if(list[i] != NULL) {
            printf("%s\n", list[i]);
        }
        free(list[i]);
    }

    return 0;
}