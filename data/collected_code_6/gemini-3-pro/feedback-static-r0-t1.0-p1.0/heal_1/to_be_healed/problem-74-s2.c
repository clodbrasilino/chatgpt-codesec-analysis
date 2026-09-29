#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkPatternSequence(const char* word, const char* patterns[], int numPatterns) {
    if (word == NULL || patterns == NULL || numPatterns <= 0) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t wordLen = strlen(word);
    size_t wordIndex = 0;

    for (int i = 0; i < numPatterns; i++) {
        if (patterns[i] == NULL) {
            return false;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t patternLen = strlen(patterns[i]);
        if (wordIndex + patternLen > wordLen) {
            return false;
        }

        if (strncmp(&word[wordIndex], patterns[i], patternLen) != 0) {
            return false;
        }

        wordIndex += patternLen;
    }

    return wordIndex == wordLen;
}

int main(void) {
    const char* word1 = "applebananacherry";
    const char* patterns1[] = {"apple", "banana", "cherry"};
    
    if (checkPatternSequence(word1, patterns1, 3)) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    const char* word2 = "applebananacherry";
    const char* patterns2[] = {"apple", "cherry", "banana"};
    
    if (!checkPatternSequence(word2, patterns2, 3)) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }

    const char* word3 = "applebanana";
    const char* patterns3[] = {"apple", "banana", "cherry"};
    
    if (!checkPatternSequence(word3, patterns3, 3)) {
        printf("Test 3 Passed\n");
    } else {
        printf("Test 3 Failed\n");
    }

    return 0;
}