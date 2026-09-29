#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ch;
    int count;
} RunLength;

RunLength* runLengthEncode(const char* str, int* size) {
    if(str == NULL) {
        *size = 0;
        return NULL;
    }
    
    int n = strlen(str);
    RunLength* encoded = (RunLength*) malloc(sizeof(RunLength) * n);

    int count = 1;
    int index = 0;

    for(int i = 1; i <= n; i++) {
        if(str[i] != str[i-1]) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'encoded' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            encoded[index].ch = str[i-1];
            encoded[index].count = count;
            index++;
            count = 1;
        } else {
            count++;
        }
    }

    *size = index;
    return encoded;
}

void printRunLength(const RunLength* encoded, int size) {
    for(int i = 0; i < size; i++) {
        printf("%c%d", encoded[i].ch, encoded[i].count);
    }
}

int main() {
    const char* str = "AAAABBBCCD";
    int size;
    RunLength* encoded = runLengthEncode(str, &size);
    if(encoded != NULL) {
        printRunLength(encoded, size);
        free(encoded);
    }
    return 0;
}