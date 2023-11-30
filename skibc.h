#ifndef SKIBC_H
#define SKIBC_H


#include "antlr4-runtime.h"
#include "skibcLexer.h"
#include "skibcParser.h"
#include "skibcVisitor.h"
#include <array>

using namespace antlr4;
using namespace tree;
using namespace std;



string indent_sp(int size);


enum{CommType, Sb, Eq, TermText};

enum{Term, SbEqTerm, SbCEqTerm, SbCCEqTerm, PutStr, NewLine};

class EVAL : public skibcVisitor{    
    public:
    bool* changed_ptr;
    vector<array<string,4>> comm;
    map<string, string> sq_term_map;
    bool top = true;
    bool not_found_sb_eval;
    vector<string> not_found_sb;
    
    

    any visitToplevel(skibcParser::ToplevelContext *context);

    any visitC_term(skibcParser::C_termContext *context);

    any visitC_sq_eq_term(skibcParser::C_sq_eq_termContext *context); 

    any visitC_sq_ceq_term(skibcParser::C_sq_ceq_termContext *context);  

    any visitC_sq_cceq_term(skibcParser::C_sq_cceq_termContext *context);

    any visitC_dq_string(skibcParser::C_dq_stringContext *context);

    any visitC_newline(skibcParser::C_newlineContext *context);  

    any visitT_app_a(skibcParser::T_app_aContext *context);

    any visitT_a(skibcParser::T_aContext *context);

    any visitT_sub(skibcParser::T_subContext *context);

    any visitT_konst(skibcParser::T_konstContext *context);

    any visitT_id(skibcParser::T_idContext *context);

    any visitT_comp(skibcParser::T_compContext *context);

    any visitT_flip(skibcParser::T_flipContext *context);

    any visitA_s(skibcParser::A_sContext *context);

    any visitA_k(skibcParser::A_kContext *context);

    any visitA_i(skibcParser::A_iContext *context);

    any visitA_b(skibcParser::A_bContext *context);

    any visitA_c(skibcParser::A_cContext *context);

    any visitA_var(skibcParser::A_varContext *context);

    any visitA_sq(skibcParser::A_sqContext *context);

    any visitA_dparen(skibcParser::A_dparenContext *context);

    any visitA_paren(skibcParser::A_parenContext *context);

    any visitSub_sa(skibcParser::Sub_saContext *context);

    any visitSub_paren(skibcParser::Sub_parenContext *context);

    any visitSub1_sa(skibcParser::Sub1_saContext *context);

    any visitSub1_paren(skibcParser::Sub1_parenContext *context);

    any visitSub0_sa(skibcParser::Sub0_saContext *context);

    any visitSub0_paren(skibcParser::Sub0_parenContext *context);

    any visitKonst_ka(skibcParser::Konst_kaContext *context);

    any visitKonst_paren(skibcParser::Konst_parenContext *context);

    any visitKonst0_ka(skibcParser::Konst0_kaContext *context);

    any visitKonst0_paren(skibcParser::Konst0_parenContext *context);

    any visitId_ia(skibcParser::Id_iaContext *context);

    any visitId_paren(skibcParser::Id_parenContext *context);

    any visitComp_ca(skibcParser::Comp_caContext *context);

    any visitComp_paren(skibcParser::Comp_parenContext *context);

    any visitComp1_ca(skibcParser::Comp1_caContext *context);

    any visitComp1_paren(skibcParser::Comp1_parenContext *context);

    any visitComp0_ba(skibcParser::Comp0_baContext *context);

    any visitComp0_paren(skibcParser::Comp0_parenContext *context);

    any visitFlip_fa(skibcParser::Flip_faContext *context);

    any visitFlip_paren(skibcParser::Flip_parenContext *context);

    any visitFlip1_fa(skibcParser::Flip1_faContext *context);

    any visitFlip1_paren(skibcParser::Flip1_parenContext *context);

    any visitFlip0_ca(skibcParser::Flip0_caContext *context);

    any visitFlip0_paren(skibcParser::Flip0_parenContext *context);

    any visitS(skibcParser::SContext *context);

    any visitK(skibcParser::KContext *context);

    any visitI(skibcParser::IContext *context);

    any visitB(skibcParser::BContext *context);

    any visitC(skibcParser::CContext *context);

    any visitVar(skibcParser::VarContext *context);

    any visitSq(skibcParser::SqContext *context);

    any visitDqString(skibcParser::DqStringContext *context);
};

#endif  // SKIBC_H