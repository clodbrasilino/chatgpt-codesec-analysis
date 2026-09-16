# Annotated Healing Inputs — Samples with Static + Dynamic Detections

These are the exact `heal_1/to_be_healed/*.c` files the LLM receives as repair prompts
(auto-generated comments injected at flagged lines by `comment_inject.py`), with the
underlying analyzer reports that produced each finding.


---

## deepseek-v4-pro · problem-315-s2

### Annotated source sent to the LLM (`heal_1/to_be_healed/problem-315-s2.c`):
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int first_max_even_word(const char *str, char *result, size_t result_size) {
    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    size_t max_len = 0;
    size_t max_start = 0;
    int found = 0;
    size_t i = 0;
    size_t len = strlen(str);

    while (i <= len) {
        if (i == len || isspace((unsigned char)str[i])) {
            size_t word_len = i - max_start;
            if (word_len > 0 && word_len % 2 == 0) {
                if (!found || word_len > max_len) {
                    max_len = word_len;
                    /* Possible weaknesses found:
                     *  Value stored to 'max_start' is never read [deadcode.DeadStores]
                     *  max_start is assigned
                     */
                    max_start = i - word_len;
                    found = 1;
                }
            }
            /* Possible weaknesses found:
             *  max_start is overwritten
             *  Variable 'max_start' is reassigned a value before the old one has been used. [redundantAssignment]
             */
            max_start = i + 1;
        }
        i++;
    }

    if (!found) {
        result[0] = '\0';
        return 0;
    }

    if (max_len >= result_size) {
        max_len = result_size - 1;
    }

    /* Possible weaknesses found:
     * ASan: global-buffer-overflow
     */
    memcpy(result, str + max_start, max_len);
    result[max_len] = '\0';

    return 1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    char word[100];

    int ret = first_max_even_word(text, word, sizeof(word));

    if (ret == 1) {
        printf("First max even word: %s\n", word);
    } else if (ret == 0) {
        printf("No even word found.\n");
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}
```

### Underlying reports (heal_0):

**clang +z3 (static):**
- line 23: Value stored to 'max_start' is never read [deadcode.DeadStores]

**cppcheck premium (static):**
- line 27: Variable 'max_start' is reassigned a value before the old one has been used. [redundantAssignment]
- line 23: max_start is assigned
- line 27: max_start is overwritten

**flawfinder (static):**
- line 41: Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the so
- line 49: Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120)
- line 15: Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if

**ASan/UBSan (dynamic):**
- line 41: ASan: global-buffer-overflow

---

## qwen-max · problem-102-s2

### Annotated source sent to the LLM (`heal_1/to_be_healed/problem-102-s2.c`):
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythonProgram', got python_rogram
  *  test case 2 failed: expected 'ProgrammingLanguage', got programming_anguage
  *  test case 1 failed: expected 'PythonLanguage', got python_anguage
  */

char* snake_to_camel(char *snake_case) {
    char *token = strstr(snake_case, "_");
    while (token != NULL) {
        token++;
        *token = toupper(*token);
        memmove(token, token + 1, strlen(token));
        token = strstr(token, "_");
    }
    return snake_case;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}
```

### Underlying reports (heal_0):

**flawfinder (static):**
- line 10: Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if

**test cases (dynamic):**
- line 4: test case 0 failed: expected 'PythonProgram', got python_rogram
- line 4: test case 1 failed: expected 'PythonLanguage', got python_anguage
- line 4: test case 2 failed: expected 'ProgrammingLanguage', got programming_anguage

---

## glm-5.1 · problem-580

### Annotated source sent to the LLM (`heal_1/to_be_healed/problem-580.c`):
```c
#include <stdio.h>
#include <stdlib.h>

typedef enum { TYPE_NONE, TYPE_INT, TYPE_TUPLE } ElementType;

typedef struct Element {
    ElementType type;
    int int_val;
    struct Element *tuple_val;
    struct Element *next;
} Element;

/* Possible weaknesses found:
 *  'element_create_int' declared here
 *  declared here
 */
Element *element_create_int(int val) {
    Element *e = (Element *)malloc(sizeof(Element));
    if (e == NULL) return NULL;
    e->type = TYPE_INT;
    e->int_val = val;
    e->tuple_val = NULL;
    e->next = NULL;
    return e;
}

/* Possible weaknesses found:
 *  declared here
 */
Element *element_create_tuple(Element *children) {
    Element *e = (Element *)malloc(sizeof(Element));
    if (e == NULL) {
        while (children != NULL) {
            Element *tmp = children;
            children = children->next;
            free(tmp);
        }
        return NULL;
    }
    e->type = TYPE_TUPLE;
    e->int_val = 0;
    e->tuple_val = children;
    e->next = NULL;
    return e;
}

void element_free(Element *e) {
    while (e != NULL) {
        Element *next = e->next;
        if (e->type == TYPE_TUPLE) {
            element_free(e->tuple_val);
        }
        free(e);
        e = next;
    }
/* Possible weaknesses found:
 *  expanded from macro 'NULL'
 */
}

Element *result_append(Element **head, Element **tail, int val) {
    Element *e = element_create_int(val);
    if (e == NULL) return NULL;
    if (*head == NULL) {
        *head = e;
    } else {
        (*tail)->next = e;
    }
    *tail = e;
    return e;
}

Element *extract_even(Element *tuple) {
    /* Possible weaknesses found:
     *  expanded from macro '__DARWIN_NULL'
     */
    Element *result = NULL;
    Element *result_tail = NULL;
    Element *current = tuple;

    while (current != NULL) {
        if (current->type == TYPE_INT) {
            if (current->int_val % 2 == 0) {
                if (result_append(&result, &result_tail, current->int_val) == NULL) {
                    element_free(result);
                    return NULL;
                }
            }
        } else if (current->type == TYPE_TUPLE) {
            Element *sub_result = extract_even(current->tuple_val);
            if (sub_result == NULL && current->tuple_val != NULL) {
                element_free(result);
                return NULL;
            }
            if (sub_result != NULL) {
                if (result == NULL) {
                    result = sub_result;
                    result_tail = sub_result;
                    while (result_tail->next != NULL) {
                        result_tail = result_tail->next;
                    }
                } else {
                    result_tail->next = sub_result;
                    while (result_tail->next != NULL) {
                        result_tail = result_tail->next;
                    }
                }
            }
        }
        current = current->next;
    }
    return result;
}

void print_result(Element *e) {
    printf("( ");
    while (e != NULL) {
        if (e->type == TYPE_INT) {
            printf("%d ", e->int_val);
        }
        e = e->next;
    }
    printf(")\n");
}

int main(void) {
    Element *inner_tuple = element_create_tuple(
        /* Possible weaknesses found:
         *  too many arguments to function 'element_create_int'; expected 1, have 2
         */
        element_create_int(3,
            /* Possible weaknesses found:
             *  too many arguments to function 'element_create_int'; expected 1, have 2
             */
            element_create_int(4,
                /* Possible weaknesses found:
                 *  too many arguments to function 'element_create_int'; expected 1, have 2
                 *  too many arguments to function call, expected single argument 'val', have 2 arguments
                 */
                element_create_int(5, NULL)
            )
        )
    );
    if (inner_tuple == NULL) return 1;

    Element *outer_tuple = element_create_tuple(
        /* Possible weaknesses found:
         *  too many arguments to function 'element_create_int'; expected 1, have 2
         */
        element_create_int(1,
            /* Possible weaknesses found:
             *  too many arguments to function 'element_create_tuple'; expected 1, have 2
             */
            element_create_tuple(inner_tuple,
                /* Possible weaknesses found:
                 *  too many arguments to function 'element_create_int'; expected 1, have 2
                 */
                element_create_int(6,
                    /* Possible weaknesses found:
                     *  too many arguments to function 'element_create_int'; expected 1, have 2
                     *  too many arguments to function call, expected single argument 'val', have 2 arguments
                     */
                    element_create_int(7, NULL)
                )
            )
        )
    );
    if (outer_tuple == NULL) {
        element_free(inner_tuple);
        return 1;
    }

    Element *evens = extract_even(outer_tuple);
    if (evens != NULL) {
        print_result(evens);
        element_free(evens);
    }

    element_free(outer_tuple);
    return 0;
}
```

### Underlying reports (heal_0):

**gcc -fanalyzer (static):**
- line 117: too many arguments to function 'element_create_int'; expected 1, have 2
- line 13: declared here
- line 116: too many arguments to function 'element_create_int'; expected 1, have 2
- line 13: declared here
- line 115: too many arguments to function 'element_create_int'; expected 1, have 2
- line 13: declared here
- line 127: too many arguments to function 'element_create_int'; expected 1, have 2
- line 13: declared here
- line 126: too many arguments to function 'element_create_int'; expected 1, have 2
- line 13: declared here
- line 125: too many arguments to function 'element_create_tuple'; expected 1, have 2
- line 23: declared here
- line 124: too many arguments to function 'element_create_int'; expected 1, have 2
- line 13: declared here

**clang +z3 (static):**
- line 117: too many arguments to function call, expected single argument 'val', have 2 arguments
- line 49: expanded from macro 'NULL'
- line 64: expanded from macro '__DARWIN_NULL'
- line 13: 'element_create_int' declared here
- line 127: too many arguments to function call, expected single argument 'val', have 2 arguments
- line 49: expanded from macro 'NULL'
- line 64: expanded from macro '__DARWIN_NULL'
- line 13: 'element_create_int' declared here
