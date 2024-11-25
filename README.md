## A implementation of SKIBCS'B'C' combinator calculus using binary tree 


### SKIBCS'B'C' combinator

```
Ix = x
Kfx = f  
Sfgx = (fx)(gx)    (=fx(gx))
Bfgx = f(gx)
Cfgx = (fx)g       (=fxg)
S'ufgx = u(fx)(gx)
B'ufgx = uf(gx) 
C'ufgx = u(fx)g
```

### Combinator expressions can be represented as a binary tree

the next expression is "not x"
``` 
C(CI(KI))Kx

 -- conversion to binary tree -->

    r---x
---
   |    r---K
    l---
       |            r---I
       |        r---
       |       |    l---K
       |    r---
       |   |   |    r---I
       |   |    l---
       |   |        l---C
        l---
            l---C
```

### Running the tests 

unzip [SKIBC-win64.zip](https://github.com/AkiraHakuta/SKIBC/releases)   

Open `Dos Command Prompt`  

``` 
/* test1.txt */

Ix;
Kfx;
Sfgx;
Bfgx;
Cfgx;
S'ufgx;
B'ufgx;
C'ufgx;
```

```
> skibc.exe test1.txt -t

trace:

Ix

 -- conversion to binary tree -->

    r---x
---
    l---I

 -- reduction -->

---x


Kfx

 -- conversion to binary tree -->

    r---x
---
   |    r---f
    l---
        l---K

 -- reduction -->

---f


Sfgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
            l---S

 -- reduction -->

        r---x
    r---
   |    l---g
---
   |    r---x
    l---
        l---f


Bfgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
            l---B

 -- reduction -->

        r---x
    r---
   |    l---g
---
    l---f


Cfgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
            l---C

 -- reduction -->

    r---g
---
   |    r---x
    l---
        l---f


S'ufgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
           |    r---u
            l---
                l---S'

 -- reduction -->

        r---x
    r---
   |    l---g
---
   |        r---x
   |    r---
   |   |    l---f
    l---
        l---u


B'ufgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
           |    r---u
            l---
                l---B'

 -- reduction -->

        r---x
    r---
   |    l---g
---
   |    r---f
    l---
        l---u


C'ufgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
           |    r---u
            l---
                l---C'

 -- reduction -->

    r---g
---
   |        r---x
   |    r---
   |   |    l---f
    l---
        l---u
```



```
/* test2.txt (reverse xy) */

S(K(SI))Kxy;

```

``` 
> skibc.exe test2.txt -t

trace:

S(K(SI))Kxy

 -- conversion to binary tree -->

    r---y
---
   |    r---x
    l---
       |    r---K
        l---
           |            r---I
           |        r---
           |       |    l---S
           |    r---
           |   |    l---K
            l---
                l---S

 -- reduction -->

    r---y
---
   |        r---x
   |    r---
   |   |    l---K
    l---
       |    r---x
        l---
           |        r---I
           |    r---
           |   |    l---S
            l---
                l---K

 -- reduction -->

        r---y
    r---
   |   |    r---x
   |    l---
   |        l---K
---
   |    r---y
    l---
        l---I

 -- reduction -->

    r---x
---
    l---y
``` 

``` 
/* test3.txt (addition) */

//Scott encoding

//Booleans
[tru] = K;
[fls] = (KI);

//Numbers
[0] = K;
[succ] = (BK(CI));
[1] = [succ][0];
[2] = [succ][1];
[3] = [succ][2];
[iszero] = (C(CI[tru])(K[fls]));
[pred] = (C(CI[0])I);

//Addtion (pattern matching)
[add] := (CS(B'B[succ](C[add])));

[2+3] = [add][2][3];
```  

```
> skibc.exe test3.txt 

result (binary tree):

[tru] =
---K

[fls] =
    r---I
---
    l---K

[0] =
---K

[succ] =
        r---I
    r---
   |    l---C
---
   |    r---K
    l---
        l---B

[1] =
        r---K
    r---
   |   |    r---I
   |    l---
   |        l---C
---
    l---K

[2] =
                r---K
            r---
           |   |    r---I
           |    l---
           |        l---C
        r---
       |    l---K
    r---
   |   |    r---I
   |    l---
   |        l---C
---
    l---K

[3] =
                        r---K
                    r---
                   |   |    r---I
                   |    l---
                   |        l---C
                r---
               |    l---K
            r---
           |   |    r---I
           |    l---
           |        l---C
        r---
       |    l---K
    r---
   |   |    r---I
   |    l---
   |        l---C
---
    l---K

[iszero] =
            r---I
        r---
       |    l---K
    r---
   |    l---K
---
   |        r---K
   |    r---
   |   |   |    r---I
   |   |    l---
   |   |        l---C
    l---
        l---C

[pred] =
    r---I
---
   |        r---K
   |    r---
   |   |   |    r---I
   |   |    l---
   |   |        l---C
    l---
        l---C

[add] :=
            r---[add]
        r---
       |    l---C
    r---
   |   |    r---[succ]
   |    l---
   |       |    r---B
   |        l---
   |            l---B'
---
   |    r---S
    l---
        l---C

[2+3] =
                                        r---K
                                    r---
                                   |   |    r---I
                                   |    l---
                                   |        l---C
                                r---
                               |    l---K
                            r---
                           |   |    r---I
                           |    l---
                           |        l---C
                        r---
                       |    l---K
                    r---
                   |   |    r---I
                   |    l---
                   |        l---C
                r---
               |    l---K
            r---
           |   |    r---I
           |    l---
           |        l---C
        r---
       |    l---K
    r---
   |   |    r---I
   |    l---
   |        l---C
---
    l---K
```


```
                                                reducted?   displayed?
[name]    = M  -- skibc.exe --> [name]   = N       Y           Y
[name]   := M  -- skibc.exe --> [name]  := M       N           Y       
[name]   |= M  -- skibc.exe --> 　　　　　　        Y           N
[name]  |:= M  -- skibc.exe -->                    N           N         

``` 

```
          lambda term                               SKIBCS'B'C' combinators
[pair] |= \x.\y.\f.(fxy);   -- lambda2c.exe -->    [pair] |= (BC(CI));
``` 


see [Lambda2Combinator](https://github.com/AkiraHakuta/Lambda2Combinator)

```
//header.h

//Booleans
[tru] |= K;
[fls] |= (KI);
[and] |= (CC[fls]);
[or] |= (C(CI[tru]));
[not] |= (C(CI[fls])[tru]);

//Scott natural numbers
[0] |= [tru];
[succ] |= (BK(CI));
[1] |= [succ][0];
[2] |= [succ][1];
[3] |= [succ][2];
[4] |= [succ][3];
[5] |= [succ][4];
[6] |= [succ][5];
[7] |= [succ][6];
[8] |= [succ][7];
[9] |= [succ][8];
[10] |= [succ][9];
[iszero] |= (C(CI[tru])(K[fls]));
[pred] |= (C(CI[0])I);

//Arithmetic operations
[add] |:= (CS(B'B[succ](C[add])));
[mult] |:= (C(CB'[0])(S(B'[add])(C[mult])));
[sub] |:= (S'C(CI)(B[sub][pred]));
[power] |:= (B'C(CI[1])(S(B'[mult])[power]));

//List
[cons] |= (B'BK(BC(CI)));
[nil] |= K;
[isnil] |= (C(CI[tru])(K(K[fls])));
[head] |= (C(CIK)K);
[tail] |= (C(CI[nil])(KI));
[pick] |:= (C(CS'[head])(B'C[pick][tail]));

//Pair
[pair] |= (BC(CI));
[fst] |= (CIK);
[snd] |= (CI(KI));

//etc
[fact] |:= (S(CI[1])(C(B'[mult])[fact]));
[fib] |:= (S(C'[iszero][pred][1])(S'[add](B[fib][pred])(B[fib](B[pred][pred]))));
[isOdd] |:= (S(C[iszero][fls])(B[isEven][pred]));
[isEven] |:= (S(C[iszero][tru])(B[isOdd][pred]));

//[list2431] := [cons][2]([cons][4]([cons][3]([cons][1][nil])));
```

```
/* test4.txt (list) */
#include "header.h"

[list2431] := [cons][2]([cons][4]([cons][3]([cons][1][nil])));

[pick_2_list2431] = [pick][2][list2431];
```

```
> skibc.exe test4.txt

result (binary tree):

[list2431] :=
                r---[nil]
            r---
           |   |    r---[1]
           |    l---
           |        l---[cons]
        r---
       |   |    r---[3]
       |    l---
       |        l---[cons]
    r---
   |   |    r---[4]
   |    l---
   |        l---[cons]
---
   |    r---[2]
    l---
        l---[cons]

[pick_2_list2431] =
                        r---K
                    r---
                   |   |    r---I
                   |    l---
                   |        l---C
                r---
               |    l---K
            r---
           |   |    r---I
           |    l---
           |        l---C
        r---
       |    l---K
    r---
   |   |    r---I
   |    l---
   |        l---C
---
    l---K
``` 

  
test5.txt (factorial)  
test6.txt (odd or even?)  
test7.txt (Fibonacci number) 


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

### References  

-  D.A. Turner, Another algorithm for bracket abstraction (1979)
-  Gert Smolka, [Untyped Lambda Calculus Lecture Notes](https://www.ps.uni-saarland.de/courses/sem-ws15/ulc.pdf)
-  Wikipedia [Combinatory logic](https://en.wikipedia.org/wiki/Combinatory_logic)