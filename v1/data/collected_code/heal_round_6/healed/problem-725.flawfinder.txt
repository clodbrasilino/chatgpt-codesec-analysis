Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_6/healed/problem-725.c

FINAL RESULTS:

collected_code/heal_round_6/healed/problem-725.c:24:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.

ANALYSIS SUMMARY:

Hits = 1
Lines analyzed = 43 in approximately 0.00 seconds (12199 lines/second)
Physical Source Lines of Code (SLOC) = 38
Hits@level = [0]   5 [1]   0 [2]   1 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   6 [1+]   1 [2+]   1 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 157.895 [1+] 26.3158 [2+] 26.3158 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
