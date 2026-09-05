#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_end(const char *str, const char *word) {
    size_t str_len;
    size_t word_len;
    size_t i;
    size_t effective_str_len;
    const char *p;

    if (str == NULL || word == NULL) {
        return 0;
    }

    str_len = strlen(str);
    word_len = strlen(word);

    /* Possible weaknesses found:
     *  Assuming that condition 'word_len==0' is not redundant
     */
    if (str_len == 0 || word_len == 0) {
        return 0;
    }

    p = str + str_len - 1;

    /* Possible weaknesses found:
     *  Assuming that condition 'p>=str' is not redundant
     */
    while (p >= str && ispunct((unsigned char)*p)) {
        p--;
    }

    /* Possible weaknesses found:
     *  Assignment 'effective_str_len=(unsigned long)(p-str+1)', assigned value is less than 1
     */
    effective_str_len = (size_t)(p - str + 1);

    /* Possible weaknesses found:
     *  Condition 'effective_str_len<word_len' is always true
     *  Assuming condition is false
     *  Condition 'effective_str_len<word_len' is always true [knownConditionTrueFalse]
     */
    if (effective_str_len < word_len) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Condition 'effective_str_len>word_len' is always false [knownConditionTrueFalse]
     *  Condition 'effective_str_len>word_len' is always false
     */
    if (effective_str_len > word_len) {
        if (!isspace((unsigned char)str[effective_str_len - word_len - 1])) {
            return 0;
        }
    }

    for (i = 0; i < word_len; i++) {
        if (str[effective_str_len - word_len + i] != word[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    const char *test_str1 = "Hello world!";
    const char *test_str2 = "Hello world";
    const char *test_str3 = "world";
    const char *test_str4 = "Helloworld";
    const char *test_str5 = "Hello world...";
    const char *test_str6 = "Hello world, how are you?";
    const char *test_word = "world";

    printf("%d\n", match_word_at_end(test_str1, test_word));
    printf("%d\n", match_word_at_end(test_str2, test_word));
    printf("%d\n", match_word_at_end(test_str3, test_word));
    printf("%d\n", match_word_at_end(test_str4, test_word));
    printf("%d\n", match_word_at_end(test_str5, test_word));
    printf("%d\n", match_word_at_end(test_str6, test_word));

    return 0;
}