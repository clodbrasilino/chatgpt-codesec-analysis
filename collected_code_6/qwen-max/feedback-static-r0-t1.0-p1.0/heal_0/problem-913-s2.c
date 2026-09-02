#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool is_number_at_end(const char *str) {
    if (str == NULL) {
        return false;
    }
    const char *p = str;
    while (*p != '\0') {
        ++p;
    }
    bool found_digit = false;
    while (p > str && isspace(*--p));
    while (p > str && isdigit(*--p)) {
        found_digit = true;
    }
    return found_digit && (p <= str || !isdigit(*p));
}

int main() {
    const char *test_strings[] = {
        "Hello 123",
        "Hello ABC123",
        "123 Hello",
        "123456",
        "ABCDEF",
        "   123   "
    };
    
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("'%s' has number at end: %s\n", test_strings[i], is_number_at_end(test_strings[i]) ? "true" : "false");
    }
    
    return 0;
}