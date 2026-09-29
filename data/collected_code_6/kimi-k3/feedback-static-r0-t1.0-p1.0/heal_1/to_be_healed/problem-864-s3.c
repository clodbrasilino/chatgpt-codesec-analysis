#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(const char *str) {
    size_t left = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t right = strlen(str);
    
    if (right == 0) {
        return true;
    }
    right--;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int findPalindromes(const char **strings, size_t count, char ***results) {
    if (strings == NULL || results == NULL) {
        return -1;
    }
    
    *results = NULL;
    size_t palindromeCount = 0;
    
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        
        if (isPalindrome(strings[i])) {
            char **temp = realloc(*results, (palindromeCount + 1) * sizeof(char *));
            if (temp == NULL) {
                for (size_t j = 0; j < palindromeCount; j++) {
                    free((*results)[j]);
                }
                free(*results);
                *results = NULL;
                return -1;
            }
            *results = temp;
            
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(strings[i]);
            (*results)[palindromeCount] = malloc(len + 1);
            if ((*results)[palindromeCount] == NULL) {
                for (size_t j = 0; j < palindromeCount; j++) {
                    free((*results)[j]);
                }
                free(*results);
                *results = NULL;
                return -1;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy((*results)[palindromeCount], strings[i]);
            palindromeCount++;
        }
    }
    
    return (int)palindromeCount;
}

void freeResults(char **results, int count) {
    if (results == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(results[i]);
    }
    free(results);
}

int main(void) {
    const char *testStrings[] = {
        "racecar",
        "hello",
        "level",
        "world",
        "madam",
        "noon",
        "test"
    };
    size_t numStrings = sizeof(testStrings) / sizeof(testStrings[0]);
    char **palindromes = NULL;
    
    int count = findPalindromes(testStrings, numStrings, &palindromes);
    
    if (count < 0) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %d palindrome(s):\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", palindromes[i]);
    }
    
    freeResults(palindromes, count);
    
    return EXIT_SUCCESS;
}