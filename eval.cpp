#include "skibc.h"


any EVAL::visitToplevel(skibcParser::ToplevelContext *ctx) {
    if (top)    
        for (int i = 0; i < ctx->command().size(); i++)
            comm.push_back(any_cast<array<string, 4>>(visit(ctx->command(i))));      
    return 1;
}


any EVAL::visitC_term(skibcParser::C_termContext *ctx){ 
    any result;
    array<string, 4> arr;
    string t;
    if (top){
        arr[CommType] = to_string(Term);
        arr[TermText] = ctx->getText();
        arr[Sb] = "";
        arr[Eq] = "";
        result = arr;
    }
    else {
        
        result = any_cast<string>(visit(ctx->term()));
        
    }        
    return result;
}


any EVAL::visitC_sq_eq_term(skibcParser::C_sq_eq_termContext *ctx){
    any result;
    array<string, 4> arr;
    string t;
    if (top){
        arr[CommType] = to_string(SbEqTerm);
        arr[TermText] = ctx->term()->getText();
        arr[Sb] = ctx->sq()->getText();
        arr[Eq] = " = ";
        result = arr;
    }
    else         
        result = any_cast<string>(visit(ctx->term()));              
    return result;
}


any EVAL::visitC_sq_ceq_term(skibcParser::C_sq_ceq_termContext *ctx){
    any result;
    array<string, 4> arr;
    if (top){
        arr[CommType] = to_string(SbCEqTerm);
        arr[TermText] = ctx->term()->getText();
        arr[Sb] = ctx->sq()->getText();
        arr[Eq] = " := ";
        result = arr;
    }
    else         
        result = any_cast<string>(visit(ctx->term()));                    
    return result;
}


any EVAL::visitC_sq_cceq_term(skibcParser::C_sq_cceq_termContext *ctx){
    any result;
    array<string, 4> arr;
    if (top){
        arr[CommType] = to_string(SbCCEqTerm);
        arr[TermText] = ctx->term()->getText();
        arr[Sb] = ctx->sq()->getText();
        arr[Eq] = " ::= ";
        result = arr;
    }
    else        
        result = ctx->term()->getText();                 
    return result;
}


any EVAL::visitC_dq_string(skibcParser::C_dq_stringContext *ctx){
    any result;
    array<string, 4> arr;
    if (top){
        arr[CommType] = to_string(PutStr);
        arr[TermText] = ctx->getText();
        arr[Sb] = "";
        arr[Eq] = "";
        result = arr;
    }
    else
        result = any_cast<string>(visit(ctx->dqString()));
    return result;    
}


any EVAL::visitC_newline(skibcParser::C_newlineContext *ctx){
    any result;
    array<string, 4> arr;
    if (top){
        arr[CommType] = to_string(NewLine);
        arr[TermText] = ctx->getText();
        arr[Sb] = "";
        arr[Eq] = "";
        result = arr;
    }
    else
        result = "";
    return result;   
}


any EVAL::visitT_app_a(skibcParser::T_app_aContext *ctx){ 
    string left_t = any_cast<string>(visit(ctx->term()));
    string right_t =  any_cast<string>(visit(ctx->aterm()));
    return left_t + right_t;
}


any EVAL::visitT_a(skibcParser::T_aContext *ctx){ 
    return any_cast<string>(visit(ctx->aterm()));
}


any EVAL::visitT_sub(skibcParser::T_subContext *ctx){ 
    return any_cast<string>(visit(ctx->sub()));
}


any EVAL::visitT_konst(skibcParser::T_konstContext *ctx){
    return any_cast<string>(visit(ctx->konst()));
}


any EVAL::visitT_id(skibcParser::T_idContext *ctx){ 
    return any_cast<string>(visit(ctx->id()));
}


any EVAL::visitT_comp(skibcParser::T_compContext *ctx){ 
    return any_cast<string>(visit(ctx->comp()));
}


any EVAL::visitT_flip(skibcParser::T_flipContext *ctx){ 
    return any_cast<string>(visit(ctx->flip()));
}


any EVAL::visitA_s(skibcParser::A_sContext *ctx){ 
    return any_cast<string>(visit(ctx->s()));
}


any EVAL::visitA_k(skibcParser::A_kContext *ctx){ 
    return any_cast<string>(visit(ctx->k()));
}


any EVAL::visitA_i(skibcParser::A_iContext *ctx){ 
    return any_cast<string>(visit(ctx->i()));
}


any EVAL::visitA_b(skibcParser::A_bContext *ctx){ 
    return any_cast<string>(visit(ctx->b()));
}


any EVAL::visitA_c(skibcParser::A_cContext *ctx){ 
    return any_cast<string>(visit(ctx->c()));
}


any EVAL::visitA_var(skibcParser::A_varContext *ctx){ 
    return any_cast<string>(visit(ctx->var()));
}


any EVAL::visitA_sq(skibcParser::A_sqContext *ctx) {    
    string sb = ctx->getText();
    string result_str;
    if (sq_term_map.find(sb) == sq_term_map.end()){
        if(not_found_sb_eval){
            cout << sb << " is not found" << endl;
            exit(1);        
        }
        else{
            auto it = find(cbegin(not_found_sb), cend(not_found_sb), sb);
            if (it == cend(not_found_sb)) {
                not_found_sb.push_back(sb);
                cout << sb << " is not found, continue ..." << endl;
            }
            result_str = sb;
        }
    }
    else if (sq_term_map[sb] != sb){
        *changed_ptr = true;
        result_str = sq_term_map[sb];
        if (result_str.length() != 1)
            result_str = "(" + result_str + ")";
    }
    return result_str;
}


any EVAL::visitA_dparen(skibcParser::A_dparenContext *ctx){ 
    string result_str = any_cast<string>(visit(ctx->term()));
    if (result_str.length() != 1 )
        result_str = "(" + result_str + ")";
    return result_str;
}


any EVAL::visitA_paren(skibcParser::A_parenContext *ctx){ 
    string result_str = any_cast<string>(visit(ctx->term()));
    if (result_str.length() != 1 )
        result_str = "(" + result_str + ")";
    return result_str;
}


any EVAL::visitSub_sa(skibcParser::Sub_saContext *ctx) {
     /* S p.second p.first t */
    *changed_ptr = true;
    string t = any_cast<string>(visit(ctx->aterm()));
    pair<string, string> p = any_cast<pair<string, string>>(visit(ctx->sub1()));
    return   p.second + t + "(" + p.first + t + ")";
}


any EVAL::visitSub_paren(skibcParser::Sub_parenContext *ctx) {
    return visit(ctx->sub());
}


any EVAL::visitSub1_sa(skibcParser::Sub1_saContext *ctx) {
    pair<string, string> p;
    p.first = any_cast<string>(visit(ctx->aterm()));
    p.second = any_cast<string>(visit(ctx->sub0()));
    return p;
}


any EVAL::visitSub1_paren(skibcParser::Sub1_parenContext *ctx) {
    return visit(ctx->sub1());
}


any EVAL::visitSub0_sa(skibcParser::Sub0_saContext *ctx) {
    return visit(ctx->aterm());
}


any EVAL::visitSub0_paren(skibcParser::Sub0_parenContext *ctx) {
    return visit(ctx->sub0());
}


any EVAL::visitKonst_ka(skibcParser::Konst_kaContext *ctx) {
    *changed_ptr = true;
    return any_cast<string>(visit(ctx->konst0()));
}


any EVAL::visitKonst_paren(skibcParser::Konst_parenContext *ctx) {
    return visit(ctx->konst());
}


any EVAL::visitKonst0_ka(skibcParser::Konst0_kaContext *ctx) {
    return visit(ctx->aterm());
}


any EVAL::visitKonst0_paren(skibcParser::Konst0_parenContext *ctx) {
    return visit(ctx->konst0());
}


any EVAL::visitId_ia(skibcParser::Id_iaContext *ctx) {
    *changed_ptr = true;
    return any_cast<string>(visit(ctx->aterm()));
}


any EVAL::visitId_paren(skibcParser::Id_parenContext *ctx) {
    return visit(ctx->id());
}


any EVAL::visitComp_ca(skibcParser::Comp_caContext *ctx) {
     /* B p.second p.first t */
    *changed_ptr = true;
    string t = any_cast<string>(visit(ctx->aterm()));
    pair<string, string> p = any_cast<pair<string, string>>(visit(ctx->comp1()));
    return   p.second + "(" + p.first + t + ")";
}


any EVAL::visitComp_paren(skibcParser::Comp_parenContext *ctx) {
    return visit(ctx->comp());
}


any EVAL::visitComp1_ca(skibcParser::Comp1_caContext *ctx) {
    pair<string, string> p;
    p.first = any_cast<string>(visit(ctx->aterm()));
    p.second = any_cast<string>(visit(ctx->comp0()));
    return p;
}


any EVAL::visitComp1_paren(skibcParser::Comp1_parenContext *ctx) {
    return visit(ctx->comp1());
}


any EVAL::visitComp0_ba(skibcParser::Comp0_baContext *ctx) {
    return visit(ctx->aterm());
}


any EVAL::visitComp0_paren(skibcParser::Comp0_parenContext *ctx) {
    return visit(ctx->comp0());
}


any EVAL::visitFlip_fa(skibcParser::Flip_faContext *ctx) {
     /* C p.second p.first t */
    *changed_ptr = true;
    string t = any_cast<string>(visit(ctx->aterm()));
    pair<string, string> p = any_cast<pair<string, string>>(visit(ctx->flip1()));
    return   p.second  + t + p.first;
}


any EVAL::visitFlip_paren(skibcParser::Flip_parenContext *ctx) {
    return visit(ctx->flip());
}


any EVAL::visitFlip1_fa(skibcParser::Flip1_faContext *ctx) {
    pair<string, string> p;
    p.first = any_cast<string>(visit(ctx->aterm()));
    p.second = any_cast<string>(visit(ctx->flip0()));
    return p;
}


any EVAL::visitFlip1_paren(skibcParser::Flip1_parenContext *ctx) {
    return visit(ctx->flip1());
}


any EVAL::visitFlip0_ca(skibcParser::Flip0_caContext *ctx) {
    return visit(ctx->aterm());
}


any EVAL::visitFlip0_paren(skibcParser::Flip0_parenContext *ctx) {
    return visit(ctx->flip0());
}


any EVAL::visitS(skibcParser::SContext *context) {
    return string("S");
}


any EVAL::visitK(skibcParser::KContext *context) {
    return string("K");
}


any EVAL::visitI(skibcParser::IContext *context) {
    return string("I");
}


any EVAL::visitB(skibcParser::BContext *context) {
    return string("B");
}


any EVAL::visitC(skibcParser::CContext *context) {
    return string("C");
}


any EVAL::visitVar(skibcParser::VarContext *ctx) {
    return ctx->getText();
}


any EVAL::visitSq(skibcParser::SqContext *ctx) {
    return ctx->getText();
}


any EVAL::visitDqString(skibcParser::DqStringContext *ctx) {
    string result_str = ctx->getText();
    (result_str.erase(0, 1)).pop_back();
    return result_str;
}
