## SKIBC combinator calculus implemented in antlr4, testing factorial, map, fold-left

### SKIBC combinators

```
Sxyz = xz(yz)
Kxy = x  
Ix = x 
Bxyz = x(yz)
Cxyz = xzy
```

### Running the tests 

unzip [SKIBC-win64.zip](https://github.com/AkiraHakuta/SKIBC/releases/tag/1.0)  

Open `Dos Command Prompt`  
from `C:/.../SKIBC


```
/* test1.txt */

//booleans
[tru] := K;
[fls] := (KI);

//pair
[pair] := (BC(CI));
[fst] := (CI[tru]);
[snd] := (CI[fls]);

[pair_xy] := [pair]xy;
[fst_pair_xy] = [fst][pair_xy];
[snd_pair_xy] = [snd][pair_xy];

```

``` 
> skibc.exe test1.txt 

[tru] := K;
[fls] := (KI);
[pair] := (BC(CI));
[fst] := (CI[tru]);
[snd] := (CI[fls]);
[pair_xy] := [pair]xy;
[fst_pair_xy] = x;
[snd_pair_xy] = y;
```


```
> skibc.exe test1.txt -t 

   0: [tru] := K;
   1: K;

   0: [fls] := (KI);
   1: (KI);

   0: [pair] := (BC(CI));
   1: (BC(CI));

   0: [fst] := (CI[tru]);
   1: (CIK);
   2: (CIK);

   0: [snd] := (CI[fls]);
   1: (CI((KI)));
   2: (CI(KI));

   0: [pair_xy] := [pair]xy;
   1: ((BC(CI)))xy;
   2: C((CI)x)y;
   3: C((CI)x)y;

   0: [fst_pair_xy] = [fst][pair_xy];
   1: ((CIK))(C((CI)x)y);
   2: I(C((CI)x)y)K;
   3: (C((CI)x)y)K;
   4: ((CI)x)Ky;
   5: IKxy;
   6: Kxy;
   7: x;
   8: x;

   0: [snd_pair_xy] = [snd][pair_xy];
   1: ((CI(KI)))(C((CI)x)y);
   2: I(C((CI)x)y)(KI);
   3: (C((CI)x)y)(KI);
   4: ((CI)x)(KI)y;
   5: I(KI)xy;
   6: (KI)xy;
   7: Iy;
   8: y;
   9: y;
```

```
/* test2.txt */

///fixedpoint combinators
[Y] ::= (B(SII)(CB(SII)));
[Z] ::= (B(SII)(CB(SII)));
[T] ::= (B(SI)(SII))(B(SI)(SII));
//The simplest fixed-point combinator, found by John Tromp, is
[Y''] ::= (SCI)(SB(C(BS(CI))I));

//booleans
[tru] := K;
[fls] := (KI);

//church numerals
[0] := [fls];
[succ] := (SB);
[1] := [succ][0];
[2] := [succ][1];
[3] := [succ][2];
[4] := [succ][3];
[5] := [succ][4];
[add] := (BS(BB));

//pairs
[pair] := (BC(CI));
[fst] := (CI[tru]);
[snd] := (CI[fls]);

//lists
[cons] := [pair];
[head] := [fst];
[tail] := [snd];
[nil] := (K[tru]);
[isnil] := (CI((K(K[fls]))));

//list example
[list3241] := [cons][3]([cons][2]([cons][4]([cons][1][nil])));

[sum_list] := (B(S(C[isnil][0]))(B(S(B[add][head]))(CB[tail])));
[sum_list'] := (B(S(C[isnil][0]))(B(S(B[add][head]))(C(BB(SII))[tail])));

[sum_list3241_xy] = [Y''][sum_list][list3241]xy;
//[sum_list3241_xy] = [sum_list'][sum_list'][list3241]xy;
```

``` 
> skibc.exe test2.txt 

[Y] ::= (B(SII)(CB(SII)));
[Z] ::= (B(SII)(CB(SII)));
[T] ::= (B(SI)(SII))(B(SI)(SII));
[Y''] ::= (SCI)(SB(C(BS(CI))I));
....
....
[list3241] := [cons][3]([cons][2]([cons][4]([cons][1][nil])));
[sum_list] := (B(S(C[isnil][0]))(B(S(B[add][head]))(CB[tail])));
[sum_list'] := (B(S(C[isnil][0]))(B(S(B[add][head]))(C(BB(SII))[tail])));
[sum_list3241_xy] = x(x(x(x(x(x(x(x(x(xy)))))))));
[Finished in 6.3s]
``` 


test3.txt (factorial) 4!  [Finished in 20.3s]  
test4.txt (map) [Finished in 28.9s]  
test5.txt (fold_left) [Finished in 67.3s] 

```
          lambda term                                            SKIBC combinators
[pair] := \x.\y.\f.(fxy);   -- lambda2skibc.exe -->    [pair] := (BC(CI));
``` 

see [lambda2SKIBC](https://github.com/AkiraHakuta/lambda2SKIBC)


``` 
[name]   = M   -- skibc.exe -->  [name]  =  N  (M is evaluated to N)    
[name]  := M   -- skibc.exe -->  [name] :=  M  (M is evaluated)
[name] ::= M   -- skibc.exe -->  [name] ::= M  (M is not evaluated)
```


### Building (Windows only)   
<ol>
<li>

Install [mingw-w64](https://www.mingw-w64.org/downloads/)  

</li>
<li>

Install [cmake](https://cmake.org/download/)   
 
</li>
<li>

Install antlr4 of the Cpp target  
see [antlr4_Cpp_examples](https://github.com/AkiraHakuta/antlr4_Cpp_examples)  

</li>

Compile   
open Dos Command Prompt  
from `C:/.../SKIBC`  

```
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" ..
> mingw32-make.exe  
```
</li>  
</ol>


