#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASCII_SIZE 256

typedef struct {
    char character;
    int frequency;
} CharFreq;

void count_char_frequency(const char *str, CharFreq **freq_array, int *unique_count) {
    int freq[ASCII_SIZE] = {0};
    int i;
    int count = 0;
    CharFreq *result;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'freq_array==NULL' is not redundant
     *  Assuming that condition 'unique_count==NULL' is not redundant
     */
    if (str == NULL || freq_array == NULL || unique_count == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'freq_array==NULL' is redundant or there is possible null pointer dereference: freq_array. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *freq_array = NULL;
        /* Possible weaknesses found:
         *  Either the condition 'unique_count==NULL' is redundant or there is possible null pointer dereference: unique_count. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *unique_count = 0;
        return;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }
    
    for (i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > 0) {
            count++;
        }
    }
    
    if (count == 0) {
        *freq_array = NULL;
        *unique_count = 0;
        return;
    }
    
    result = (CharFreq *)malloc(count * sizeof(CharFreq));
    if (result == NULL) {
        *freq_array = NULL;
        *unique_count = 0;
        return;
    }
    
    int index = 0;
    for (i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > 0) {
            result[index].character = (char)i;
            result[index].frequency = freq[i];
            index++;
        }
    }
    
    *freq_array = result;
    *unique_count = count;
}

int main(void) {
    const char *test_string = "Hello, World!";
    CharFreq *freq_array = NULL;
    int unique_count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;
    
    count_char_frequency(test_string, &freq_array, &unique_count);
    
    if (freq_array != NULL && unique_count > 0) {
        printf("Character frequencies for \"%s\":\n", test_string);
        for (i = 0; i < unique_count; i++) {
            if (isprint((unsigned char)freq_array[i].character)) {
                printf("'%c': %d\n", freq_array[i].character, freq_array[i].frequency);
            } else {
                printf("'\\x%02X': %d\n", (unsigned char)freq_array[i].character, freq_array[i].frequency);
            }
        }
        free(freq_array);
    }
    
    return 0;
}