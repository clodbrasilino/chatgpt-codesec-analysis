Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-821.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-821.c:30:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
collected_code/heal_round_7/healed/problem-821.c:10:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120).
collected_code/heal_round_7/healed/problem-821.c:14:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120).

ANALYSIS SUMMARY:

Hits = 3
Lines analyzed = 39 in approximately 0.00 seconds (10532 lines/second)
Physical Source Lines of Code (SLOC) = 29
Hits@level = [0]   2 [1]   2 [2]   1 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   5 [1+]   3 [2+]   1 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 172.414 [1+] 103.448 [2+] 34.4828 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
