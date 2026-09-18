# Analyzer Output Census — All Finding Types Across the Main Experiment

**Scope:** heal_0 (initial generations) of all 7 main cells (974 × 3 samples each;
6 completed cells + gemini's completed heal_0) — every report file parsed with
the pipeline's own parsers. **Current CWE mapping** column = the v1/base-paper
token mapping (static analyzers, kept verbatim from the ISE 2026 work) plus this
work's dynamic-channel extensions (`src/analysis/cwe_map.py`). **UNMAPPED** rows
and any mapping you want to revisit are the discussion agenda for the CWE-2026
re-taxonomization.

## gcc — gcc-15 -fanalyzer

20,454 report files scanned · **2,051 findings** · **67 distinct types**

| # | Finding type | Count | Example | Current CWE |
|---|---|---|---|---|
| 1 | `'X' undeclared (first use in this function)` | 404 | 'LLONG_MAX' undeclared (first use in this function) | CWE-457 |
| 2 | `'X' is defined in header 'X'; this is probably fixable by` | 404 | 'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <li | UNMAPPED ⚠️ |
| 3 | `each undeclared identifier is reported only once for each` | 293 | each undeclared identifier is reported only once for each function it appears in | UNMAPPED ⚠️ |
| 4 | `warning -Wimplicit-function-declaration` | 239 | implicit declaration of function 'strtol'; did you mean 'strtok'? [-Wimplicit-function-declarat | CWE-758 |
| 5 | `include 'X' or provide a declaration of 'X'` | 161 | include '<math.h>' or provide a declaration of 'fmodf' | UNMAPPED ⚠️ |
| 6 | `warning -Wincompatible-pointer-types` | 98 | assignment to 'Pair *' from incompatible pointer type 'struct Pair *' [-Wincompatible-pointer-t | CWE-843 |
| 7 | `(near initialization for 'X')` | 76 | (near initialization for '(anonymous)') | UNMAPPED ⚠️ |
| 8 | `expected 'X' but argument is of type 'X'` | 53 | expected 'ElementCount *' but argument is of type 'ElementCount **' | UNMAPPED ⚠️ |
| 9 | `warning -Wint-conversion` | 47 | passing argument 1 of 'strlen' makes pointer from integer without a cast [-Wint-conversion] | CWE-704 |
| 10 | `expected 'X' before 'X'` | 34 | expected ')' before 'PRIu64' | UNMAPPED ⚠️ |
| 11 | `'X' has no member named 'X'` | 28 | 'List' has no member named 'next' | UNMAPPED ⚠️ |
| 12 | `request for member 'X' in something not a structure or uni` | 24 | request for member 'tuples' in something not a structure or union | UNMAPPED ⚠️ |
| 13 | `declared here` | 13 | declared here | UNMAPPED ⚠️ |
| 14 | `field name not in record or union initializer` | 12 | field name not in record or union initializer | UNMAPPED ⚠️ |
| 15 | `unknown type name 'X'` | 11 | unknown type name 'size_t' | CWE-758 |
| 16 | `non-static initialization of a flexible array member` | 10 | non-static initialization of a flexible array member | UNMAPPED ⚠️ |
| 17 | `subscripted value is neither array nor pointer nor vector` | 9 | subscripted value is neither array nor pointer nor vector | UNMAPPED ⚠️ |
| 18 | `too many arguments to function 'X'; expected N, have N` | 8 | too many arguments to function 'qsort'; expected 4, have 5 | UNMAPPED ⚠️ |
| 19 | `'X' undeclared (first use in this function); did you mean` | 7 | 'INFINITY' undeclared (first use in this function); did you mean 'RLIM_INFINITY'? | CWE-457 |
| 20 | `incompatible type for argument N of 'X'` | 6 | incompatible type for argument 1 of 'free_list' | UNMAPPED ⚠️ |
| 21 | `conflicting types for 'X'; have 'X'` | 6 | conflicting types for 'radixsort'; have 'void(int *, int)' | CWE-758 |
| 22 | `variable-sized object may not be initialized except with a` | 6 | variable-sized object may not be initialized except with an empty initializer | UNMAPPED ⚠️ |
| 23 | `invalid use of undefined type 'X'` | 6 | invalid use of undefined type 'struct Tuple' | UNMAPPED ⚠️ |
| 24 | `expected declaration or statement at end of input` | 6 | expected declaration or statement at end of input | UNMAPPED ⚠️ |
| 25 | `Python.h: No such file or directory` | 6 | Python.h: No such file or directory | UNMAPPED ⚠️ |
| 26 | `incompatible types when assigning to type 'X' from type 'X` | 5 | incompatible types when assigning to type 'ElementCount' from type 'ElementCount *' | UNMAPPED ⚠️ |
| 27 | `too few arguments to function 'X'; expected N, have N` | 5 | too few arguments to function 'max3'; expected 3, have 2 | UNMAPPED ⚠️ |
| 28 | `expected expression before 'X' token` | 5 | expected expression before ')' token | UNMAPPED ⚠️ |
| 29 | `expected 'X' before 'X' token` | 5 | expected ')' before '*' token | UNMAPPED ⚠️ |
| 30 | `assignment of read-only location 'X'` | 4 | assignment of read-only location '*(str2 + (sizetype)i)' | UNMAPPED ⚠️ |
| 31 | `assignment to expression with array type` | 3 | assignment to expression with array type | UNMAPPED ⚠️ |
| 32 | `expected 'X', 'X', 'X', 'X' or 'X' before 'X'` | 3 | expected '=', ',', ';', 'asm' or '__attribute__' before 'PositiveNumbers' | UNMAPPED ⚠️ |
| 33 | `expected 'X', 'X', 'X', 'X' or 'X' before 'X' token` | 3 | expected '=', ',', ';', 'asm' or '__attribute__' before ':' token | UNMAPPED ⚠️ |
| 34 | `previous declaration of 'X' with type 'X'` | 3 | previous declaration of 'radixsort' with type 'int(const unsigned char **, int,  const unsigned | UNMAPPED ⚠️ |
| 35 | `incompatible types when initializing type 'X' using type '` | 3 | incompatible types when initializing type 'List *' using type 'List' | UNMAPPED ⚠️ |
| 36 | `previous implicit declaration of 'X' with type 'X'` | 3 | previous implicit declaration of 'count_chars_in_partial' with type 'int()' | UNMAPPED ⚠️ |
| 37 | `'X' is a pointer; did you mean to use 'X'?` | 3 | 'list' is a pointer; did you mean to use '->'? | UNMAPPED ⚠️ |
| 38 | `expected 'X' at end of input` | 3 | expected ')' at end of input | UNMAPPED ⚠️ |
| 39 | `extra brace group at end of initializer` | 2 | extra brace group at end of initializer | UNMAPPED ⚠️ |
| 40 | `array type has incomplete element type 'X'` | 2 | array type has incomplete element type 'char *[]' | UNMAPPED ⚠️ |
| 41 | `declaration of 'X' as multidimensional array must have bou` | 2 | declaration of 'list' as multidimensional array must have bounds for all dimensions except the  | UNMAPPED ⚠️ |
| 42 | `expected expression before 'X'` | 2 | expected expression before 'int' | UNMAPPED ⚠️ |
| 43 | `expected 'X' but argument is of type 'X' {aka 'X'}` | 2 | expected 'regmatch_t * restrict' but argument is of type 'regoff_t *' {aka 'long long int *'} | UNMAPPED ⚠️ |
| 44 | `'X' declared here` | 2 | 'map_int' declared here | UNMAPPED ⚠️ |
| 45 | `expected identifier before 'X'` | 2 | expected identifier before 'int' | UNMAPPED ⚠️ |
| 46 | `expected 'X' before string constant` | 1 | expected ';' before string constant | UNMAPPED ⚠️ |
| 47 | `expected statement before 'X' token` | 1 | expected statement before ')' token | UNMAPPED ⚠️ |
| 48 | `invalid operands to binary == (have 'X' and 'X')` | 1 | invalid operands to binary == (have 'LinkedList' and 'void *') | UNMAPPED ⚠️ |
| 49 | `incompatible types when returning type 'X' but 'X' was exp` | 1 | incompatible types when returning type 'Tuple' but 'Tuple *' was expected | UNMAPPED ⚠️ |
| 50 | `invalid use of void expression` | 1 | invalid use of void expression | UNMAPPED ⚠️ |
| 51 | `lvalue required as left operand of assignment` | 1 | lvalue required as left operand of assignment | UNMAPPED ⚠️ |
| 52 | `'X' is a pointer to pointer; did you mean to dereference i` | 1 | 'result_list' is a pointer to pointer; did you mean to dereference it before applying '->' to i | UNMAPPED ⚠️ |
| 53 | `void value not ignored as it ought to be` | 1 | void value not ignored as it ought to be | UNMAPPED ⚠️ |
| 54 | `conflicting types for 'X'; have 'X' {aka 'X'}` | 1 | conflicting types for 'qsort_r'; have 'void(void *, size_t,  size_t,  int (*)(const void *, con | CWE-758 |
| 55 | `previous declaration of 'X' with type 'X' {aka 'X'}` | 1 | previous declaration of 'qsort_r' with type 'void(void *, size_t,  size_t,  void *, int (*)(voi | UNMAPPED ⚠️ |
| 56 | `type of formal parameter N is incomplete` | 1 | type of formal parameter 1 is incomplete | UNMAPPED ⚠️ |
| 57 | `an argument type that has a default promotion cannot match` | 1 | an argument type that has a default promotion cannot match an empty parameter name list declara | UNMAPPED ⚠️ |
| 58 | `invalid operands to binary % (have 'X' and 'X')` | 1 | invalid operands to binary % (have 'double' and 'int') | UNMAPPED ⚠️ |
| 59 | `cast specifies array type` | 1 | cast specifies array type | UNMAPPED ⚠️ |
| 60 | `cannot convert to a pointer type` | 1 | cannot convert to a pointer type | UNMAPPED ⚠️ |
| 61 | `warning -Wimplicit-int` | 1 | return type defaults to 'int' [-Wimplicit-int] | UNMAPPED ⚠️ |
| 62 | `expected 'X' {aka 'X'} but argument is of type 'X'` | 1 | expected 'MapFunc' {aka 'void * (*)(void *)'} but argument is of type 'int * (*)(void *)' | UNMAPPED ⚠️ |
| 63 | `expected 'X' before numeric constant` | 1 | expected ';' before numeric constant | UNMAPPED ⚠️ |
| 64 | `gmp.h: No such file or directory` | 1 | gmp.h: No such file or directory | UNMAPPED ⚠️ |
| 65 | `invalid initializer` | 1 | invalid initializer | UNMAPPED ⚠️ |
| 66 | `missing terminating " character` | 1 | missing terminating " character | UNMAPPED ⚠️ |
| 67 | `expected expression at end of input` | 1 | expected expression at end of input | UNMAPPED ⚠️ |

## clang — clang --analyze + z3 crosscheck

20,454 report files scanned · **1,563 findings** · **74 distinct types**

| # | Finding type | Count | Example | Current CWE |
|---|---|---|---|---|
| 1 | `use of undeclared identifier 'X'` | 583 | use of undeclared identifier 'count' | UNMAPPED ⚠️ |
| 2 | `call to undeclared library function 'X' with type 'X'; ISO` | 199 | call to undeclared library function 'strtol' with type 'long (const char *, char **, int)'; ISO | UNMAPPED ⚠️ |
| 3 | `include the header <string.h> or explicitly provide a decl` | 69 | include the header <string.h> or explicitly provide a declaration for 'memcpy' | UNMAPPED ⚠️ |
| 4 | `Value stored to 'X' is never read [deadcode.DeadStores]` | 66 | Value stored to 'max_start' is never read [deadcode.DeadStores] | UNMAPPED ⚠️ |
| 5 | `include the header <stdlib.h> or explicitly provide a decl` | 63 | include the header <stdlib.h> or explicitly provide a declaration for 'strtol' | UNMAPPED ⚠️ |
| 6 | `call to undeclared function 'X'; ISO C99 and later do not` | 57 | call to undeclared function 'dict_free'; ISO C99 and later do not support implicit function dec | UNMAPPED ⚠️ |
| 7 | `Value stored to 'X' during its initialization is never rea` | 51 | Value stored to 'val' during its initialization is never read [deadcode.DeadStores] | UNMAPPED ⚠️ |
| 8 | `include the header <math.h> or explicitly provide a declar` | 46 | include the header <math.h> or explicitly provide a declaration for 'fmodf' | UNMAPPED ⚠️ |
| 9 | `expected 'X'` | 43 | expected ')' | UNMAPPED ⚠️ |
| 10 | `to match this 'X'` | 43 | to match this '(' | UNMAPPED ⚠️ |
| 11 | `incompatible integer to pointer conversion initializing 'X` | 29 | incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int | UNMAPPED ⚠️ |
| 12 | `no member named 'X' in 'X'` | 28 | no member named 'next' in 'struct Tuple' | UNMAPPED ⚠️ |
| 13 | `conflicting types for 'X'` | 18 | conflicting types for 'dict_free' | CWE-758 |
| 14 | `Although the value stored to 'X' is used in the enclosing` | 16 | Although the value stored to 'line_length' is used in the enclosing expression, the value is ne | UNMAPPED ⚠️ |
| 15 | `include the header <ctype.h> or explicitly provide a decla` | 16 | include the header <ctype.h> or explicitly provide a declaration for 'isdigit' | UNMAPPED ⚠️ |
| 16 | `'X' declared here` | 15 | 'create_tuple' declared here | UNMAPPED ⚠️ |
| 17 | `previous implicit declaration is here` | 14 | previous implicit declaration is here | UNMAPPED ⚠️ |
| 18 | `expected expression` | 14 | expected expression | UNMAPPED ⚠️ |
| 19 | `passing argument to parameter 'X' here` | 11 | passing argument to parameter 'list' here | UNMAPPED ⚠️ |
| 20 | `subscripted value is not an array, pointer, or vector` | 9 | subscripted value is not an array, pointer, or vector | UNMAPPED ⚠️ |
| 21 | `incompatible integer to pointer conversion passing 'X' to` | 8 | incompatible integer to pointer conversion passing 'char' to parameter of type 'const char *';  | UNMAPPED ⚠️ |
| 22 | `expanded from macro 'X'` | 8 | expanded from macro 'strcpy' | UNMAPPED ⚠️ |
| 23 | `did you mean 'X'?` | 7 | did you mean 'create_tuple'? | UNMAPPED ⚠️ |
| 24 | `too few arguments to function call, expected N, have N` | 7 | too few arguments to function call, expected 3, have 2 | UNMAPPED ⚠️ |
| 25 | `initialization of non-aggregate type 'X' with a designated` | 6 | initialization of non-aggregate type 'DictionaryEntry *' with a designated initializer list | UNMAPPED ⚠️ |
| 26 | `expected 'X' after top level declarator` | 6 | expected ';' after top level declarator | UNMAPPED ⚠️ |
| 27 | `variable-sized object may not be initialized` | 6 | variable-sized object may not be initialized | UNMAPPED ⚠️ |
| 28 | `incomplete definition of type 'X'` | 6 | incomplete definition of type 'struct Tuple' | UNMAPPED ⚠️ |
| 29 | `forward declaration of 'X'` | 6 | forward declaration of 'struct Tuple' | UNMAPPED ⚠️ |
| 30 | `member reference base type 'X' is not a structure or union` | 6 | member reference base type 'int' is not a structure or union | UNMAPPED ⚠️ |
| 31 | `'X' file not found` | 6 | 'Python.h' file not found | UNMAPPED ⚠️ |
| 32 | `passing 'X' to parameter of incompatible type 'X'; take th` | 5 | passing 'LinkedList' to parameter of incompatible type 'LinkedList *'; take the address with & | UNMAPPED ⚠️ |
| 33 | `expected 'X' after expression` | 5 | expected ';' after expression | UNMAPPED ⚠️ |
| 34 | `use of undeclared identifier 'X'; did you mean 'X'?` | 4 | use of undeclared identifier 'size_t'; did you mean 'sizeof'? | UNMAPPED ⚠️ |
| 35 | `read-only variable is not assignable` | 4 | read-only variable is not assignable | UNMAPPED ⚠️ |
| 36 | `unknown type name 'X'` | 4 | unknown type name 'TupleList' | CWE-758 |
| 37 | `initialization of flexible array member is not allowed` | 4 | initialization of flexible array member is not allowed | UNMAPPED ⚠️ |
| 38 | `initialized flexible array member 'X' is here` | 4 | initialized flexible array member 'elements' is here | UNMAPPED ⚠️ |
| 39 | `previous declaration is here` | 4 | previous declaration is here | UNMAPPED ⚠️ |
| 40 | `invalid operands to binary expression ('X' and 'X')` | 3 | invalid operands to binary expression ('LinkedList' and 'void *') | UNMAPPED ⚠️ |
| 41 | `array type 'X' is not assignable` | 3 | array type 'char *[5]' is not assignable | UNMAPPED ⚠️ |
| 42 | `invalid application of 'X' to an incomplete type 'X'` | 3 | invalid application of 'sizeof' to an incomplete type 'Tuple[]' | UNMAPPED ⚠️ |
| 43 | `variable has incomplete type 'X'` | 3 | variable has incomplete type 'void' | UNMAPPED ⚠️ |
| 44 | `initializing 'X' (aka 'X') with an expression of incompati` | 3 | initializing 'Node *' (aka 'struct Node *') with an expression of incompatible type 'Node' (aka | UNMAPPED ⚠️ |
| 45 | `incompatible pointer to integer conversion initializing 'X` | 3 | incompatible pointer to integer conversion initializing 'int' with an expression of type 'char[ | UNMAPPED ⚠️ |
| 46 | `expected 'X' in 'X' statement specifier` | 3 | expected ';' in 'for' statement specifier | UNMAPPED ⚠️ |
| 47 | `passing argument to parameter here` | 3 | passing argument to parameter here | UNMAPPED ⚠️ |
| 48 | `assigning to 'X' from incompatible type 'X'` | 3 | assigning to 'int' from incompatible type 'void' | UNMAPPED ⚠️ |
| 49 | `member reference type 'X' is a pointer; did you mean to us` | 3 | member reference type 'Dictionary *' is a pointer; did you mean to use '->'? | UNMAPPED ⚠️ |
| 50 | `assigning to 'X' from incompatible type 'X'; dereference w` | 2 | assigning to 'ElementCount' from incompatible type 'ElementCount *'; dereference with * | UNMAPPED ⚠️ |
| 51 | `include the header <stdio.h> or explicitly provide a decla` | 2 | include the header <stdio.h> or explicitly provide a declaration for 'printf' | UNMAPPED ⚠️ |
| 52 | `redefinition of 'X' as different kind of symbol` | 2 | redefinition of 'PriorityQueue' as different kind of symbol | UNMAPPED ⚠️ |
| 53 | `previous definition is here` | 2 | previous definition is here | UNMAPPED ⚠️ |
| 54 | `expected 'X' at end of declaration` | 2 | expected ';' at end of declaration | UNMAPPED ⚠️ |
| 55 | `include the header <stdarg.h> or explicitly provide a decl` | 2 | include the header <stdarg.h> or explicitly provide a declaration for 'va_start' | UNMAPPED ⚠️ |
| 56 | `array subscript is not an integer` | 2 | array subscript is not an integer | UNMAPPED ⚠️ |
| 57 | `array has incomplete element type 'X'` | 2 | array has incomplete element type 'char *[]' | UNMAPPED ⚠️ |
| 58 | `incompatible function pointer types passing 'X' to paramet` | 2 | incompatible function pointer types passing 'int *(void *)' to parameter of type 'MapFunc' (aka | UNMAPPED ⚠️ |
| 59 | `too many arguments to function call, expected single argum` | 2 | too many arguments to function call, expected single argument 'val', have 2 arguments | UNMAPPED ⚠️ |
| 60 | `Result of 'X' is converted to a pointer of type 'X', which` | 2 | Result of 'realloc' is converted to a pointer of type 'int', which is incompatible with sizeof  | UNMAPPED ⚠️ |
| 61 | `function definition is not allowed here` | 2 | function definition is not allowed here | UNMAPPED ⚠️ |
| 62 | `assigning to 'X' (aka 'X') from incompatible type 'X' (aka` | 1 | assigning to 'Tuple' (aka 'struct Tuple') from incompatible type 'Tuple *' (aka 'struct Tuple * | UNMAPPED ⚠️ |
| 63 | `extraneous 'X' before 'X'` | 1 | extraneous ')' before ';' | UNMAPPED ⚠️ |
| 64 | `called object type 'X' (aka 'X') is not a function or func` | 1 | called object type 'Node *' (aka 'struct Node *') is not a function or function pointer | UNMAPPED ⚠️ |
| 65 | `incompatible pointer to integer conversion assigning to 'X` | 1 | incompatible pointer to integer conversion assigning to 'char' from 'void *' [-Wint-conversion] | CWE-704 |
| 66 | `too many arguments to function call, expected N, have N` | 1 | too many arguments to function call, expected 4, have 5 | UNMAPPED ⚠️ |
| 67 | `operand of type 'X' cannot be cast to a pointer type` | 1 | operand of type 'double' cannot be cast to a pointer type | UNMAPPED ⚠️ |
| 68 | `assignment to cast is illegal, lvalue casts are not suppor` | 1 | assignment to cast is illegal, lvalue casts are not supported | UNMAPPED ⚠️ |
| 69 | `include the header <strings.h> or explicitly provide a dec` | 1 | include the header <strings.h> or explicitly provide a declaration for 'index' | UNMAPPED ⚠️ |
| 70 | `used type 'X' (aka 'X') where arithmetic or pointer type i` | 1 | used type 'PointList' (aka 'Point *[6]') where arithmetic or pointer type is required | UNMAPPED ⚠️ |
| 71 | `passing 'X' to parameter of incompatible type 'X'` | 1 | passing 'Tuple' to parameter of incompatible type 'void *' | UNMAPPED ⚠️ |
| 72 | `returning 'X' from a function with incompatible result typ` | 1 | returning 'Tuple' from a function with incompatible result type 'Tuple *'; take the address wit | UNMAPPED ⚠️ |
| 73 | `member reference base type 'X' (aka 'X') is not a structur` | 1 | member reference base type 'List *' (aka 'struct List *') is not a structure or union | UNMAPPED ⚠️ |
| 74 | `type specifier missing, defaults to 'X'; ISO C99 and later` | 1 | type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimp | UNMAPPED ⚠️ |

## cppcheck — Cppcheck Premium 23.6 (bughunting)

20,454 report files scanned · **9,544 findings** · **229 distinct types**

| # | Finding type | Count | Example | Current CWE |
|---|---|---|---|---|
| 1 | `constParameter` | 1,940 | Parameter 'arr' can be declared as const array [constParameter] | UNMAPPED ⚠️ |
| 2 | `constParameterPointer` | 1,675 | Parameter 'list' can be declared as pointer to const [constParameterPointer] | UNMAPPED ⚠️ |
| 3 | `variableScope` | 1,224 | The scope of the variable 'current_value' can be reduced. [variableScope] | UNMAPPED ⚠️ |
| 4 | `constVariable` | 731 | Variable 'test1' can be declared as const array [constVariable] | UNMAPPED ⚠️ |
| 5 | `knownConditionTrueFalse` | 571 | Condition 'shifted>=0' is always true [knownConditionTrueFalse] | UNMAPPED ⚠️ |
| 6 | `Assignment 'X', assigned value is N` | 323 | Assignment 'result=snake_to_camel(test8)', assigned value is 0 | UNMAPPED ⚠️ |
| 7 | `constVariablePointer` | 318 | Variable 'check_time' can be declared as pointer to const [constVariablePointer] | UNMAPPED ⚠️ |
| 8 | `unreadVariable` | 298 | Variable 'data2' is assigned a value that is never used. [unreadVariable] | UNMAPPED ⚠️ |
| 9 | `Condition 'X' is always false` | 293 | Condition 'result' is always false | UNMAPPED ⚠️ |
| 10 | `unusedStructMember` | 259 | struct member 'KeyValue::next' is never used. [unusedStructMember] | UNMAPPED ⚠️ |
| 11 | `Condition 'X' is always true` | 233 | Condition 'shifted>=0' is always true | UNMAPPED ⚠️ |
| 12 | `Assuming that condition 'X' is not redundant` | 228 | Assuming that condition 'subset->is_integer' is not redundant | UNMAPPED ⚠️ |
| 13 | `Calling function 'X' returns N` | 202 | Calling function 'snake_to_camel' returns 0 | UNMAPPED ⚠️ |
| 14 | `Null pointer dereference` | 142 | Null pointer dereference | UNMAPPED ⚠️ |
| 15 | `nullPointerRedundantCheck` | 108 | Either the condition 'freq_array==NULL' is redundant or there is possible null pointer derefere | UNMAPPED ⚠️ |
| 16 | `Assuming condition is false` | 83 | Assuming condition is false | UNMAPPED ⚠️ |
| 17 | `uninitvar` | 61 | Uninitialized variable: digits [uninitvar] | CWE-457 |
| 18 | `unusedVariable` | 44 | Unused variable: current [unusedVariable] | UNMAPPED ⚠️ |
| 19 | `invalidPrintfArgType_uint` | 43 | %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned  | UNMAPPED ⚠️ |
| 20 | `nullPointer` | 38 | Possible null pointer dereference: prev [nullPointer] | UNMAPPED ⚠️ |
| 21 | `invalidScanfArgType_int` | 33 | %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigne | UNMAPPED ⚠️ |
| 22 | `memleakOnRealloc` | 27 | Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc] | UNMAPPED ⚠️ |
| 23 | `Assignment 'X', assigned value is greater than N` | 26 | Assignment 'new_size=list.tuples[i].size-k', assigned value is greater than 0 | UNMAPPED ⚠️ |
| 24 | `invalidPrintfArgType_sint` | 24 | %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed in | UNMAPPED ⚠️ |
| 25 | `Assuming condition 'X' is false` | 23 | Assuming condition 'result_size==NULL' is false | UNMAPPED ⚠️ |
| 26 | `Division by zero` | 22 | Division by zero | UNMAPPED ⚠️ |
| 27 | `redundantAssignment` | 20 | Variable 'result[1]' is reassigned a value before the old one has been used. [redundantAssignme | UNMAPPED ⚠️ |
| 28 | `Calling function 'X' returns -N` | 20 | Calling function 'min_tuple_difference' returns -1 | UNMAPPED ⚠️ |
| 29 | `Same expression used in consecutive assignments of 'X' and` | 20 | Same expression used in consecutive assignments of 'min_x' and 'max_x'. | UNMAPPED ⚠️ |
| 30 | `Assignment 'X', assigned value is "X"` | 19 | Assignment 'test1="101010"', assigned value is "101010" | UNMAPPED ⚠️ |
| 31 | `invalidTestForOverflow` | 18 | Invalid test for overflow 'arr[i]>max_ending_here+arr[i]'; signed integer overflow is undefined | UNMAPPED ⚠️ |
| 32 | `zerodivcond` | 18 | Either the condition 'k<=0' is redundant or there is division by zero at line 8. [zerodivcond] | UNMAPPED ⚠️ |
| 33 | `Assignment 'X', assigned value is -N` | 17 | Assignment 'missing5=findMissingNumber(empty,0)', assigned value is -1 | UNMAPPED ⚠️ |
| 34 | `arrayIndexOutOfBounds` | 15 | Array 'matches[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds] | CWE-119 |
| 35 | `arrayIndexThenCheck` | 12 | Array index 'k' is used before limits check. [arrayIndexThenCheck] | UNMAPPED ⚠️ |
| 36 | `Assignment to 'X'` | 12 | Assignment to 'n/=p' | UNMAPPED ⚠️ |
| 37 | `Array index out of bounds` | 10 | Array index out of bounds | UNMAPPED ⚠️ |
| 38 | `duplicateAssignExpression` | 10 | Same expression used in consecutive assignments of 'min_x' and 'max_x'. [duplicateAssignExpress | UNMAPPED ⚠️ |
| 39 | `memleak` | 10 | Memory leak: temp [memleak] | CWE-401 |
| 40 | `Shadowed declaration` | 9 | Shadowed declaration | UNMAPPED ⚠️ |
| 41 | `Shadow variable` | 9 | Shadow variable | UNMAPPED ⚠️ |
| 42 | `Shift` | 9 | Shift | UNMAPPED ⚠️ |
| 43 | `shadowVariable` | 8 | Local variable 'i' shadows outer variable [shadowVariable] | UNMAPPED ⚠️ |
| 44 | `invalidscanf` | 8 | scanf() without field width limits can crash with huge input data. [invalidscanf] | UNMAPPED ⚠️ |
| 45 | `unsignedLessThanZero` | 8 | Checking if unsigned expression 'h->size' is less than zero. [unsignedLessThanZero] | UNMAPPED ⚠️ |
| 46 | `'X' is assigned value 'X' here.` | 7 | 'src_pos' is assigned value '0' here. | UNMAPPED ⚠️ |
| 47 | `syntaxError` | 7 | Unmatched ')'. Configuration: ''. [syntaxError] | UNMAPPED ⚠️ |
| 48 | `Calling function 'X', 3rd argument 'X' value is N` | 7 | Calling function 'check_bits_in_range', 3rd argument '32' value is 32 | UNMAPPED ⚠️ |
| 49 | `shiftTooManyBitsSigned` | 7 | Shifting signed 32-bit value by 31 bits is implementation-defined behaviour [shiftTooManyBitsSi | UNMAPPED ⚠️ |
| 50 | `arrayIndexOutOfBoundsCond` | 5 | Either the condition 'index>0' is redundant or the array 'heap->data[100]' is accessed at index | UNMAPPED ⚠️ |
| 51 | `shiftTooManyBits` | 5 | Shifting 32-bit value by 32 bits is undefined behaviour. See condition at line 5. [shiftTooMany | UNMAPPED ⚠️ |
| 52 | `Uninitialized variable: c` | 5 | Uninitialized variable: c | UNMAPPED ⚠️ |
| 53 | `Uninitialized variable: result` | 5 | Uninitialized variable: result | UNMAPPED ⚠️ |
| 54 | `integerOverflow` | 5 | Signed integer overflow for expression '1<<31'. [integerOverflow] | CWE-190 |
| 55 | `Assuming condition 'X' is true` | 4 | Assuming condition 'shifted>=0' is true | UNMAPPED ⚠️ |
| 56 | `identicalConditionAfterEarlyExit` | 4 | Identical condition 'digits_after_decimal==0', second condition is always false [identicalCondi | UNMAPPED ⚠️ |
| 57 | `If condition 'X' is true, the function will return/exit` | 4 | If condition 'digits_after_decimal==0' is true, the function will return/exit | UNMAPPED ⚠️ |
| 58 | `Integer overflow` | 4 | Integer overflow | UNMAPPED ⚠️ |
| 59 | `autovarInvalidDeallocation` | 4 | Deallocation of an auto-variable results in undefined behaviour. [autovarInvalidDeallocation] | UNMAPPED ⚠️ |
| 60 | `Assignment 'X', assigned value is less than N` | 4 | Assignment 'digit=num%10', assigned value is less than 10 | UNMAPPED ⚠️ |
| 61 | `zerodiv` | 4 | Division by zero. [zerodiv] | CWE-369 |
| 62 | `redundantInitialization` | 4 | Redundant initialization for 'i'. The initialized value is overwritten before it is read. [redu | UNMAPPED ⚠️ |
| 63 | `oppositeInnerCondition` | 4 | Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition] | UNMAPPED ⚠️ |
| 64 | `Condition 'X'\N'X' is always true` | 4 | Condition 'input[length]=='\0'' is always true | UNMAPPED ⚠️ |
| 65 | `Uninitialized variable: digits` | 3 | Uninitialized variable: digits | UNMAPPED ⚠️ |
| 66 | `pointerSize` | 3 | Size of pointer 'lists' used instead of size of its data. [pointerSize] | UNMAPPED ⚠️ |
| 67 | `pos is assigned` | 3 | pos is assigned | UNMAPPED ⚠️ |
| 68 | `pos is overwritten` | 3 | pos is overwritten | UNMAPPED ⚠️ |
| 69 | `Testing identical condition 'X'` | 3 | Testing identical condition 'digits_after_decimal==0' | UNMAPPED ⚠️ |
| 70 | `Calling function 'X', 1st argument 'X' value is N` | 3 | Calling function 'free_tuple', 1st argument 'result' value is 0 | UNMAPPED ⚠️ |
| 71 | `ctunullpointer` | 3 | Null pointer dereference: t [ctunullpointer] | UNMAPPED ⚠️ |
| 72 | `Calling function 'X', 2nd argument 'X' value is N` | 3 | Calling function 'concatenate_tuples', 2nd argument 't2' value is 0 | UNMAPPED ⚠️ |
| 73 | `constParameterCallback` | 3 | Parameter 'list' can be declared as pointer to const. However it seems that 'print_list' is a c | UNMAPPED ⚠️ |
| 74 | `You might need to cast the function pointer here` | 3 | You might need to cast the function pointer here | UNMAPPED ⚠️ |
| 75 | `Parameter 'X' can be declared as pointer to const` | 3 | Parameter 'list' can be declared as pointer to const | UNMAPPED ⚠️ |
| 76 | `Condition 'X'\N'X' is always false` | 3 | Condition 'res4!='\0'' is always false | UNMAPPED ⚠️ |
| 77 | `Uninitialized variable: octalNumber` | 3 | Uninitialized variable: octalNumber | UNMAPPED ⚠️ |
| 78 | `Calling function 'X', 1st argument 'X' value is <Uninit>` | 3 | Calling function 'retain_three_largest', 1st argument 'largest' value is <Uninit> | UNMAPPED ⚠️ |
| 79 | `root->count is assigned` | 3 | root->count is assigned | UNMAPPED ⚠️ |
| 80 | `root->count is overwritten` | 3 | root->count is overwritten | UNMAPPED ⚠️ |
| 81 | `Uninitialized variable: terms` | 3 | Uninitialized variable: terms | UNMAPPED ⚠️ |
| 82 | `varFuncNullUB` | 2 | Passing NULL after the last typed argument to a variadic function leads to undefined behaviour. | UNMAPPED ⚠️ |
| 83 | `The comparison 'X' is always true.` | 2 | The comparison 'src_pos == 0' is always true. | UNMAPPED ⚠️ |
| 84 | `negativeIndex` | 2 | Either the condition 'mid-1>=0' is redundant or the array 'arr[0]' is accessed at index -1, whi | UNMAPPED ⚠️ |
| 85 | `Negative array index` | 2 | Negative array index | UNMAPPED ⚠️ |
| 86 | `redundantCondition` | 2 | Redundant condition: The condition '*(pos+4) == '\0'' is redundant since '*(pos+4) != 'b'' is s | UNMAPPED ⚠️ |
| 87 | `integerOverflowCond` | 2 | Either the condition 'val<-2147483648' is redundant or there is signed integer overflow for exp | UNMAPPED ⚠️ |
| 88 | `Uninitialized variable: words.count` | 2 | Uninitialized variable: words.count | UNMAPPED ⚠️ |
| 89 | `uselessAssignmentPtrArg` | 2 | Assignment of function parameter has no effect outside the function. Did you forget dereferenci | UNMAPPED ⚠️ |
| 90 | `invalidFunctionArgStr` | 2 | Invalid strtok() argument nr 2. A nul-terminated string is required. [invalidFunctionArgStr] | UNMAPPED ⚠️ |
| 91 | `duplicateExpression` | 2 | Same expression on both sides of '=='. [duplicateExpression] | UNMAPPED ⚠️ |
| 92 | `internalAstError` | 2 | Syntax Error: AST broken, binary operator '=' doesn't have two operands. [internalAstError] | UNMAPPED ⚠️ |
| 93 | `Uninitialized variable: output` | 2 | Uninitialized variable: output | UNMAPPED ⚠️ |
| 94 | `legacyUninitvar` | 2 | Uninitialized variable: result [legacyUninitvar] | CWE-457 |
| 95 | `deallocuse` | 2 | Dereferencing 'dict' after it is deallocated / released [deallocuse] | UNMAPPED ⚠️ |
| 96 | `unknownEvaluationOrder` | 2 | Expression 'new_str[i++]=str[i]' depends on order of evaluation of side effects [unknownEvaluat | UNMAPPED ⚠️ |
| 97 | `Uninitialized variable: L` | 2 | Uninitialized variable: L | UNMAPPED ⚠️ |
| 98 | `Uninitialized variable: R` | 2 | Uninitialized variable: R | UNMAPPED ⚠️ |
| 99 | `n_ll is assigned 'X' here.` | 2 | n_ll is assigned 'n' here. | UNMAPPED ⚠️ |
| 100 | `Same expression on both sides of 'X' because 'X' and 'X' r` | 2 | Same expression on both sides of '&&' because 'left_empty' and 'right_empty' represent the same | UNMAPPED ⚠️ |
| 101 | `duplicateExpressionTernary` | 2 | Same expression in both branches of ternary operator. [duplicateExpressionTernary] | UNMAPPED ⚠️ |
| 102 | `Assignment 'X', assigned value is greater than -N` | 2 | Assignment 'exp=n-1', assigned value is greater than -1 | UNMAPPED ⚠️ |
| 103 | `Unsigned less than zero` | 2 | Unsigned less than zero | UNMAPPED ⚠️ |
| 104 | `duplicateCondition` | 2 | The if condition is the same as the previous if condition [duplicateCondition] | UNMAPPED ⚠️ |
| 105 | `First condition` | 2 | First condition | UNMAPPED ⚠️ |
| 106 | `Second condition` | 2 | Second condition | UNMAPPED ⚠️ |
| 107 | `Uninitialized variable: heap` | 2 | Uninitialized variable: heap | UNMAPPED ⚠️ |
| 108 | `invalidScanfArgType_float` | 2 | %lf in format string (no. 1) requires 'double *' but the argument type is 'double'. [invalidSca | UNMAPPED ⚠️ |
| 109 | `signConversionCond` | 2 | Expression 'values[i]' can have a negative value. That is converted to an unsigned value and us | UNMAPPED ⚠️ |
| 110 | `Negative value is converted to an unsigned value` | 2 | Negative value is converted to an unsigned value | UNMAPPED ⚠️ |
| 111 | `prod2 is initialized` | 2 | prod2 is initialized | UNMAPPED ⚠️ |
| 112 | `prod2 is overwritten` | 2 | prod2 is overwritten | UNMAPPED ⚠️ |
| 113 | `result[N] is assigned` | 1 | result[1] is assigned | UNMAPPED ⚠️ |
| 114 | `result[N] is overwritten` | 1 | result[1] is overwritten | UNMAPPED ⚠️ |
| 115 | `Uninitialized variable: current` | 1 | Uninitialized variable: current | UNMAPPED ⚠️ |
| 116 | `list_of_lists->head is assigned` | 1 | list_of_lists->head is assigned | UNMAPPED ⚠️ |
| 117 | `list_of_lists->head is overwritten` | 1 | list_of_lists->head is overwritten | UNMAPPED ⚠️ |
| 118 | `unsignedPositive` | 1 | Unsigned expression 'group_start' can't be negative so it is unnecessary to test it. [unsignedP | UNMAPPED ⚠️ |
| 119 | `Uninitialized variable: binary` | 1 | Uninitialized variable: binary | UNMAPPED ⚠️ |
| 120 | `Uninitialized variable: sorted_arr` | 1 | Uninitialized variable: sorted_arr | UNMAPPED ⚠️ |
| 121 | `shiftNegative` | 1 | Shifting by a negative value is undefined behaviour [shiftNegative] | UNMAPPED ⚠️ |
| 122 | `result.size is assigned` | 1 | result.size is assigned | UNMAPPED ⚠️ |
| 123 | `result.size is overwritten` | 1 | result.size is overwritten | UNMAPPED ⚠️ |
| 124 | `result is assigned` | 1 | result is assigned | UNMAPPED ⚠️ |
| 125 | `result is overwritten` | 1 | result is overwritten | UNMAPPED ⚠️ |
| 126 | `max_start is assigned` | 1 | max_start is assigned | UNMAPPED ⚠️ |
| 127 | `max_start is overwritten` | 1 | max_start is overwritten | UNMAPPED ⚠️ |
| 128 | `n is assigned 'X' here.` | 1 | n is assigned '(int)val' here. | UNMAPPED ⚠️ |
| 129 | `Calling function 'X', 1st argument 'X' value is -N` | 1 | Calling function 'count_divisors', 1st argument 'n' value is -2147483648 | UNMAPPED ⚠️ |
| 130 | `signConversion` | 1 | Expression '-1' has a negative value. That is converted to an unsigned value and used in an uns | UNMAPPED ⚠️ |
| 131 | `shadowFunction` | 1 | Local variable 'main' shadows outer function [shadowFunction] | UNMAPPED ⚠️ |
| 132 | `Calling function free_tuple, 1st argument is null` | 1 | Calling function free_tuple, 1st argument is null | UNMAPPED ⚠️ |
| 133 | `Dereferencing argument t that is null` | 1 | Dereferencing argument t that is null | UNMAPPED ⚠️ |
| 134 | `Uninitialized variable: products` | 1 | Uninitialized variable: products | UNMAPPED ⚠️ |
| 135 | `a.head is assigned` | 1 | a.head is assigned | UNMAPPED ⚠️ |
| 136 | `a.head is overwritten` | 1 | a.head is overwritten | UNMAPPED ⚠️ |
| 137 | `Calling function add_item, 3rd argument is null` | 1 | Calling function add_item, 3rd argument is null | UNMAPPED ⚠️ |
| 138 | `Dereferencing argument value that is null` | 1 | Dereferencing argument value that is null | UNMAPPED ⚠️ |
| 139 | `nullPointerArithmetic` | 1 | Overflow in pointer arithmetic, NULL pointer is subtracted. [nullPointerArithmetic] | UNMAPPED ⚠️ |
| 140 | `Null pointer subtraction` | 1 | Null pointer subtraction | UNMAPPED ⚠️ |
| 141 | `multiCondition` | 1 | Expression is always true because 'else if' condition is opposite to previous condition at line | UNMAPPED ⚠️ |
| 142 | `first condition` | 1 | first condition | UNMAPPED ⚠️ |
| 143 | `else if condition is opposite to first condition` | 1 | else if condition is opposite to first condition | UNMAPPED ⚠️ |
| 144 | `bufferAccessOutOfBounds` | 1 | Buffer is accessed out of bounds: temp [bufferAccessOutOfBounds] | UNMAPPED ⚠️ |
| 145 | `Uninitialized variable: index` | 1 | Uninitialized variable: index | UNMAPPED ⚠️ |
| 146 | `Uninitialized variable: result.data` | 1 | Uninitialized variable: result.data | UNMAPPED ⚠️ |
| 147 | `h->elements[N] is assigned` | 1 | h->elements[0] is assigned | UNMAPPED ⚠️ |
| 148 | `h->elements[N] is overwritten` | 1 | h->elements[0] is overwritten | UNMAPPED ⚠️ |
| 149 | `Uninitialized variable: p` | 1 | Uninitialized variable: p | UNMAPPED ⚠️ |
| 150 | `Uninitialized variable: q` | 1 | Uninitialized variable: q | UNMAPPED ⚠️ |
| 151 | `Uninitialized variable: r` | 1 | Uninitialized variable: r | UNMAPPED ⚠️ |
| 152 | `'X' is assigned value 'X't'X' here.` | 1 | 'surface' is assigned value ''t'' here. | UNMAPPED ⚠️ |
| 153 | `The comparison 'X't'X' is always true because 'X' and 'X't` | 1 | The comparison 'surface == 't'' is always true because 'surface' and ''t'' represent the same v | UNMAPPED ⚠️ |
| 154 | `Uninitialized variable: res_i` | 1 | Uninitialized variable: res_i | UNMAPPED ⚠️ |
| 155 | `Uninitialized variable: res_j` | 1 | Uninitialized variable: res_j | UNMAPPED ⚠️ |
| 156 | `Uninitialized variable: res_k` | 1 | Uninitialized variable: res_k | UNMAPPED ⚠️ |
| 157 | `Calling function concatenate_tuples, 2nd argument is null` | 1 | Calling function concatenate_tuples, 2nd argument is null | UNMAPPED ⚠️ |
| 158 | `Dereferencing argument t2 that is null` | 1 | Dereferencing argument t2 that is null | UNMAPPED ⚠️ |
| 159 | `AssignmentAddressToInteger` | 1 | Assigning a pointer to an integer is not portable. [AssignmentAddressToInteger] | UNMAPPED ⚠️ |
| 160 | `missingReturn` | 1 | Found an exit path from function with non-void return type that has missing return statement [m | UNMAPPED ⚠️ |
| 161 | `invalidPointerCast` | 1 | Casting from float * to signed int * is not portable due to different binary data representatio | UNMAPPED ⚠️ |
| 162 | `Uninitialized variable: digit` | 1 | Uninitialized variable: digit | UNMAPPED ⚠️ |
| 163 | `originalNum is assigned` | 1 | originalNum is assigned | UNMAPPED ⚠️ |
| 164 | `originalNum is overwritten` | 1 | originalNum is overwritten | UNMAPPED ⚠️ |
| 165 | `Deallocating memory that was not dynamically allocated` | 1 | Deallocating memory that was not dynamically allocated | UNMAPPED ⚠️ |
| 166 | `overlappingWriteFunction` | 1 | Overlapping read/write in strncat() is undefined behavior [overlappingWriteFunction] | CWE-1260 |
| 167 | `shiftNegativeLHS` | 1 | Shifting a negative value is technically undefined behaviour [shiftNegativeLHS] | UNMAPPED ⚠️ |
| 168 | `literalWithCharPtrCompare` | 1 | String literal compared with variable 'loss'. Did you intend to use strcmp() instead? [literalW | UNMAPPED ⚠️ |
| 169 | `originalNumber is assigned` | 1 | originalNumber is assigned | UNMAPPED ⚠️ |
| 170 | `originalNumber is overwritten` | 1 | originalNumber is overwritten | UNMAPPED ⚠️ |
| 171 | `truncLongCastReturn` | 1 | int result is returned as long value. If the return value is long to avoid loss of information, | UNMAPPED ⚠️ |
| 172 | `Returning identical expression 'X'` | 1 | Returning identical expression 'len==1' | UNMAPPED ⚠️ |
| 173 | `duplicateValueTernary` | 1 | Same value in both branches of ternary operator. [duplicateValueTernary] | UNMAPPED ⚠️ |
| 174 | `va_list_usedBeforeStarted` | 1 | va_list 'args' used before va_start() was called. [va_list_usedBeforeStarted] | UNMAPPED ⚠️ |
| 175 | `selfAssignment` | 1 | Redundant assignment of 'dp[j]' to itself. [selfAssignment] | UNMAPPED ⚠️ |
| 176 | `uselessAssignmentArg` | 1 | Assignment of function parameter has no effect outside the function. [uselessAssignmentArg] | UNMAPPED ⚠️ |
| 177 | `actual_n is assigned 'X' here.` | 1 | actual_n is assigned 'n' here. | UNMAPPED ⚠️ |
| 178 | `i is initialized` | 1 | i is initialized | UNMAPPED ⚠️ |
| 179 | `i is overwritten` | 1 | i is overwritten | UNMAPPED ⚠️ |
| 180 | `Uninitialized variable: res1` | 1 | Uninitialized variable: res1 | UNMAPPED ⚠️ |
| 181 | `Uninitialized variable: res2` | 1 | Uninitialized variable: res2 | UNMAPPED ⚠️ |
| 182 | `Uninitialized variable: res3` | 1 | Uninitialized variable: res3 | UNMAPPED ⚠️ |
| 183 | `Same expression on both sides of 'X'.` | 1 | Same expression on both sides of '-'. | UNMAPPED ⚠️ |
| 184 | `incorrectLogicOperator` | 1 | Logical conjunction always evaluates to false: t.a == 0 && t.a != 0. [incorrectLogicOperator] | UNMAPPED ⚠️ |
| 185 | `oppositeExpression` | 1 | Opposite expression on both sides of '&&'. [oppositeExpression] | UNMAPPED ⚠️ |
| 186 | `invalidScanfFormatWidth` | 1 | Width 65 given in format string (no. 1) is larger than destination buffer 'binary_input[65]', u | UNMAPPED ⚠️ |
| 187 | `range_end is assigned 'X' here.` | 1 | range_end is assigned 'ranges[i].end' here. | UNMAPPED ⚠️ |
| 188 | `outer condition: i>N` | 1 | outer condition: i>0 | UNMAPPED ⚠️ |
| 189 | `opposite inner condition: i==N` | 1 | opposite inner condition: i==0 | UNMAPPED ⚠️ |
| 190 | `outer condition: count<max_adverbs` | 1 | outer condition: count<max_adverbs | UNMAPPED ⚠️ |
| 191 | `opposite inner condition: count>=max_adverbs` | 1 | opposite inner condition: count>=max_adverbs | UNMAPPED ⚠️ |
| 192 | `pair is assigned 'X' here.` | 1 | pair is assigned 'n/i' here. | UNMAPPED ⚠️ |
| 193 | `Uninitialized variable: s_curr` | 1 | Uninitialized variable: s_curr | UNMAPPED ⚠️ |
| 194 | `d1 is assigned 'X' here.` | 1 | d1 is assigned 'i' here. | UNMAPPED ⚠️ |
| 195 | `d2 is assigned 'X' here.` | 1 | d2 is assigned 'n/i' here. | UNMAPPED ⚠️ |
| 196 | `Return index of string to the first element that is N` | 1 | Return index of string to the first element that is 0 | UNMAPPED ⚠️ |
| 197 | `new_length is assigned 'X' here.` | 1 | new_length is assigned 'list->length+1U' here. | UNMAPPED ⚠️ |
| 198 | `new_count is assigned 'X' here.` | 1 | new_count is assigned 'container->count+1U' here. | UNMAPPED ⚠️ |
| 199 | `upper is assigned 'X' here.` | 1 | upper is assigned 'n<end?n:end' here. | UNMAPPED ⚠️ |
| 200 | `value is initialized` | 1 | value is initialized | UNMAPPED ⚠️ |
| 201 | `value is overwritten` | 1 | value is overwritten | UNMAPPED ⚠️ |
| 202 | `required is assigned 'X' here.` | 1 | required is assigned 'length+2U' here. | UNMAPPED ⚠️ |
| 203 | `best_x is assigned` | 1 | best_x is assigned | UNMAPPED ⚠️ |
| 204 | `best_x is overwritten` | 1 | best_x is overwritten | UNMAPPED ⚠️ |
| 205 | `Uninitialized variable: duplicates` | 1 | Uninitialized variable: duplicates | UNMAPPED ⚠️ |
| 206 | `Uninitialized variable: largest` | 1 | Uninitialized variable: largest | UNMAPPED ⚠️ |
| 207 | `Uninitialized variable: smallest` | 1 | Uninitialized variable: smallest | UNMAPPED ⚠️ |
| 208 | `candidate_index is assigned 'X' here.` | 1 | candidate_index is assigned 'length/2U' here. | UNMAPPED ⚠️ |
| 209 | `Assuming that condition 'X'\N'X' is not redundant` | 1 | Assuming that condition 'input[length]!='\0'' is not redundant | UNMAPPED ⚠️ |
| 210 | `inner->count is assigned` | 1 | inner->count is assigned | UNMAPPED ⚠️ |
| 211 | `inner->count is overwritten` | 1 | inner->count is overwritten | UNMAPPED ⚠️ |
| 212 | `invalidFunctionArg` | 1 | Invalid sqrt() argument nr 1. The value is -1 but the valid values are '0.0:'. [invalidFunction | CWE-628 |
| 213 | `remainder is assigned 'X' here.` | 1 | remainder is assigned 'n-a*a' here. | UNMAPPED ⚠️ |
| 214 | `Invalid argument` | 1 | Invalid argument | UNMAPPED ⚠️ |
| 215 | `status is assigned` | 1 | status is assigned | UNMAPPED ⚠️ |
| 216 | `status is overwritten` | 1 | status is overwritten | UNMAPPED ⚠️ |
| 217 | `outer condition: mid!=0UL` | 1 | outer condition: mid!=0UL | UNMAPPED ⚠️ |
| 218 | `opposite inner condition: mid==0UL` | 1 | opposite inner condition: mid==0UL | UNMAPPED ⚠️ |
| 219 | `Uninitialized variable: aggs.total` | 1 | Uninitialized variable: aggs.total | UNMAPPED ⚠️ |
| 220 | `tmp is assigned 'X' here.` | 1 | tmp is assigned 'y1' here. | UNMAPPED ⚠️ |
| 221 | `y1 is assigned 'X' here.` | 1 | y1 is assigned 'y2' here. | UNMAPPED ⚠️ |
| 222 | `y2 is assigned 'X' here.` | 1 | y2 is assigned 'tmp' here. | UNMAPPED ⚠️ |
| 223 | `*max_diff is assigned` | 1 | *max_diff is assigned | UNMAPPED ⚠️ |
| 224 | `*max_diff is overwritten` | 1 | *max_diff is overwritten | UNMAPPED ⚠️ |
| 225 | `Return value 'X' is always true` | 1 | Return value 'arr[n-1]<=arr[0]' is always true | UNMAPPED ⚠️ |
| 226 | `odd_days is assigned` | 1 | odd_days is assigned | UNMAPPED ⚠️ |
| 227 | `odd_days is overwritten` | 1 | odd_days is overwritten | UNMAPPED ⚠️ |
| 228 | `outer condition: len>N` | 1 | outer condition: len>2 | UNMAPPED ⚠️ |
| 229 | `opposite inner condition: len==N` | 1 | opposite inner condition: len==2 | UNMAPPED ⚠️ |

## flawfinder — Flawfinder 2.0.19 (rule-based)

20,454 report files scanned · **10,118 findings** · **32 distinct types**

| # | Finding type | Count | Example | Current CWE |
|---|---|---|---|---|
| 1 | `level 1 · buffer · strlen` | 4,253 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 2 | `level 2 · buffer · char` | 2,299 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 3 | `level 2 · buffer · memcpy` | 1,369 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 4 | `level 4 · buffer · strcpy` | 552 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 5 | `level 1 · buffer · strncpy` | 434 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 6 | `level 4 · buffer · scanf` | 263 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 7 | `level 2 · integer · atoi` | 230 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 8 | `level 1 · buffer · getchar` | 184 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 9 | `level 4 · buffer · strcat` | 143 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 10 | `level 2 · buffer · strcpy` | 63 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 11 | `level 1 · buffer · read` | 60 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 12 | `level 1 · buffer · scanf` | 44 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 13 | `level 1 · buffer · strcat` | 35 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 14 | `level 1 · buffer · strncat` | 34 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 15 | `level 2 · misc · open` | 31 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 16 | `level 2 · buffer · sprintf` | 19 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback- | UNMAPPED ⚠️ |
| 17 | `level 1 · buffer · mismatch` | 18 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 18 | `level 4 · format · snprintf` | 14 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/glm-5.1/feedback-s | UNMAPPED ⚠️ |
| 19 | `level 1 · buffer · equal` | 10 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/kimi-k3/feedback-s | UNMAPPED ⚠️ |
| 20 | `level 2 · misc · fopen` | 9 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 21 | `level 4 · format · printf` | 8 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 22 | `level 4 · race · access` | 8 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 23 | `level 1 · buffer · fgetc` | 8 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/openai-gpt56-sol/f | UNMAPPED ⚠️ |
| 24 | `level 1 · buffer · strcpy` | 7 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 25 | `level 1 · buffer · fscanf` | 5 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 26 | `level 2 · buffer · strcat` | 4 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback- | UNMAPPED ⚠️ |
| 27 | `level 1 · buffer · is_permutation` | 4 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/kimi-k3/feedback-s | UNMAPPED ⚠️ |
| 28 | `level 4 · buffer · sprintf` | 3 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 29 | `level 2 · integer · atol` | 3 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback- | UNMAPPED ⚠️ |
| 30 | `level 4 · format · vsnprintf` | 2 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/deepseek-v4-pro/fe | UNMAPPED ⚠️ |
| 31 | `level 1 · buffer · sprintf` | 1 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback- | UNMAPPED ⚠️ |
| 32 | `level 3 · random · srand` | 1 | /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/gemini-3-pro/feedb | UNMAPPED ⚠️ |

## sanitizer — ASan/UBSan runtime oracle

456 report files scanned · **578 findings** · **36 distinct types**

| # | Finding type | Count | Example | Current CWE |
|---|---|---|---|---|
| 1 | `ASan: SEGV` | 106 | ASan: SEGV | CWE-758 |
| 2 | `ASan: BUS` | 88 | ASan: BUS | UNMAPPED ⚠️ |
| 3 | `ASan: attempting` | 63 | ASan: attempting | UNMAPPED ⚠️ |
| 4 | `ASan: heap-buffer-overflow` | 51 | ASan: heap-buffer-overflow | CWE-787 |
| 5 | `ASan: stack-buffer-overflow` | 42 | ASan: stack-buffer-overflow | CWE-787 |
| 6 | `UBSan: member access within misaligned address 0xbebebe` | 38 | UBSan: member access within misaligned address 0xbebebebebebebebe for type 'Node' (aka 'struct  | UNMAPPED ⚠️ |
| 7 | `ASan: heap-use-after-free` | 37 | ASan: heap-use-after-free | CWE-416 |
| 8 | `UBSan: load of misaligned address 0xbebebebebebebebe fo` | 37 | UBSan: load of misaligned address 0xbebebebebebebebe for type 'int', which requires 8 byte alig | UNMAPPED ⚠️ |
| 9 | `UBSan: signed integer overflow: N + N cannot be represe` | 21 | UBSan: signed integer overflow: 1573198689 + 955137920 cannot be represented in type 'int' | CWE-190 |
| 10 | `UBSan: load of misaligned address 0x000400000005 for ty` | 10 | UBSan: load of misaligned address 0x000400000005 for type 'int', which requires 4 byte alignmen | UNMAPPED ⚠️ |
| 11 | `UBSan: load of misaligned address 0x000200000001 for ty` | 10 | UBSan: load of misaligned address 0x000200000001 for type 'int', which requires 4 byte alignmen | UNMAPPED ⚠️ |
| 12 | `ASan: stack-buffer-underflow` | 9 | ASan: stack-buffer-underflow | UNMAPPED ⚠️ |
| 13 | `ASan: negative-size-param:` | 7 | ASan: negative-size-param: | UNMAPPED ⚠️ |
| 14 | `UBSan: variable length array bound evaluates to non-pos` | 7 | UBSan: variable length array bound evaluates to non-positive value -1241577719 | UNMAPPED ⚠️ |
| 15 | `UBSan: signed integer overflow: N * N cannot be represe` | 6 | UBSan: signed integer overflow: 1000000000000000000 * 10 cannot be represented in type 'long lo | CWE-190 |
| 16 | `ASan: requested` | 6 | ASan: requested | UNMAPPED ⚠️ |
| 17 | `UBSan: left shift of N by N places cannot be represente` | 5 | UBSan: left shift of 1 by 31 places cannot be represented in type 'int' | UNMAPPED ⚠️ |
| 18 | `UBSan: signed integer overflow: N - -N cannot be repres` | 5 | UBSan: signed integer overflow: 9223372036854775807 - -2 cannot be represented in type 'long lo | CWE-190 |
| 19 | `UBSan: member access within null pointer of type 'X' (a` | 4 | UBSan: member access within null pointer of type 'Node' (aka 'struct Node') | UNMAPPED ⚠️ |
| 20 | `UBSan: signed integer overflow: -N + -N cannot be repre` | 3 | UBSan: signed integer overflow: -5349829096719403773 + -3890459611768029184 cannot be represent | CWE-190 |
| 21 | `UBSan: load of null pointer of type 'X'` | 3 | UBSan: load of null pointer of type 'int *' | UNMAPPED ⚠️ |
| 22 | `ASan: global-buffer-overflow` | 3 | ASan: global-buffer-overflow | CWE-787 |
| 23 | `UBSan: store to null pointer of type 'X'` | 2 | UBSan: store to null pointer of type 'int' | UNMAPPED ⚠️ |
| 24 | `UBSan: shift exponent N is too large for N-bit type 'X'` | 2 | UBSan: shift exponent 60189993 is too large for 32-bit type 'unsigned int' | CWE-190 |
| 25 | `UBSan: N.48679e+N is outside the range of representable` | 2 | UBSan: 3.48679e+09 is outside the range of representable values of type 'int' | UNMAPPED ⚠️ |
| 26 | `UBSan: signed integer overflow: N * -N cannot be repres` | 1 | UBSan: signed integer overflow: 3 * -8446744073709551616 cannot be represented in type 'long lo | CWE-190 |
| 27 | `UBSan: member access within null pointer of type 'X'` | 1 | UBSan: member access within null pointer of type 'struct Node' | UNMAPPED ⚠️ |
| 28 | `UBSan: load of misaligned address 0xbebebebebebebec6 fo` | 1 | UBSan: load of misaligned address 0xbebebebebebebec6 for type 'struct Node *', which requires 8 | UNMAPPED ⚠️ |
| 29 | `ASan: memcpy-param-overlap:` | 1 | ASan: memcpy-param-overlap: | UNMAPPED ⚠️ |
| 30 | `ASan: FPE` | 1 | ASan: FPE | UNMAPPED ⚠️ |
| 31 | `UBSan: division by zero` | 1 | UBSan: division by zero | CWE-369 |
| 32 | `UBSan: inf is outside the range of representable values` | 1 | UBSan: inf is outside the range of representable values of type 'int' | UNMAPPED ⚠️ |
| 33 | `UBSan: signed integer overflow: -N - N cannot be repres` | 1 | UBSan: signed integer overflow: -2147479015 - 947900944 cannot be represented in type 'int' | CWE-190 |
| 34 | `UBSan: index -N out of bounds for type 'X'` | 1 | UBSan: index -6 out of bounds for type 'bool[m]' | CWE-787 |
| 35 | `UBSan: load of misaligned address 0x7ff7b8d4a46c for ty` | 1 | UBSan: load of misaligned address 0x7ff7b8d4a46c for type 'const void *', which requires 8 byte | UNMAPPED ⚠️ |
| 36 | `ASan: out` | 1 | ASan: out | UNMAPPED ⚠️ |

## tests — MBPP test-case oracle

20,185 report files scanned · **21,699 findings** · **6 distinct types**

| # | Finding type | Count | Example | Current CWE |
|---|---|---|---|---|
| 1 | `MARKER: CLI mode exercised via stdin (no functional oracle)` | 12,035 | problem-49.c:0:0: info: CLI mode exercised via stdin | CWE-758 (crash-backed only; plain wrong answers unmapped) |
| 2 | `MARKER: no testable interface (never executed)` | 3,004 | problem-124-s3.c:0:0: error: no testable interface (no testable interface (no target function,  | CWE-758 (crash-backed only; plain wrong answers unmapped) |
| 3 | `MARKER: could not compile under sanitizers` | 2,609 | problem-516-s3.c:0:0: error: could not compile under sanitizers (no combo compiled (signature m | CWE-758 (crash-backed only; plain wrong answers unmapped) |
| 4 | `test case failure (wrong output)` | 2,429 | test case 0 failed: expected 81, got <no output> | CWE-758 (crash-backed only; plain wrong answers unmapped) |
| 5 | `MARKER: all test cases passed (clean)` | 1,482 | problem-566-s2.c:0:0: info: all 3 test cases passed | CWE-758 (crash-backed only; plain wrong answers unmapped) |
| 6 | `MARKER: not compilable (skipped, heals via static channel)` | 140 | problem-512.c:0:0: error: not compilable - dynamic analysis skipped; compile errors are reporte | CWE-758 (crash-backed only; plain wrong answers unmapped) |

## Unmapped types (discussion agenda)

**gcc:** `'X' is defined in header 'X'; this is probably fixable by` (404); `each undeclared identifier is reported only once for each` (293); `include 'X' or provide a declaration of 'X'` (161); `(near initialization for 'X')` (76); `expected 'X' but argument is of type 'X'` (53); `expected 'X' before 'X'` (34); `'X' has no member named 'X'` (28); `request for member 'X' in something not a structure or uni` (24); `declared here` (13); `field name not in record or union initializer` (12); `non-static initialization of a flexible array member` (10); `subscripted value is neither array nor pointer nor vector` (9); `too many arguments to function 'X'; expected N, have N` (8); `incompatible type for argument N of 'X'` (6); `variable-sized object may not be initialized except with a` (6); `invalid use of undefined type 'X'` (6); `expected declaration or statement at end of input` (6); `Python.h: No such file or directory` (6); `incompatible types when assigning to type 'X' from type 'X` (5); `too few arguments to function 'X'; expected N, have N` (5); `expected expression before 'X' token` (5); `expected 'X' before 'X' token` (5); `assignment of read-only location 'X'` (4); `assignment to expression with array type` (3); `expected 'X', 'X', 'X', 'X' or 'X' before 'X'` (3); `expected 'X', 'X', 'X', 'X' or 'X' before 'X' token` (3); `previous declaration of 'X' with type 'X'` (3); `incompatible types when initializing type 'X' using type '` (3); `previous implicit declaration of 'X' with type 'X'` (3); `'X' is a pointer; did you mean to use 'X'?` (3); `expected 'X' at end of input` (3); `extra brace group at end of initializer` (2); `array type has incomplete element type 'X'` (2); `declaration of 'X' as multidimensional array must have bou` (2); `expected expression before 'X'` (2); `expected 'X' but argument is of type 'X' {aka 'X'}` (2); `'X' declared here` (2); `expected identifier before 'X'` (2); `expected 'X' before string constant` (1); `expected statement before 'X' token` (1); `invalid operands to binary == (have 'X' and 'X')` (1); `incompatible types when returning type 'X' but 'X' was exp` (1); `invalid use of void expression` (1); `lvalue required as left operand of assignment` (1); `'X' is a pointer to pointer; did you mean to dereference i` (1); `void value not ignored as it ought to be` (1); `previous declaration of 'X' with type 'X' {aka 'X'}` (1); `type of formal parameter N is incomplete` (1); `an argument type that has a default promotion cannot match` (1); `invalid operands to binary % (have 'X' and 'X')` (1); `cast specifies array type` (1); `cannot convert to a pointer type` (1); `warning -Wimplicit-int` (1); `expected 'X' {aka 'X'} but argument is of type 'X'` (1); `expected 'X' before numeric constant` (1); `gmp.h: No such file or directory` (1); `invalid initializer` (1); `missing terminating " character` (1); `expected expression at end of input` (1)

**clang:** `use of undeclared identifier 'X'` (583); `call to undeclared library function 'X' with type 'X'; ISO` (199); `include the header <string.h> or explicitly provide a decl` (69); `Value stored to 'X' is never read [deadcode.DeadStores]` (66); `include the header <stdlib.h> or explicitly provide a decl` (63); `call to undeclared function 'X'; ISO C99 and later do not` (57); `Value stored to 'X' during its initialization is never rea` (51); `include the header <math.h> or explicitly provide a declar` (46); `expected 'X'` (43); `to match this 'X'` (43); `incompatible integer to pointer conversion initializing 'X` (29); `no member named 'X' in 'X'` (28); `Although the value stored to 'X' is used in the enclosing` (16); `include the header <ctype.h> or explicitly provide a decla` (16); `'X' declared here` (15); `previous implicit declaration is here` (14); `expected expression` (14); `passing argument to parameter 'X' here` (11); `subscripted value is not an array, pointer, or vector` (9); `incompatible integer to pointer conversion passing 'X' to` (8); `expanded from macro 'X'` (8); `did you mean 'X'?` (7); `too few arguments to function call, expected N, have N` (7); `initialization of non-aggregate type 'X' with a designated` (6); `expected 'X' after top level declarator` (6); `variable-sized object may not be initialized` (6); `incomplete definition of type 'X'` (6); `forward declaration of 'X'` (6); `member reference base type 'X' is not a structure or union` (6); `'X' file not found` (6); `passing 'X' to parameter of incompatible type 'X'; take th` (5); `expected 'X' after expression` (5); `use of undeclared identifier 'X'; did you mean 'X'?` (4); `read-only variable is not assignable` (4); `initialization of flexible array member is not allowed` (4); `initialized flexible array member 'X' is here` (4); `previous declaration is here` (4); `invalid operands to binary expression ('X' and 'X')` (3); `array type 'X' is not assignable` (3); `invalid application of 'X' to an incomplete type 'X'` (3); `variable has incomplete type 'X'` (3); `initializing 'X' (aka 'X') with an expression of incompati` (3); `incompatible pointer to integer conversion initializing 'X` (3); `expected 'X' in 'X' statement specifier` (3); `passing argument to parameter here` (3); `assigning to 'X' from incompatible type 'X'` (3); `member reference type 'X' is a pointer; did you mean to us` (3); `assigning to 'X' from incompatible type 'X'; dereference w` (2); `include the header <stdio.h> or explicitly provide a decla` (2); `redefinition of 'X' as different kind of symbol` (2); `previous definition is here` (2); `expected 'X' at end of declaration` (2); `include the header <stdarg.h> or explicitly provide a decl` (2); `array subscript is not an integer` (2); `array has incomplete element type 'X'` (2); `incompatible function pointer types passing 'X' to paramet` (2); `too many arguments to function call, expected single argum` (2); `Result of 'X' is converted to a pointer of type 'X', which` (2); `function definition is not allowed here` (2); `assigning to 'X' (aka 'X') from incompatible type 'X' (aka` (1); `extraneous 'X' before 'X'` (1); `called object type 'X' (aka 'X') is not a function or func` (1); `too many arguments to function call, expected N, have N` (1); `operand of type 'X' cannot be cast to a pointer type` (1); `assignment to cast is illegal, lvalue casts are not suppor` (1); `include the header <strings.h> or explicitly provide a dec` (1); `used type 'X' (aka 'X') where arithmetic or pointer type i` (1); `passing 'X' to parameter of incompatible type 'X'` (1); `returning 'X' from a function with incompatible result typ` (1); `member reference base type 'X' (aka 'X') is not a structur` (1); `type specifier missing, defaults to 'X'; ISO C99 and later` (1)

**cppcheck:** `constParameter` (1,940); `constParameterPointer` (1,675); `variableScope` (1,224); `constVariable` (731); `knownConditionTrueFalse` (571); `Assignment 'X', assigned value is N` (323); `constVariablePointer` (318); `unreadVariable` (298); `Condition 'X' is always false` (293); `unusedStructMember` (259); `Condition 'X' is always true` (233); `Assuming that condition 'X' is not redundant` (228); `Calling function 'X' returns N` (202); `Null pointer dereference` (142); `nullPointerRedundantCheck` (108); `Assuming condition is false` (83); `unusedVariable` (44); `invalidPrintfArgType_uint` (43); `nullPointer` (38); `invalidScanfArgType_int` (33); `memleakOnRealloc` (27); `Assignment 'X', assigned value is greater than N` (26); `invalidPrintfArgType_sint` (24); `Assuming condition 'X' is false` (23); `Division by zero` (22); `redundantAssignment` (20); `Calling function 'X' returns -N` (20); `Same expression used in consecutive assignments of 'X' and` (20); `Assignment 'X', assigned value is "X"` (19); `invalidTestForOverflow` (18); `zerodivcond` (18); `Assignment 'X', assigned value is -N` (17); `arrayIndexThenCheck` (12); `Assignment to 'X'` (12); `Array index out of bounds` (10); `duplicateAssignExpression` (10); `Shadowed declaration` (9); `Shadow variable` (9); `Shift` (9); `shadowVariable` (8); `invalidscanf` (8); `unsignedLessThanZero` (8); `'X' is assigned value 'X' here.` (7); `syntaxError` (7); `Calling function 'X', 3rd argument 'X' value is N` (7); `shiftTooManyBitsSigned` (7); `arrayIndexOutOfBoundsCond` (5); `shiftTooManyBits` (5); `Uninitialized variable: c` (5); `Uninitialized variable: result` (5); `Assuming condition 'X' is true` (4); `identicalConditionAfterEarlyExit` (4); `If condition 'X' is true, the function will return/exit` (4); `Integer overflow` (4); `autovarInvalidDeallocation` (4); `Assignment 'X', assigned value is less than N` (4); `redundantInitialization` (4); `oppositeInnerCondition` (4); `Condition 'X'\N'X' is always true` (4); `Uninitialized variable: digits` (3); `pointerSize` (3); `pos is assigned` (3); `pos is overwritten` (3); `Testing identical condition 'X'` (3); `Calling function 'X', 1st argument 'X' value is N` (3); `ctunullpointer` (3); `Calling function 'X', 2nd argument 'X' value is N` (3); `constParameterCallback` (3); `You might need to cast the function pointer here` (3); `Parameter 'X' can be declared as pointer to const` (3); `Condition 'X'\N'X' is always false` (3); `Uninitialized variable: octalNumber` (3); `Calling function 'X', 1st argument 'X' value is <Uninit>` (3); `root->count is assigned` (3); `root->count is overwritten` (3); `Uninitialized variable: terms` (3); `varFuncNullUB` (2); `The comparison 'X' is always true.` (2); `negativeIndex` (2); `Negative array index` (2); `redundantCondition` (2); `integerOverflowCond` (2); `Uninitialized variable: words.count` (2); `uselessAssignmentPtrArg` (2); `invalidFunctionArgStr` (2); `duplicateExpression` (2); `internalAstError` (2); `Uninitialized variable: output` (2); `deallocuse` (2); `unknownEvaluationOrder` (2); `Uninitialized variable: L` (2); `Uninitialized variable: R` (2); `n_ll is assigned 'X' here.` (2); `Same expression on both sides of 'X' because 'X' and 'X' r` (2); `duplicateExpressionTernary` (2); `Assignment 'X', assigned value is greater than -N` (2); `Unsigned less than zero` (2); `duplicateCondition` (2); `First condition` (2); `Second condition` (2); `Uninitialized variable: heap` (2); `invalidScanfArgType_float` (2); `signConversionCond` (2); `Negative value is converted to an unsigned value` (2); `prod2 is initialized` (2); `prod2 is overwritten` (2); `result[N] is assigned` (1); `result[N] is overwritten` (1); `Uninitialized variable: current` (1); `list_of_lists->head is assigned` (1); `list_of_lists->head is overwritten` (1); `unsignedPositive` (1); `Uninitialized variable: binary` (1); `Uninitialized variable: sorted_arr` (1); `shiftNegative` (1); `result.size is assigned` (1); `result.size is overwritten` (1); `result is assigned` (1); `result is overwritten` (1); `max_start is assigned` (1); `max_start is overwritten` (1); `n is assigned 'X' here.` (1); `Calling function 'X', 1st argument 'X' value is -N` (1); `signConversion` (1); `shadowFunction` (1); `Calling function free_tuple, 1st argument is null` (1); `Dereferencing argument t that is null` (1); `Uninitialized variable: products` (1); `a.head is assigned` (1); `a.head is overwritten` (1); `Calling function add_item, 3rd argument is null` (1); `Dereferencing argument value that is null` (1); `nullPointerArithmetic` (1); `Null pointer subtraction` (1); `multiCondition` (1); `first condition` (1); `else if condition is opposite to first condition` (1); `bufferAccessOutOfBounds` (1); `Uninitialized variable: index` (1); `Uninitialized variable: result.data` (1); `h->elements[N] is assigned` (1); `h->elements[N] is overwritten` (1); `Uninitialized variable: p` (1); `Uninitialized variable: q` (1); `Uninitialized variable: r` (1); `'X' is assigned value 'X't'X' here.` (1); `The comparison 'X't'X' is always true because 'X' and 'X't` (1); `Uninitialized variable: res_i` (1); `Uninitialized variable: res_j` (1); `Uninitialized variable: res_k` (1); `Calling function concatenate_tuples, 2nd argument is null` (1); `Dereferencing argument t2 that is null` (1); `AssignmentAddressToInteger` (1); `missingReturn` (1); `invalidPointerCast` (1); `Uninitialized variable: digit` (1); `originalNum is assigned` (1); `originalNum is overwritten` (1); `Deallocating memory that was not dynamically allocated` (1); `shiftNegativeLHS` (1); `literalWithCharPtrCompare` (1); `originalNumber is assigned` (1); `originalNumber is overwritten` (1); `truncLongCastReturn` (1); `Returning identical expression 'X'` (1); `duplicateValueTernary` (1); `va_list_usedBeforeStarted` (1); `selfAssignment` (1); `uselessAssignmentArg` (1); `actual_n is assigned 'X' here.` (1); `i is initialized` (1); `i is overwritten` (1); `Uninitialized variable: res1` (1); `Uninitialized variable: res2` (1); `Uninitialized variable: res3` (1); `Same expression on both sides of 'X'.` (1); `incorrectLogicOperator` (1); `oppositeExpression` (1); `invalidScanfFormatWidth` (1); `range_end is assigned 'X' here.` (1); `outer condition: i>N` (1); `opposite inner condition: i==N` (1); `outer condition: count<max_adverbs` (1); `opposite inner condition: count>=max_adverbs` (1); `pair is assigned 'X' here.` (1); `Uninitialized variable: s_curr` (1); `d1 is assigned 'X' here.` (1); `d2 is assigned 'X' here.` (1); `Return index of string to the first element that is N` (1); `new_length is assigned 'X' here.` (1); `new_count is assigned 'X' here.` (1); `upper is assigned 'X' here.` (1); `value is initialized` (1); `value is overwritten` (1); `required is assigned 'X' here.` (1); `best_x is assigned` (1); `best_x is overwritten` (1); `Uninitialized variable: duplicates` (1); `Uninitialized variable: largest` (1); `Uninitialized variable: smallest` (1); `candidate_index is assigned 'X' here.` (1); `Assuming that condition 'X'\N'X' is not redundant` (1); `inner->count is assigned` (1); `inner->count is overwritten` (1); `remainder is assigned 'X' here.` (1); `Invalid argument` (1); `status is assigned` (1); `status is overwritten` (1); `outer condition: mid!=0UL` (1); `opposite inner condition: mid==0UL` (1); `Uninitialized variable: aggs.total` (1); `tmp is assigned 'X' here.` (1); `y1 is assigned 'X' here.` (1); `y2 is assigned 'X' here.` (1); `*max_diff is assigned` (1); `*max_diff is overwritten` (1); `Return value 'X' is always true` (1); `odd_days is assigned` (1); `odd_days is overwritten` (1); `outer condition: len>N` (1); `opposite inner condition: len==N` (1)

**flawfinder:** `level 1 · buffer · strlen` (4,253); `level 2 · buffer · char` (2,299); `level 2 · buffer · memcpy` (1,369); `level 4 · buffer · strcpy` (552); `level 1 · buffer · strncpy` (434); `level 4 · buffer · scanf` (263); `level 2 · integer · atoi` (230); `level 1 · buffer · getchar` (184); `level 4 · buffer · strcat` (143); `level 2 · buffer · strcpy` (63); `level 1 · buffer · read` (60); `level 1 · buffer · scanf` (44); `level 1 · buffer · strcat` (35); `level 1 · buffer · strncat` (34); `level 2 · misc · open` (31); `level 2 · buffer · sprintf` (19); `level 1 · buffer · mismatch` (18); `level 4 · format · snprintf` (14); `level 1 · buffer · equal` (10); `level 2 · misc · fopen` (9); `level 4 · format · printf` (8); `level 4 · race · access` (8); `level 1 · buffer · fgetc` (8); `level 1 · buffer · strcpy` (7); `level 1 · buffer · fscanf` (5); `level 2 · buffer · strcat` (4); `level 1 · buffer · is_permutation` (4); `level 4 · buffer · sprintf` (3); `level 2 · integer · atol` (3); `level 4 · format · vsnprintf` (2); `level 1 · buffer · sprintf` (1); `level 3 · random · srand` (1)

**sanitizer:** `ASan: BUS` (88); `ASan: attempting` (63); `UBSan: member access within misaligned address 0xbebebe` (38); `UBSan: load of misaligned address 0xbebebebebebebebe fo` (37); `UBSan: load of misaligned address 0x000400000005 for ty` (10); `UBSan: load of misaligned address 0x000200000001 for ty` (10); `ASan: stack-buffer-underflow` (9); `ASan: negative-size-param:` (7); `UBSan: variable length array bound evaluates to non-pos` (7); `ASan: requested` (6); `UBSan: left shift of N by N places cannot be represente` (5); `UBSan: member access within null pointer of type 'X' (a` (4); `UBSan: load of null pointer of type 'X'` (3); `UBSan: store to null pointer of type 'X'` (2); `UBSan: N.48679e+N is outside the range of representable` (2); `UBSan: member access within null pointer of type 'X'` (1); `UBSan: load of misaligned address 0xbebebebebebebec6 fo` (1); `ASan: memcpy-param-overlap:` (1); `ASan: FPE` (1); `UBSan: inf is outside the range of representable values` (1); `UBSan: load of misaligned address 0x7ff7b8d4a46c for ty` (1); `ASan: out` (1)

## Notes for the CWE-2026 update

- The static token mapping is the ISE 2026 base-paper mapping kept verbatim
  for comparability; under CWE-2026 several entries will move (e.g. buffer
  overflow family reorganizations, CWE-758 'Reliance on Undefined Behavior'
  successor entries).
- The dynamic mapping (ASan kinds, UBSan runtime errors) was added in this
  work; several entries currently collapse to broad CWEs (e.g. all buffer
  overflows → CWE-787) that CWE-2026 may want to split by memory region.
- Test-case failures are mapped to CWE-758 only when crash/sanitizer-backed;
  plain wrong answers are deliberately unmapped (functional defect, not a
  memory-safety CWE) — a framing decision to revisit for the new taxonomy.
- Flawfinder carries its own CWE tags in the raw output (parsed at mapping
  time from `(CWE-xxx)` markers); the census rows show its rule category +
  level as the type key.

## Reading notes (normalization caveats)

- UBSan misaligned-access rows (6, 8, 10, 11, 28, 35) are ONE type — "load of /
  member access within misaligned address" — split only by the runtime address in
  the message. Same for the ASan "requested" row (= "requested allocation size
  exceeds maximum supported size") and "ASan: out" (truncated "out-of-memory").
- "ASan: attempting" = "attempting free on address which was not malloc()-ed"
  (the v1 token `[CWE-590]`-equivalent; the truncated key hides it).
- Sanitizer counts cover the WHOLE dataset (all cells + healing rounds), since
  runtime findings are rare; static-tool counts cover the 7 main cells' heal_0
  (initial generations) only.
- gcc/clang compile-error types (the large UNMAPPED families) are not memory-
  safety weaknesses: they are the "not compilable" outcome class that heals via
  the static channel (see §1e of the collection report) — candidates for a
  dedicated non-CWE category or CWE-758-style umbrella in the 2026 taxonomy.
