Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-421.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-421.c:7:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
collected_code/heal_round_7/healed/problem-421.c:19:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120).
collected_code/heal_round_7/healed/problem-421.c:23:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120).

ANALYSIS SUMMARY:

Hits = 3
Lines analyzed = 40 in approximately 0.01 seconds (7540 lines/second)
Physical Source Lines of Code (SLOC) = 30
Hits@level = [0]   2 [1]   2 [2]   1 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   5 [1+]   3 [2+]   1 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 166.667 [1+] 100 [2+] 33.3333 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
