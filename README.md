# nondeterministic-turing-machine-simulator
This program implements a nondeterministic Turing machine simulator in C.

This program accept files written in the following way:

tr
0 a a S 0
0 a a S 13
1 x x R 1
1 a x R 2
2 a a R 3
2 b b R 8
3 a a R 3
3 b b R 4
4 b b R 4
4 c c R 5
5 y y R 5
5 c c R 5
5 x x R 5
5 _ x L 6
6 y y L 6
6 x x L 6
6 c y L 7
7 c c L 7
7 y y L 7
7 b b L 7
7 x x L 7
7 a a L 7
7 _ x R 1
8 b b R 8
8 c y R 9
9 y y R 10
10 y y R 10
10 x x S 11
9 c c R 12
13 a x R 14
13 x x R 13
13 y y R 20
13 b b R 21
14 a a R 14
14 b b R 15
15 b b R 15
15 c c R 16
16 c c R 16
16 x x R 16
16 _ x L 17
17 c c L 17
17 x x L 1
17 y y L 18
18 y y L 18
18 b y L 19
19 b b L 19
19 a a L 19
19 x x L 19
19 _ x R 13
20 y y R 20
20 c c R 20
20 x x S 22
15 y y R 15
17 b y L 19
acc
11
22
max
4000
run
aabbcc
aabbccc
aaabbc
aabbbbcc
aabcc
aabbcccccc
aaaaaabbccccc
aaaaabbbbbc
aaabbbccccccccc
abbbccccc

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

'tr'--->following this statement there are all the transitions that describe the turing machine.
'acc'--->following this statement there are all the acceptance states.
'max'--->following this statement there is the maximum number of moves, this is done in order to prevent infinite loops.
'run'--->following this statement there are all the input strings, that will be executed one at a time.
The program will give one output for each input string. The output can be:
-'0': when the string cannot be accepted (does not belong to the language specified in the transitions);
-'1': when the string is accepted (does belong to the language specified in the transitions);
-'U': when the program exceeds the maximun number of moves, whether the string is to accept or to refuse.
