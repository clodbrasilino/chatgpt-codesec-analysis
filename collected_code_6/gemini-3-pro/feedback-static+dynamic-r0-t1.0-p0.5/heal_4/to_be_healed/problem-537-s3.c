#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(const char* str) {
    if (str == NULL || *str == '\0') {
        return strdup("None");
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int str_len = strlen(str);
    char** words = (char**)malloc((str_len / 2 + 2) * sizeof(char*));
    if (words == NULL) {
        return strdup("None");
    }

    int word_count = 0;
    char* result = NULL;
    
    char* current_word = (char*)malloc(str_len + 1);
    if (!current_word) {
        free(words);
        return strdup("None");
    }
    
    int c_idx = 0;
    
    for (int i = 0; i <= str_len; i++) {
        char c = str[i];
        if (isalpha((unsigned char)c)) {
            current_word[c_idx++] = tolower((unsigned char)c);
        } else {
            if (c_idx > 0) {
                current_word[c_idx] = '\0';
                for (int j = 0; j < word_count; j++) {
                    if (strcmp(words[j], current_word) == 0) {
                        result = strdup(current_word);
                        break;
                    }
                }
                if (result != NULL) {
                    break;
                }
                words[word_count++] = strdup(current_word);
                c_idx = 0;
            }
        }
    }
    
    free(current_word);
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    if (result == NULL) {
        result = strdup("None");
    }

    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t size = 0;
    
    if (getline(&buffer, &size, stdin) != -1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        char* repeated_word = find_first_repeated_word(buffer);
        if (repeated_word != NULL) {
            printf("%s", repeated_word);
            free(repeated_word);
        }
    }
    
    if (buffer != NULL) {
        free(buffer);
    }
    return 0;
}