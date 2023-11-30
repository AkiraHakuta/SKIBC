grammar skibc;

toplevel
    : (command ';')+ 
    ;

command
    : term                       # c_term
    | sq '=' term                # c_sq_eq_term
    | sq ':=' term               # c_sq_ceq_term
    | sq '::=' term              # c_sq_cceq_term
    | 'putStr' '(' dqString ')'  # c_dq_string
    | 'NL'                       # c_newline
    ;

term
    : sub                 # t_sub
    | konst               # t_konst
    | id                  # t_id 
    | comp                # t_comp
    | flip                # t_flip
    | aterm               # t_a
    | term aterm          # t_app_a
    ;

aterm      
    : s                   # a_s 
    | k                   # a_k 
    | i                   # a_i  
    | b                   # a_b
    | c                   # a_c
    | var                 # a_var
    | sq                  # a_sq
    | '(' '(' term ')' ')'# a_dparen
    |  '(' term ')'       # a_paren
    ;
 

sub : sub1 aterm          # sub_sa
    | '(' sub ')'         # sub_paren
    ;

sub1
    : sub0 aterm          # sub1_sa
    | '(' sub1 ')'        # sub1_paren
    ;

sub0 
    : s aterm             # sub0_sa
    | '(' sub0 ')'        # sub0_paren
    ;

konst : konst0 aterm      # konst_ka
    | '(' konst ')'       # konst_paren
    ;

konst0 
    : k aterm             # konst0_ka
    | '(' konst0 ')'      # konst0_paren
    ;
    
id : i aterm              # id_ia
    | '(' id ')'          # id_paren
    ;

comp : comp1 aterm        # comp_ca
    | '(' comp ')'        # comp_paren
    ;

comp1
    : comp0 aterm         # comp1_ca
    | '(' comp1 ')'       # comp1_paren
    ;

comp0 
    : b aterm             # comp0_ba
    | '(' comp0 ')'       # comp0_paren
    ;

flip : flip1 aterm        # flip_fa
    | '(' flip ')'        # flip_paren
    ;

flip1
    : flip0 aterm         # flip1_fa
    | '(' flip1 ')'       # flip1_paren
    ;

flip0 
    : c aterm             # flip0_ca
    | '(' flip0 ')'       # flip0_paren
    ;


s : 'S'
  | '(' s ')'
  ;

k : 'K'
  | '(' k ')'
  ;

i : 'I'
  | '(' i ')'
  ; 
        
b : 'B'
  | '(' b ')'
  ; 

c : 'C'
  | '(' c ')'
  ; 

var : LCID;
sq : SqStr;
dqString : StringLiteral;


LCID : [a-z];
SqStr : '[' [a-zA-Z0-9_']+ ']';
StringLiteral : '"' (~["])* '"';
WS : [ \t\n\r]+                               -> skip;
COMMENT : '/*' .*? '*/'                       -> skip;
SL_COMMENT :  '//' .*? '\n'                   -> skip;
