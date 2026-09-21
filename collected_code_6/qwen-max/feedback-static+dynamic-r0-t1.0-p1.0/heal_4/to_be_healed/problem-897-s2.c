#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }

    size_t sentence_len = strnlen(sentence, 256);
    size_t word_len = strnlen(word, 256);

    for (size_t i = 0; i <= sentence_len - word_len; i++) {
        if (strncmp(sentence + i, word, word_len) == 0) {
            if ((i == 0 || !isalpha((unsigned char)sentence[i - 1])) && 
                (i + word_len >= sentence_len || !isalpha((unsigned char)sentence[i + word_len]))) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    const char sentence[] = "This is a sample sentence with several words";
    const char word[] = "sample";

    if (is_word_present(sentence, word)) {
        printf("Word '%s' is present in the sentence.\n", word);
    } else {
        printf("Word '%s' is not present in the sentence.\n", word);
    }

    return 0;
}