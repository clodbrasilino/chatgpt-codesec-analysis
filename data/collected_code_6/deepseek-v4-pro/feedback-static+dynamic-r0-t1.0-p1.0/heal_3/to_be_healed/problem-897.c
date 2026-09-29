#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

bool word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *word == '\0') {
        return false;
    }

    size_t word_len = 0;
    while (word[word_len] != '\0') {
        word_len++;
    }

    size_t i = 0;
    while (sentence[i] != '\0') {
        while (sentence[i] != '\0' && !isalnum((unsigned char)sentence[i])) {
            i++;
        }

        if (sentence[i] == '\0') {
            break;
        }

        size_t start = i;
        while (sentence[i] != '\0' && isalnum((unsigned char)sentence[i])) {
            i++;
        }
        size_t token_len = i - start;

        if (token_len == word_len) {
            bool match = true;
            for (size_t j = 0; j < word_len; j++) {
                if (tolower((unsigned char)sentence[start + j]) != tolower((unsigned char)word[j])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    bool result;
    
    result = word_present("The quick brown fox", "fox");
    printf("%s\n", result ? "True" : "False");
    
    result = word_present("The quick brown fox", "dog");
    printf("%s\n", result ? "True" : "False");
    
    result = word_present("The quick brown fox", "");
    printf("%s\n", result ? "True" : "False");
    
    return 0;
}