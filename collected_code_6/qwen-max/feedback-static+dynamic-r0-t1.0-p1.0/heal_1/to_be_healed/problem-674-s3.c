#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char** split_string(const char* str, int* word_count) {
    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (!words) return NULL;
    
    *word_count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp_str[strlen(str) + 1];
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp_str, str);
    
    char* token = strtok(temp_str, " ");
    while (token && *word_count < MAX_WORDS) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        words[*word_count] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (!words[*word_count]) {
            while (*word_count > 0) free(words[--*word_count]);
            free(words);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(words[*word_count], token);
        (*word_count)++;
        token = strtok(NULL, " ");
    }
    
    return words;
}

void free_words(char** words, int word_count) {
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
}

char* remove_duplicates(const char* str) {
    int word_count = 0;
    char** words = split_string(str, &word_count);
    if (!words) return NULL;
    
    int unique_count = 0;
    for (int i = 0; i < word_count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            words[unique_count++] = words[i];
        }
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char* result = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (!result) {
        free_words(words, word_count);
        return NULL;
    }
    result[0] = '\0';
    
    for (int i = 0; i < unique_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, words[i]);
        if (i < unique_count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
    }
    
    free_words(words, word_count);
    return result;
}

int main() {
    const char* input = "this this is a test test string string";
    char* result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Not enough memory\n");
    }
    return 0;
}