#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

static bool is_optional_punctuation(unsigned char ch)
{
    return ispunct(ch) != 0;
}

static bool matches_word_at_end(const char *string, size_t string_length,
                                const char *word, size_t word_length)
{
    size_t end;

    if (string == NULL || word == NULL || word_length == 0U) {
        return false;
    }

    end = string_length;

    while (end > 0U &&
           is_optional_punctuation((unsigned char)string[end - 1U])) {
        --end;
    }

    if (end < word_length) {
        return false;
    }

    if (memcmp(string + end - word_length, word, word_length) != 0) {
        return false;
    }

    return end == word_length ||
           isspace((unsigned char)string[end - word_length - 1U]) != 0;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;
    const char *string;
    const char *word;
    size_t string_length;
    size_t word_length;
    bool matched;

    if (argc != 3 || argv == NULL) {
        program_name = argc > 0 && argv != NULL && argv[0] != NULL
                           ? argv[0]
                           : "program";
        fprintf(stderr, "Usage: %s <string> <word>\n", program_name);
        return 2;
    }

    string = argv[1];
    word = argv[2];

    if (string == NULL || word == NULL) {
        fputs("Invalid argument.\n", stderr);
        return 2;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
     */
    string_length = strnlen(string, SIZE_MAX);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'SIZE_MAX'
     */
    word_length = strnlen(word, SIZE_MAX);

    matched = matches_word_at_end(string, string_length, word, word_length);

    puts(matched ? "match" : "no match");
    return matched ? 0 : 1;
}