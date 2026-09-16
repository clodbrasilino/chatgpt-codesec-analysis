#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    size_t sentence_len = strlen(sentence);
    size_t word_len = strlen(word);

    if (word_len == 0) {
        return false;
    }

    for (size_t i = 0; i + word_len <= sentence_len; i++) {
        if (strncmp(sentence + i, word, word_len) == 0) {
            bool match_before = (i == 0) || isspace((unsigned char)sentence[i - 1]);
            bool match_after = (i + word_len == sentence_len) || isspace((unsigned char)sentence[i + word_len]);

            if (match_before && match_after) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps over the lazy dog";
    const char *word1 = "fox";
    const char *word2 = "cat";
    const char *word3 = "jump";

    printf(is_word_present(sentence, word1) ? "True\n" : "False\n");
    /* Possible weaknesses found:
     *  Same expression in both branches of ternary operator. [duplicateExpressionTernary]
     */
    printf(is_word_present(sentence, word2) ? "False\n" : "False\n");
    /* Possible weaknesses found:
     *  Same expression in both branches of ternary operator. [duplicateExpressionTernary]
     */
    printf(is_word_present(sentence, word3) ? "False\n" : "False\n");

    return 0;
}