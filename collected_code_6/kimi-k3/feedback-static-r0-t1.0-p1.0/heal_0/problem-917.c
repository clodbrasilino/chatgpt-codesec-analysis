#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SEQUENCE_LENGTH 256

void findSequences(const char *str) {
    int i = 0;
    int seqStart = -1;
    int seqLength = 0;
    
    if (str == NULL) {
        return;
    }
    
    while (str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            if (seqStart != -1 && seqLength > 1) {
                printf("%.*s\n", seqLength, &str[seqStart]);
            }
            seqStart = i;
            seqLength = 1;
        } else if (islower((unsigned char)str[i])) {
            if (seqStart != -1) {
                seqLength++;
            }
        } else {
            if (seqStart != -1 && seqLength > 1) {
                printf("%.*s\n", seqLength, &str[seqStart]);
            }
            seqStart = -1;
            seqLength = 0;
        }
        i++;
    }
    
    if (seqStart != -1 && seqLength > 1) {
        printf("%.*s\n", seqLength, &str[seqStart]);
    }
}

int main(void) {
    const char *testString = "Hello World This Is A Test String ABCdef GHi";
    
    if (testString != NULL) {
        findSequences(testString);
    }
    
    return 0;
}