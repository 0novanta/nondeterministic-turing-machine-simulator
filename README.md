# nondeterministic-turing-machine-simulator
This program implements a nondeterministic Turing machine simulator in C.

This program accept files written in the following way:

tr<br/>
0 a b 1 R<br/>
0 a c 1 R<br/>
1 a d 0 R<br/>
acc<br/>
0<br/>
max<br/>
50<br/>
run<br/>
a<br/>
aa<br/>
aaaaaaaaaa<br/>
aaaaaaa<br/>
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa<br/>


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

'tr'--->following this statement there are all the transitions that describe the turing machine.
'acc'--->following this statement there are all the acceptance states.
'max'--->following this statement there is the maximum number of moves, this is done in order to prevent infinite loops.
'run'--->following this statement there are all the input strings, that will be executed one at a time.
The program will give one output for each input string. The output can be:
-'0': when the string cannot be accepted (does not belong to the language specified in the transitions);
-'1': when the string is accepted (does belong to the language specified in the transitions);
-'U': when the program exceeds the maximun number of moves, whether the string is to accept or to refuse.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Example:
taken the single instruction:
0 a b 1 L
-'0' means the starting state of this instruction;
-'a' is the (seen) character the machine sees whilst being in the starting state (0 in this example);
-'b' is the character supposed to be written after reading the seen character, replacing it in the same spot;
-'1' is the new state, and will be the starting state of another instruction (if not this state might be an accptance state);
-'L' means to which spot the machine would move, meaning the machine will read its content (R for right, S stop {it stays in the same spot});

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


This program example will accept all the strings even multiple of the string 'aa' and it will print strings multiple of 'bcd' and 'cbd' and their mixes,<br/> because of his nondetermination.<br/>

I've done this for school purpose.


