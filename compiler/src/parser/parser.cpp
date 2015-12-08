#ifndef PARSER_IMPL
#define PARSER_IMPL

#include<iostream>
using std::cout;
using std::endl;
#include<utility>
using std::make_pair;
#include "parser.h"
#include "../lexer/lexer.h"
#include "../notimplementederror/notimplementederror.h"
#include "../goto/goto.h"

Parser::Parser(
    const char* sourceFile,
    Lexer *lexer,
    Synthesizer *synthesizer,
    ParseTreeLogger *parseTreeLogger,
    unordered_map<string, Token> *symboltable
){
    this->lexer = lexer;
    this->synthesizer = synthesizer;
    this->parseTreeLogger = parseTreeLogger;
    this->symboltable = symboltable;
    curtoken = lexer->getToken();
}

bool Parser::parse(){
    parseTreeLogger->logEntry("parse");
    try{
        program();
        fillGotoPlaceHolders();
        match(END_OF_FILE);
    } catch (...){
        cout << "caught exception." << endl;
        parseTreeLogger->logExit("parse");
        return false;
    }
    return true;
}

void Parser::fillGotoPlaceHolders(){
    Token curtok;
    list<Goto> gotos;
    while(headLabel != ""){
        curtok = (*symboltable)[headLabel.c_str()];
        gotos = curtok.getListOfGotos();
        while(!gotos.empty()){
            Goto g = gotos.back();
            synthesizer->fillPlaceHolderAddress(g.getHole(), curtok.getAddress());
            gotos.pop_back();
        }
        headLabel = curtok.getPrevLab();
    }
}

void Parser::match(Tag t){
    cout << "Entering Parser::match" << endl;
    cout << "Tag t: " << t << endl;
    cout << "curtoken.getTag(): " << curtoken.getTag() << endl;
    if(curtoken.getTag() == t){
        curtoken = lexer->getToken();
    } else {
        throw "Parser::match failed";
    }
}

void Parser::actual_parameter(){
    parseTreeLogger->logEntry("actual_parameter");
    throw NotImplementedError("actual_parameter");
    parseTreeLogger->logExit("actual_parameter");
}

void Parser::actual_parameter_list(){
    parseTreeLogger->logEntry("actual_parameter_list");
    throw NotImplementedError("actual_parameter_list");
    parseTreeLogger->logExit("actual_parameter_list");
}

void Parser::adding_operator(){
    parseTreeLogger->logEntry("adding_operator");
    throw NotImplementedError("adding_operator");
    parseTreeLogger->logExit("adding_operator");
}

void Parser::apostrophe_image(){
    parseTreeLogger->logEntry("apostrophe_image");
    throw NotImplementedError("apostrophe_image");
    parseTreeLogger->logExit("apostrophe_image");
}

Type Parser::array_type(){
    Type index_t, elem_t;
    parseTreeLogger->logEntry("array_type");
    match(ARRAY);
    match(LBRACKET);
    index_t = index_type();
    /* Let's just ignore this for now.
    while(curtoken.getTag() == COMMA){
        match(COMMA);
        index_type();
    }
    */
    match(RBRACKET);
    match(OF);
    elem_t = component_type();
    index_t.setElemKind(elem_t.getKind());
    index_t.setKind(ARRAY_K);
    parseTreeLogger->logExit("array_type");
    return index_t;
}

void Parser::array_variable(){
    parseTreeLogger->logEntry("array_variable");
    throw NotImplementedError("array_variable");
    parseTreeLogger->logExit("array_variable");
}

void Parser::assignment_statement(){
    parseTreeLogger->logEntry("assignment_statement");
    Type lhs(curtoken.getKind());
    switch(curtoken.getTag()){
        case TK_A_FUNC:
            function_identifier();
            break;
        case TK_A_ARRAY:
            lhs = Type(curtoken.getElemKind());
            variable_access();
            break;
        default:
            synthesizer->genOpCode(PUSH_ADDRESS);
            variable_access();
            break;
    }
    match(ASSIGN);
    Type rhs = expression();
    if(lhs.getKind() != rhs.getKind()){
        throw "Incompatible assignment error";
    }
    switch(lhs.getKind()){
        case STRING_K:
            synthesizer->genOpCode(POP_STRING);
            break;
        case INTEGER_K:
            synthesizer->genOpCode(POP_INTEGER);
            break;
        case REAL_K:
            synthesizer->genOpCode(POP_REAL);
            break;
        case BOOLEAN_K:
            synthesizer->genOpCode(POP_BOOLEAN);
            break;
        default:
            throw "assignment statement not implemented for this type!";
    }
    parseTreeLogger->logExit("assignment_statement");
}

void Parser::base_type(){
    parseTreeLogger->logEntry("base_type");
    throw NotImplementedError("base_type");
    parseTreeLogger->logExit("base_type");
}

void Parser::block(){
    parseTreeLogger->logEntry("block");
    label_declaration_part();
    constant_definition_part();
    type_definition_part();
    variable_declaration_part();
    procedure_and_function_declaration_part();
    statement_part();
    parseTreeLogger->logExit("block");
}

void Parser::Boolean_expression(){
    parseTreeLogger->logEntry("Boolean_expression");
    Type t = expression();
    if(t.getKind() != BOOLEAN_K){
        throw "Syntax error: Boolean expression with non-Boolean result";
    }
    parseTreeLogger->logExit("Boolean_expression");
}

void Parser::bound_identifier(){
    parseTreeLogger->logEntry("bound_identifier");
    throw NotImplementedError("bound_identifier");
    parseTreeLogger->logExit("bound_identifier");
}

void Parser::buffer_variable(){
    parseTreeLogger->logEntry("buffer_variable");
    throw NotImplementedError("buffer_variable");
    parseTreeLogger->logExit("buffer_variable");
}

void Parser::case_constant(){
    parseTreeLogger->logEntry("case_constant");
    throw NotImplementedError("case_constant");
    parseTreeLogger->logExit("case_constant");
}

void Parser::case_constant_list(){
    parseTreeLogger->logEntry("case_constant_list");
    throw NotImplementedError("case_constant_list");
    parseTreeLogger->logExit("case_constant_list");
}

void Parser::case_index(){
    parseTreeLogger->logEntry("case_index");
    throw NotImplementedError("case_index");
    parseTreeLogger->logExit("case_index");
}

void Parser::case_list_element(){
    parseTreeLogger->logEntry("case_list_element");
    throw NotImplementedError("case_list_element");
    parseTreeLogger->logExit("case_list_element");
}

void Parser::case_statement(){
    parseTreeLogger->logEntry("case_statement");
    match(CASE);
    Type t = expression();
    if(t.getKind() != INTEGER_K && t.getKind() != BOOLEAN_K){
        throw "Ordinal type required for case statement control variable!";
    }
    match(OF);
    while(curtoken.getTag() == INT || curtoken.getTag() == BOOLEAN){
    }
    parseTreeLogger->logExit("case_statement");
}

Type Parser::character_string(){
    parseTreeLogger->logEntry("character_string");
    StringToken strtok(curtoken.getLexeme());
    size_t addr = synthesizer->writeStringLiteralToHeader(strtok);
    synthesizer->genOpCode(PUSH_STRING);
    synthesizer->genAddress(addr);
    match(STRING);
    parseTreeLogger->logExit("character_string");
    return Type(STRING_K);
}

Type Parser::component_type(){
    Type t;
    parseTreeLogger->logEntry("component_type");
    t = type_denoter();
    parseTreeLogger->logExit("component_type");
    return t;
}

Type Parser::component_variable(){
    parseTreeLogger->logEntry("component_variable");
    Type t;
    switch(curtoken.getTag()){
        case TK_A_ARRAY:
            t = indexed_variable();
            break;
        default:
            throw "component_variable not implemented for this tag.";
            break;
    }
    parseTreeLogger->logExit("component_variable");
    return t;
}

void Parser::compound_statement(){
    parseTreeLogger->logEntry("compound_statement");
    match(BEGIN);
    statement_sequence();
    match(END);
    parseTreeLogger->logExit("compound_statement");
}

void Parser::conditional_statement(){
    parseTreeLogger->logEntry("conditional_statement");
    switch(curtoken.getTag()){
        case IF:
            if_statement();
            break;
        case CASE:
            case_statement();
            break;
        default:
            throw "syntax error discovered in conditional_statement";
    }
    parseTreeLogger->logExit("conditional_statement");
}

void Parser::conformant_array_parameter_specification(){
    parseTreeLogger->logEntry("conformant_array_parameter_specification");
    throw NotImplementedError("conformant_array_parameter_specification");
    parseTreeLogger->logExit("conformant_array_parameter_specification");
}

void Parser::conformant_array_schema(){
    parseTreeLogger->logEntry("conformant_array_schema");
    throw NotImplementedError("conformant_array_schema");
    parseTreeLogger->logExit("conformant_array_schema");
}

void Parser::constant(){
    parseTreeLogger->logEntry("constant");
    throw NotImplementedError("constant");
    parseTreeLogger->logExit("constant");
}

void Parser::constant_definition(){
    parseTreeLogger->logEntry("constant_definition");
    throw NotImplementedError("constant_definition");
    parseTreeLogger->logExit("constant_definition");
}

void Parser::constant_definition_part(){
    parseTreeLogger->logEntry("constant_definition_part");
    if(curtoken.getTag() == CONST){
        match(CONST);
        while(curtoken.getTag() == ID){
            constant_definition();
            match(SEMICOLON);
        }
    }
    parseTreeLogger->logExit("constant_definition_part");
}

Type Parser::constant_identifier(){
    parseTreeLogger->logEntry("constant_identifier");
    throw NotImplementedError("constant_identifier");
    parseTreeLogger->logExit("constant_identifier");
}

Type Parser::control_variable(){
    parseTreeLogger->logEntry("control_variable");
    Type t = entire_variable();
    parseTreeLogger->logExit("control_variable");
    return t;
}

void Parser::digit(){
    parseTreeLogger->logEntry("digit");
    throw NotImplementedError("digit");
    parseTreeLogger->logExit("digit");
}

void Parser::digit_sequence(){
    parseTreeLogger->logEntry("digit_sequence");
    throw NotImplementedError("digit_sequence");
    parseTreeLogger->logExit("digit_sequence");
}

void Parser::directive(){
    parseTreeLogger->logEntry("directive");
    throw NotImplementedError("directive");
    parseTreeLogger->logExit("directive");
}

void Parser::domain_type(){
    parseTreeLogger->logEntry("domain_type");
    throw NotImplementedError("domain_type");
    parseTreeLogger->logExit("domain_type");
}

void Parser::else_part(){
    parseTreeLogger->logEntry("else_part");
    match(ELSE);
    statement();
    parseTreeLogger->logExit("else_part");
}

void Parser::empty_statement(){
    parseTreeLogger->logEntry("empty_statement");
    parseTreeLogger->logExit("empty_statement");
}

Type Parser::entire_variable(){
    parseTreeLogger->logEntry("entire_variable");
    Type t = variable_identifier();
    parseTreeLogger->logExit("entire_variable");
    return t;
}

void Parser::enumerated_type(){
    parseTreeLogger->logEntry("enumerated_type");
    throw NotImplementedError("enumerated_type");
    parseTreeLogger->logExit("enumerated_type");
}

Type Parser::expression(){
    parseTreeLogger->logEntry("expression");
    Type t1 = simple_expression(), t2;
    switch(curtoken.getTag()){
        case EQ:
            match(EQ);
            t2 = simple_expression();
            t1 = synthesizer->genEqualityCode(t1, t2);
            break;
        case NEQ:
            match(NEQ);
            t2 = simple_expression();
            t1 = synthesizer->genInequalityCode(t1, t2);
            break;
        case LT:
            match(LT);
            t2 = simple_expression();
            t1 = synthesizer->genLessThanCode(t1, t2);
            break;
        case GT:
            match(GT);
            t2 = simple_expression();
            t1 = synthesizer->genGreaterThanCode(t1, t2);
            break;
        case LEQ:
            match(LEQ);
            t2 = simple_expression();
            t1 = synthesizer->genLessOrEqualCode(t1, t2);
            break;
        case GEQ:
            match(GEQ);
            t2 = simple_expression();
            t1 = synthesizer->genGreaterOrEqualCode(t1, t2);
            break;
        case IN:
            match(curtoken.getTag());
            simple_expression();
            break;
        default:
            break;
    }
    parseTreeLogger->logExit("expression");
    return t1;
}

Type Parser::factor(){
    parseTreeLogger->logEntry("factor");
    Type t;
    switch(curtoken.getTag()){
        case RPAREN:
            break;
        case INT:
        case REAL:
        case STRING:
        case BOOLEAN:
        case TK_A_CONST:
            t = unsigned_constant();
            break;
        case TK_A_FUNC:
            t = function_designator();
            break;
        case LBRACKET:
            t = set_constructor();
            break;
        case LPAREN:
            match(LPAREN);
            t = expression();
            break;
        case NOT:
            match(NOT);
            t = factor();
            break;
        case TK_A_ARRAY:
            t = variable_access();
            synthesizer->genPushVarBackwardsOpcode(t.getKind());
            break;
        default:
            synthesizer->genPushVarOpcode(curtoken.getKind());
            t = variable_access();
            break;
    }
    parseTreeLogger->logExit("factor");
    return t;
}

void Parser::field_designator(){
    parseTreeLogger->logEntry("field_designator");
    throw NotImplementedError("field_designator");
    parseTreeLogger->logExit("field_designator");
}

void Parser::field_designator_identifier(){
    parseTreeLogger->logEntry("field_designator_identifier");
    throw NotImplementedError("field_designator_identifier");
    parseTreeLogger->logExit("field_designator_identifier");
}

void Parser::field_identifier(){
    parseTreeLogger->logEntry("field_identifier");
    throw NotImplementedError("field_identifier");
    parseTreeLogger->logExit("field_identifier");
}

void Parser::field_list(){
    parseTreeLogger->logEntry("field_list");
    throw NotImplementedError("field_list");
    parseTreeLogger->logExit("field_list");
}

void Parser::field_specififer(){
    parseTreeLogger->logEntry("field_specififer");
    throw NotImplementedError("field_specififer");
    parseTreeLogger->logExit("field_specififer");
}

void Parser::file_type(){
    parseTreeLogger->logEntry("file_type");
    throw NotImplementedError("file_type");
    parseTreeLogger->logExit("file_type");
}

void Parser::file_variable(){
    parseTreeLogger->logEntry("file_variable");
    throw NotImplementedError("file_variable");
    parseTreeLogger->logExit("file_variable");
}

Type Parser::final_value(){
    parseTreeLogger->logEntry("final_value");
    Type t = expression();
    parseTreeLogger->logExit("final_value");
    return t;
}

void Parser::fixed_part(){
    parseTreeLogger->logEntry("fixed_part");
    throw NotImplementedError("fixed_part");
    parseTreeLogger->logExit("fixed_part");
}

void Parser::for_statement(){
    bool ascending = true;
    parseTreeLogger->logEntry("for_statement");
    match(FOR);
    synthesizer->genOpCode(PUSH_ADDRESS);
    Type cvt = control_variable();
    size_t controlVariableAddress = synthesizer->getVariableAddress();
    match(ASSIGN);
    Type ivt = initial_value();
    // Check if the type of the initial-value is compatible with
    // the type of the control variable. For now we will simply
    // check that they are the same.
    if(cvt.getKind() != ivt.getKind()){
        throw "Syntax error discovered in for_statement:\nIncompatible control variable and initial value.";
    }
    switch(cvt.getKind()){
        case STRING_K:
            synthesizer->genOpCode(POP_STRING);
            break;
        case INTEGER_K:
            synthesizer->genOpCode(POP_INTEGER);
            break;
        case REAL_K:
            synthesizer->genOpCode(POP_REAL);
            break;
        case BOOLEAN_K:
            synthesizer->genOpCode(POP_BOOLEAN);
            break;
        default:
            throw "assignment statement not implemented for this type!";
    }

    // Generate byte code for checking the loop continuation condition.
    size_t instructionAddress = synthesizer->getInstructionAddress();
    synthesizer->genPushVarOpcode(cvt.getKind());
    synthesizer->genAddress(controlVariableAddress);

    if(curtoken.getTag() == TO){
        match(TO);
    } else if(curtoken.getTag() == DOWNTO){
        ascending = false;
        match(DOWNTO);
    } else {
        throw "Syntax error discovered in for_statement";
    }

    Type fvt = final_value();
    if(cvt.getKind() != fvt.getKind()){
        throw "Syntax error discovered in for_statement:\nIncompatible control variable and final value.";
    }

    // The value of the control variable and the final value are on the
    // stack in this order.
    if(ascending){
        synthesizer->genLessOrEqualCode(cvt, fvt);
    } else {
        synthesizer->genGreaterOrEqualCode(cvt, fvt);
    }

    synthesizer->genOpCode(JUMP_FALSE);
    size_t placeHolder = synthesizer->makePlaceHolderAddress();
    match(DO);

    // Generate byte code for the for_statement's statement.
    statement();

    // Generate byte code to update control variable.
    synthesizer->genOpCode(PUSH_ADDRESS);
    synthesizer->genAddress(controlVariableAddress);
    synthesizer->genPushVarOpcode(cvt.getKind());
    synthesizer->genAddress(controlVariableAddress);
    if(ascending){
        synthesizer->genAddOne(cvt.getKind());
    } else {
        synthesizer->genSubOne(cvt.getKind());
    }
    synthesizer->genPopVarOpcode(cvt.getKind());

    // Generate byte code to jump back to loop continuation
    // condition byte code.
    synthesizer->genOpCode(JUMP);
    synthesizer->genAddress(instructionAddress);

    // Fill in JUMP_FALSE address.
    synthesizer->fillPlaceHolderAddress(placeHolder);

    parseTreeLogger->logExit("for_statement");
}

void Parser::formal_parameter_list(){
    parseTreeLogger->logEntry("formal_parameter_list");
    throw NotImplementedError("formal_parameter_list");
    parseTreeLogger->logExit("formal_parameter_list");
}

void Parser::formal_parameter_section(){
    parseTreeLogger->logEntry("formal_parameter_section");
    throw NotImplementedError("formal_parameter_section");
    parseTreeLogger->logExit("formal_parameter_section");
}

void Parser::fractional_part(){
    parseTreeLogger->logEntry("fractional_part");
    throw NotImplementedError("fractional_part");
    parseTreeLogger->logExit("fractional_part");
}

void Parser::function_block(){
    parseTreeLogger->logEntry("function_block");
    throw NotImplementedError("function_block");
    parseTreeLogger->logExit("function_block");
}

void Parser::function_declaration(){
    parseTreeLogger->logEntry("function_declaration");
    throw NotImplementedError("function_declaration");
    parseTreeLogger->logExit("function_declaration");
}

Type Parser::function_designator(){
    parseTreeLogger->logEntry("function_designator");
    throw NotImplementedError("function_designator");
    parseTreeLogger->logExit("function_designator");
}

void Parser::function_heading(){
    parseTreeLogger->logEntry("function_heading");
    throw NotImplementedError("function_heading");
    parseTreeLogger->logExit("function_heading");
}

void Parser::function_identification(){
    parseTreeLogger->logEntry("function_identification");
    throw NotImplementedError("function_identification");
    parseTreeLogger->logExit("function_identification");
}

void Parser::function_identifier(){
    parseTreeLogger->logEntry("function_identifier");
    throw NotImplementedError("function_identifier");
    parseTreeLogger->logExit("function_identifier");
}

void Parser::functional_parameter_specification(){
    parseTreeLogger->logEntry("functional_parameter_specification");
    throw NotImplementedError("functional_parameter_specification");
    parseTreeLogger->logExit("functional_parameter_specification");
}

void Parser::goto_statement(){
    parseTreeLogger->logEntry("goto_statement");
    match(TK_GOTO);
    if(curtoken.getTag() != TK_A_LABEL){
        throw "Syntax error discovered in goto_statement";
    }
    synthesizer->genOpCode(JUMP);
    size_t placeHolder = synthesizer->makePlaceHolderAddress();
    Token& tok = (*symboltable)[curtoken.getLexeme()];
    tok.addGoto(Goto(placeHolder));
    /*
    symboltable->erase(curtoken.getLexeme());
    symboltable->insert(
        make_pair<string, Token>(
            curtoken.getLexeme(),
            Token(curtoken)
        )
    );
    */
    match(TK_A_LABEL);
    parseTreeLogger->logExit("goto_statement");
}

void Parser::identified_variable(){
    parseTreeLogger->logEntry("identified_variable");
    throw NotImplementedError("identified_variable");
    parseTreeLogger->logExit("identified_variable");
}

string Parser::identifier(){
    parseTreeLogger->logEntry("identifier");
    string id = curtoken.getLexeme();
    match(ID);
    parseTreeLogger->logExit("identifier");
    return id;
}

vector<string> Parser::identifier_list(){
    parseTreeLogger->logEntry("identifier_list");
    vector<string> list;
    list.push_back(identifier());
    while(curtoken.getTag() == COMMA){
        match(COMMA);
        list.push_back(identifier());
    }
    parseTreeLogger->logExit("identifier_list");
    return list;
}

void Parser::if_statement(){
    parseTreeLogger->logEntry("if_statement");
    match(IF);
    // Should generate byte code for evaluating the condition
    // and placing the result on the stack.
    Boolean_expression();
    synthesizer->genOpCode(JUMP_FALSE);
    size_t placeHolder = synthesizer->makePlaceHolderAddress();
    match(THEN);
    statement();
    synthesizer->fillPlaceHolderAddress(placeHolder);
    match(SEMICOLON);
    if(curtoken.getTag() == ELSE){
        else_part();
    } else {
        lexer->addToStack(curtoken);
        curtoken = Token(SEMICOLON);
    }
    parseTreeLogger->logExit("if_statement");
}

Type Parser::index_expression(){
    parseTreeLogger->logEntry("index_expression");
    Type t = expression();
    parseTreeLogger->logExit("index_expression");
    return t;
}

Type Parser::index_type(){
    Type t;
    parseTreeLogger->logEntry("index_type");
    t = ordinal_type();
    parseTreeLogger->logExit("index_type");
    return t;
}

void Parser::index_type_specification(){
    parseTreeLogger->logEntry("index_type_specification");
    throw NotImplementedError("index_type_specification");
    parseTreeLogger->logExit("index_type_specification");
}

Type Parser::indexed_variable(){
    parseTreeLogger->logEntry("indexed_variable");
    Token& array_info = curtoken;
    match(TK_A_ARRAY);
    match(LBRACKET);
    Type index_t = index_expression();
    synthesizer->genOpCode(PUSH_ARRAY_ADDRESS);
    if(index_t.getKind() != array_info.getIndexKind()){
        throw "Type of index expression does not match array index type.";
    }
    synthesizer->writeKind(index_t.getKind());
    switch(array_info.getIndexKind()){
        case INTEGER_K:
            // Write lower bound as a size_t to instruction byte code.
            synthesizer->writeToInstructions((size_t)array_info.getIntLow());
            // Calculate offset from array address.
            synthesizer->writeToInstructions((size_t)sizeof(int));
            // Write address of array to instruction byte code.
            synthesizer->genAddress(array_info.getAddress());
            break;
        default:
            throw "indexed_variable not implemented for this index type.";
            break;
    }
    match(RBRACKET);
    parseTreeLogger->logExit("indexed_variable");
    return Type(array_info.getElemKind());
}

Type Parser::initial_value(){
    parseTreeLogger->logEntry("initial_value");
    Type t = expression();
    parseTreeLogger->logExit("initial_value");
    return t;
}

string Parser::label(){
    parseTreeLogger->logEntry("label");
    string id = curtoken.getLexeme();
    match(ID);
    parseTreeLogger->logExit("label");
    return id;
}

void Parser::label_declaration_part(){
    parseTreeLogger->logEntry("label_declaration_part");
    string prevLabel = "";
    if(curtoken.getTag() == LABEL){
        vector<string> labels;
        match(LABEL);
        labels.push_back(label());
        while(curtoken.getTag() == COMMA){
            match(COMMA);
            labels.push_back(label());
        }
        match(SEMICOLON);
        for(int i = 0; i < labels.size(); ++i){
            symboltable->erase(labels[i].c_str());
            symboltable->insert(
                make_pair<string, Token>(
                    labels[i].c_str(),
                    Token(
                        TK_A_LABEL,
                        labels[i].c_str(),
                        prevLabel.c_str()
                    )
                )
            );
            prevLabel = labels[i];
        }
    }
    headLabel = prevLabel;
    parseTreeLogger->logExit("label_declaration_part");
}

void Parser::letter(){
    parseTreeLogger->logEntry("letter");
    throw NotImplementedError("letter");
    parseTreeLogger->logExit("letter");
}

void Parser::member_designator(){
    parseTreeLogger->logEntry("member_designator");
    throw NotImplementedError("member_designator");
    parseTreeLogger->logExit("member_designator");
}

void Parser::multiplying_operator(){
    parseTreeLogger->logEntry("multiplying_operator");
    throw NotImplementedError("multiplying_operator");
    parseTreeLogger->logExit("multiplying_operator");
}

Type Parser::new_ordinal_type(){
    Type t;
    parseTreeLogger->logEntry("new_ordinal_type");
    switch(curtoken.getTag()){
        case LPAREN:
            enumerated_type();
            break;
        default:
            t = subrange_type();
            break;
    }
    parseTreeLogger->logExit("new_ordinal_type");
    return t;
}

void Parser::new_pointer_type(){
    parseTreeLogger->logEntry("new_pointer_type");
    throw NotImplementedError("new_pointer_type");
    parseTreeLogger->logExit("new_pointer_type");
}

Type Parser::new_structured_type(){
    parseTreeLogger->logEntry("new_structured_type");
    Type t;
    switch(curtoken.getTag()){
        case ARRAY:
            t = array_type();
            break;
        case RECORD:
            record_type();
            break;
        case SET:
            set_type();
            break;
        case PFILE:
            file_type();
            break;
        default:
            throw "Danger in new_structured_type Will Robinson!";
    }
    parseTreeLogger->logExit("new_structured_type");
    return t;
}

Type Parser::new_type(){
    parseTreeLogger->logEntry("new_type");
    Type t;
    switch(curtoken.getTag()){
        case EXP:
            new_pointer_type();
            break;
        case ARRAY:
        case RECORD:
        case SET:
        case PFILE:
            t = new_structured_type();
            break;
        default:
            new_ordinal_type();
            break;
    }
    parseTreeLogger->logExit("new_type");
    return t;
}

Type Parser::ordinal_type(){
    Type t;
    parseTreeLogger->logEntry("ordinal_type");
    switch(curtoken.getTag()){
        case ID:
            ordinal_type_identifier();
            break;
        default:
            t = new_ordinal_type();
            break;
    }
    parseTreeLogger->logExit("ordinal_type");
    return t;
}

void Parser::ordinal_type_identifier(){
    parseTreeLogger->logEntry("ordinal_type_identifier");
    throw NotImplementedError("ordinal_type_identifier");
    parseTreeLogger->logExit("ordinal_type_identifier");
}

void Parser::packed_conformant_array_schema(){
    parseTreeLogger->logEntry("packed_conformant_array_schema");
    throw NotImplementedError("packed_conformant_array_schema");
    parseTreeLogger->logExit("packed_conformant_array_schema");
}

void Parser::pointer_type(){
    parseTreeLogger->logEntry("pointer_type");
    throw NotImplementedError("pointer_type");
    parseTreeLogger->logExit("pointer_type");
}

void Parser::procedural_parameter_specification(){
    parseTreeLogger->logEntry("procedural_parameter_specification");
    throw NotImplementedError("procedural_parameter_specification");
    parseTreeLogger->logExit("procedural_parameter_specification");
}

void Parser::procedure_and_function_declaration_part(){
    parseTreeLogger->logEntry("procedure_and_function_declaration_part");
    switch(curtoken.getTag()){
        case PROCEDURE:
            procedure_declaration();
            match(SEMICOLON);
            break;
        case FUNCTION:
            function_declaration();
            match(SEMICOLON);
            break;
        default:
            break;
    }
    parseTreeLogger->logExit("procedure_and_function_declaration_part");
}

void Parser::procedure_block(){
    parseTreeLogger->logEntry("procedure_block");
    throw NotImplementedError("procedure_block");
    parseTreeLogger->logExit("procedure_block");
}

void Parser::procedure_declaration(){
    parseTreeLogger->logEntry("procedure_declaration");
    throw NotImplementedError("procedure_declaration");
    parseTreeLogger->logExit("procedure_declaration");
}

void Parser::procedure_heading(){
    parseTreeLogger->logEntry("procedure_heading");
    throw NotImplementedError("procedure_heading");
    parseTreeLogger->logExit("procedure_heading");
}

void Parser::procedure_identification(){
    parseTreeLogger->logEntry("procedure_identification");
    throw NotImplementedError("procedure_identification");
    parseTreeLogger->logExit("procedure_identification");
}

ProcedureToken Parser::procedure_identifier(){
    parseTreeLogger->logEntry("procedure_identifier");
    ProcedureToken result = ProcedureToken(curtoken.getLexeme());
    match(curtoken.getTag());
    parseTreeLogger->logExit("procedure_identifier");
    return result;
}

void Parser::procedure_statement(){
    parseTreeLogger->logEntry("procedure_statement");
    ProcedureToken proc = procedure_identifier();
    cout << "Returning from procedure_identifier()" << endl;
    cout << "proc.getTag(): " << proc.getTag() << " proc.getLexeme(): " << proc.getLexeme() << endl;
    if(proc.getLexeme() == "read"){
        read_parameter_list();
    } else if(proc.getLexeme() == "readln"){
        readln_parameter_list();
    } else if(proc.getLexeme() == "write"){
        write_parameter_list();
    } else if(proc.getLexeme() == "writeln"){
        writeln_parameter_list();
    } else if(curtoken.getTag() == LPAREN){
        actual_parameter_list();
    }
    parseTreeLogger->logExit("procedure_statement");
}

void Parser::program(){
    parseTreeLogger->logEntry("program");
    program_heading();
    match(SEMICOLON);
    program_block();
    match(DOT);
    parseTreeLogger->logExit("program");
}

void Parser::program_block(){
    parseTreeLogger->logEntry("program_block");
    block();
    parseTreeLogger->logExit("program_block");
}

void Parser::program_heading(){
    parseTreeLogger->logEntry("program_heading");
    match(PROGRAM);
    identifier();
    if(curtoken.getTag() == LPAREN){
        match(LPAREN);
        program_parameter_list();
        match(RPAREN);
    }
    parseTreeLogger->logExit("program_heading");
}

void Parser::program_parameter_list(){
    parseTreeLogger->logEntry("program_parameter_list");
    throw NotImplementedError("program_parameter_list");
    parseTreeLogger->logExit("program_parameter_list");
}

void Parser::read_parameter_list(){
    parseTreeLogger->logEntry("read_parameter_list");
    throw NotImplementedError("read_parameter_list");
    parseTreeLogger->logExit("read_parameter_list");
}

void Parser::readln_parameter_list(){
    parseTreeLogger->logEntry("readln_parameter_list");
    throw NotImplementedError("readln_parameter_list");
    parseTreeLogger->logExit("readln_parameter_list");
}

void Parser::real_type_identifier(){
    parseTreeLogger->logEntry("real_type_identifier");
    throw NotImplementedError("real_type_identifier");
    parseTreeLogger->logExit("real_type_identifier");
}

void Parser::record_section(){
    parseTreeLogger->logEntry("record_section");
    throw NotImplementedError("record_section");
    parseTreeLogger->logExit("record_section");
}

void Parser::record_type(){
    parseTreeLogger->logEntry("record_type");
    throw NotImplementedError("record_type");
    parseTreeLogger->logExit("record_type");
}

void Parser::record_variable(){
    parseTreeLogger->logEntry("record_variable");
    throw NotImplementedError("record_variable");
    parseTreeLogger->logExit("record_variable");
}

void Parser::record_variable_list(){
    parseTreeLogger->logEntry("record_variable_list");
    throw NotImplementedError("record_variable_list");
    parseTreeLogger->logExit("record_variable_list");
}

void Parser::relational_operator(){
    parseTreeLogger->logEntry("relational_operator");
    throw NotImplementedError("relational_operator");
    parseTreeLogger->logExit("relational_operator");
}

void Parser::repeat_statement(){
    parseTreeLogger->logEntry("repeat_statement");
    match(REPEAT);
    size_t condAddress = synthesizer->getInstructionAddress();
    statement_sequence();
    match(UNTIL);
    Boolean_expression();
    synthesizer->genOpCode(JUMP_FALSE);
    synthesizer->genAddress(condAddress);
    parseTreeLogger->logExit("repeat_statement");
}

void Parser::repetitive_statement(){
    parseTreeLogger->logEntry("repetitive_statement");
    switch(curtoken.getTag()){
        case REPEAT:
            repeat_statement();
            break;
        case WHILE:
            while_statement();
            break;
        case FOR:
            for_statement();
            break;
        default:
            throw "Syntax error discovered in repetitive_statement";
    }
    parseTreeLogger->logExit("repetitive_statement");
}

void Parser::result_type(){
    parseTreeLogger->logEntry("result_type");
    throw NotImplementedError("result_type");
    parseTreeLogger->logExit("result_type");
}

void Parser::scale_factor(){
    parseTreeLogger->logEntry("scale_factor");
    throw NotImplementedError("scale_factor");
    parseTreeLogger->logExit("scale_factor");
}

Type Parser::set_constructor(){
    parseTreeLogger->logEntry("set_constructor");
    throw NotImplementedError("set_constructor");
    parseTreeLogger->logExit("set_constructor");
}

void Parser::set_type(){
    parseTreeLogger->logEntry("set_type");
    throw NotImplementedError("set_type");
    parseTreeLogger->logExit("set_type");
}

void Parser::sign(){
    parseTreeLogger->logEntry("sign");
    throw NotImplementedError("sign");
    parseTreeLogger->logExit("sign");
}

void Parser::signed_integer(){
    parseTreeLogger->logEntry("signed_integer");
    throw NotImplementedError("signed_integer");
    parseTreeLogger->logExit("signed_integer");
}

void Parser::signed_number(){
    parseTreeLogger->logEntry("signed_number");
    throw NotImplementedError("signed_number");
    parseTreeLogger->logExit("signed_number");
}

void Parser::signed_real(){
    parseTreeLogger->logEntry("signed_real");
    throw NotImplementedError("signed_real");
    parseTreeLogger->logExit("signed_real");
}

Type Parser::simple_expression(){
    parseTreeLogger->logEntry("simple_expression");
    if(curtoken.getTag() == PLUS || curtoken.getTag() == MINUS) sign();
    Type t1 = term(), t2;
    switch(curtoken.getTag()){
        case PLUS:
            match(PLUS);
            t2 = simple_expression();
            if(t1.getKind() == t2.getKind()){
                t1 = synthesizer->genAdditionCode(t1, t2);
            } else if(t1.getKind() == INTEGER_K && t2.getKind() == REAL_K){
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(REAL_ADDITION);
                t1 = Type(REAL_K);
            } else if(t1.getKind() == REAL_K && t2.getKind() == INTEGER_K){
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(REAL_ADDITION);
            } else {
                throw "syntax error addition is defined only on integers and reals.";
            }
            break;
        case MINUS:
            match(MINUS);
            t2 = simple_expression();
            if(t1.getKind() == t2.getKind()){
                t1 = synthesizer->genSubtractionCode(t1, t2);
            } else if(t1.getKind() == INTEGER_K && t2.getKind() == REAL_K){
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(REAL_SUBTRACTION);
                t1 = Type(REAL_K);
            } else if(t1.getKind() == REAL_K && t2.getKind() == INTEGER_K){
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(REAL_SUBTRACTION);
            } else {
                throw "syntax error subtraction is defined only on integers and reals.";
            }
            break;
        case OR:
            throw NotImplementedError("OR addition operator in simple_expression.");
    }
    parseTreeLogger->logExit("simple_expression");
    return t1;
}

void Parser::simple_statement(){
    parseTreeLogger->logEntry("simple_statement");
    switch(curtoken.getTag()){
        case TK_A_PROC:
            procedure_statement();
            break;
        case TK_GOTO:
            goto_statement();
            break;
        case TK_A_FUNC:
        case TK_A_ARRAY:
        case TK_A_RECORD:
        case TK_A_PTR:
        case TK_A_FILE:
        case TK_A_VAR:
            assignment_statement();
            break;
        default:
            empty_statement();
            break;
    }
    parseTreeLogger->logExit("simple_statement");
}

void Parser::simple_type(){
    parseTreeLogger->logEntry("simple_type");
    throw NotImplementedError("simple_type");
    parseTreeLogger->logExit("simple_type");
}

void Parser::simple_type_identifier(){
    parseTreeLogger->logEntry("simple_type_identifier");
    throw NotImplementedError("simple_type_identifier");
    parseTreeLogger->logExit("simple_type_identifier");
}

void Parser::special_symbol(){
    parseTreeLogger->logEntry("special_symbol");
    throw NotImplementedError("special_symbol");
    parseTreeLogger->logExit("special_symbol");
}

void Parser::statement(){
    parseTreeLogger->logEntry("statement");
    if(curtoken.getTag() == TK_A_LABEL){
        if(curtoken.getSeen()){
            throw "Syntax error discovered in statement";
        }
        Token& tok = (*symboltable)[curtoken.getLexeme()];
        tok.setSeen(true);
        tok.setAddress(synthesizer->getInstructionAddress());
        match(TK_A_LABEL);
        match(COLON);
    }
    switch(curtoken.getTag()){
        case BEGIN:
        case IF:
        case CASE:
        case REPEAT:
        case WHILE:
        case FOR:
        case WITH:
            structured_statement();
            break;
        default:
            simple_statement();
    }
    parseTreeLogger->logExit("statement");
}

void Parser::statement_part(){
    parseTreeLogger->logEntry("statement_part");
    compound_statement();
    parseTreeLogger->logExit("statement_part");
}

void Parser::statement_sequence(){
    parseTreeLogger->logEntry("statement_sequence");
    statement();
    while(curtoken.getTag() == SEMICOLON){
        match(SEMICOLON);
        statement();
    }
    parseTreeLogger->logExit("statement_sequence");
}

void Parser::string_character(){
    parseTreeLogger->logEntry("string_character");
    throw NotImplementedError("string_character");
    parseTreeLogger->logExit("string_character");
}

void Parser::string_element(){
    parseTreeLogger->logEntry("string_element");
    throw NotImplementedError("string_element");
    parseTreeLogger->logExit("string_element");
}

void Parser::structured_statement(){
    parseTreeLogger->logEntry("structured_statement");
    switch(curtoken.getTag()){
        case BEGIN:
            compound_statement();
            break;
        case IF:
        case CASE:
            conditional_statement();
            break;
        case REPEAT:
        case WHILE:
        case FOR:
            repetitive_statement();
            break;
        case WITH:
            with_statement();
            break;
        default:
            throw "syntax error discovered in structured_statement";
    }
    parseTreeLogger->logExit("structured_statement");
}

void Parser::structured_type(){
    parseTreeLogger->logEntry("structured_type");
    throw NotImplementedError("structured_type");
    parseTreeLogger->logExit("structured_type");
}

void Parser::structured_type_identifier(){
    parseTreeLogger->logEntry("structured_type_identifier");
    throw NotImplementedError("structured_type_identifier");
    parseTreeLogger->logExit("structured_type_identifier");
}

Type Parser::subrange_type(){
    Type t, s;
    parseTreeLogger->logEntry("subrange_type");
    if(curtoken.getTag() != BOOLEAN &&
       curtoken.getTag() != INT){
        throw "Subrange type must be of ordinal type.";
    }
    Token low = curtoken;
    match(curtoken.getTag());
    match(RANGE);
    Token high = curtoken;
    if(low.getTag() != high.getTag()){
        throw "Subrange low and high values must be of same type.";
    }
    switch(curtoken.getTag()){
        case INT:
            t = Type(INTEGER_K);
            s = Type(SUBRANGE_K, INTEGER_K, low.getValue(), high.getValue());
            break;
        default:
            throw "Invalid subrange type!";
    }
    match(curtoken.getTag());
    parseTreeLogger->logExit("subrange_type");
    return s;
}

void Parser::tag_field(){
    parseTreeLogger->logEntry("tag_field");
    throw NotImplementedError("tag_field");
    parseTreeLogger->logExit("tag_field");
}

void Parser::tag_type(){
    parseTreeLogger->logEntry("tag_type");
    throw NotImplementedError("tag_type");
    parseTreeLogger->logExit("tag_type");
}

Type Parser::term(){
    parseTreeLogger->logEntry("term");
    Type t1 = factor(), t2;
    switch(curtoken.getTag()){
        case STAR:
            match(STAR);
            t2 = factor();
            if(t1.getKind() == t2.getKind()){
                t1 = synthesizer->genMultiplicationCode(t1, t2);
            } else if(t1.getKind() == INTEGER_K && t2.getKind() == REAL_K){
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(REAL_MULTIPLICATION);
                t1 = Type(REAL_K);
            } else if(t1.getKind() == REAL_K && t2.getKind() == INTEGER_K){
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(REAL_MULTIPLICATION);
            } else {
                throw "syntax error, multiplication is only defined on the integers and reals";
            }
            break;
        case FSLASH:
            match(FSLASH);
            t2 = factor();
            if(t1.getKind() == REAL_K && t2.getKind() == REAL_K){
                synthesizer->genOpCode(REAL_DIVISION);
            } else if(t1.getKind() == INTEGER_K && t2.getKind() == INTEGER_K){
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(REAL_DIVISION);
                t1 = Type(REAL_K);
            } else if(t1.getKind() == REAL_K && t2.getKind() == INTEGER_K){
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(REAL_DIVISION);
            } else if(t1.getKind() == INTEGER_K && t2.getKind() == REAL_K){
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(CONVERT_INTEGER_TO_REAL);
                synthesizer->genOpCode(SWAP);
                synthesizer->genOpCode(REAL_DIVISION);
                t1 = Type(REAL_K);
            } else {
                throw "syntax error: division is only defined on the integers and reals";
            }
            break;
        case DIV:
            match(DIV);
            t2 = factor();
            if(t1.getKind() != INTEGER_K || t2.getKind() != INTEGER_K){
                throw "Both operands must be of type Integer in integer division.";
            }
            synthesizer->genOpCode(INTEGER_DIVISION);
            break;
        case MOD:
            match(MOD);
            t2 = factor();
            if(t1.getKind() != INTEGER_K || t2.getKind() != INTEGER_K){
                throw "Modular division is only defined on integers";
            }
            synthesizer->genOpCode(INTEGER_MOD_DIVISION);
            break;
        case AND:
            match(curtoken.getTag());
            factor();
            break;
    }
    parseTreeLogger->logExit("term");
    return t1;
}

void Parser::type_definition(){
    parseTreeLogger->logEntry("type_definition");
    throw NotImplementedError("type_definition");
    parseTreeLogger->logExit("type_definition");
}

void Parser::type_definition_part(){
    parseTreeLogger->logEntry("type_definition_part");
    if(curtoken.getTag() == TYP){
        match(TYP);
        while(curtoken.getTag() == ID){
            type_definition();
            match(SEMICOLON);
        }
    }
    parseTreeLogger->logExit("type_definition_part");
}

Type Parser::type_denoter(){
    Type t;
    parseTreeLogger->logEntry("type_denoter");
    if(curtoken.getTag() == ID){
        t = Type(type_identifier());
    } else {
        t = new_type();
    }
    parseTreeLogger->logExit("type_denoter");
    return t;
}

string Parser::type_identifier(){
    parseTreeLogger->logEntry("type_identifier");
    parseTreeLogger->logExit("type_identifier");
    return identifier();
}

void Parser::unpacked_conformant_array_schema(){
    parseTreeLogger->logEntry("unpacked_conformant_array_schema");
    throw NotImplementedError("unpacked_conformant_array_schema");
    parseTreeLogger->logExit("unpacked_conformant_array_schema");
}

void Parser::unpacked_structured_type(){
    parseTreeLogger->logEntry("unpacked_structured_type");
    throw NotImplementedError("unpacked_structured_type");
    parseTreeLogger->logExit("unpacked_structured_type");
}

Type Parser::unsigned_constant(){
    parseTreeLogger->logEntry("unsigned_constant");
    Type t;
    switch(curtoken.getTag()){
        case INT:
        case REAL:
            t = unsigned_number();
            break;
        case STRING:
            t = character_string();
            break;
        case BOOLEAN:
            t = Type(BOOLEAN_K);
            synthesizer->genOpCode(PUSH_BOOLEAN);
            synthesizer->genBoolean((bool)curtoken.getValue());
            match(BOOLEAN);
            break;
        case TK_A_CONST:
            t = constant_identifier();
            break;
        case NIL:
            t = Type(NIL_K);
            break;
        default:
            throw 1;
            break;
    }
    parseTreeLogger->logExit("unsigned_constant");
    return t;
}

Type Parser::unsigned_integer(){
    parseTreeLogger->logEntry("unsigned_integer");
    size_t addr = synthesizer->writeUnsignedIntegerLiteralToHeader(curtoken);
    synthesizer->genOpCode(PUSH_INT);
    synthesizer->genAddress(addr);
    match(INT);
    parseTreeLogger->logExit("unsigned_integer");
    return Type(INTEGER_K);
}

Type Parser::unsigned_number(){
    parseTreeLogger->logEntry("unsigned_number");
    Type t;
    if(curtoken.getTag() == INT){
        t = unsigned_integer();
    } else if(curtoken.getTag() == REAL){
        t = unsigned_real();
    } else {
        throw "Malformed unsigned_number. Expected INT or REAL.";
    }
    parseTreeLogger->logExit("unsigned_number");
    return t;
}

Type Parser::unsigned_real(){
    parseTreeLogger->logEntry("unsigned_real");
    size_t addr = synthesizer->writeUnsignedRealLiteralToHeader(curtoken);
    synthesizer->genOpCode(PUSH_REAL);
    synthesizer->genAddress(addr);
    match(REAL);
    parseTreeLogger->logExit("unsigned_real");
    return Type(REAL_K);
}

void Parser::value_conformant_array_specification(){
    parseTreeLogger->logEntry("value_conformant_array_specification");
    throw NotImplementedError("value_conformant_array_specification");
    parseTreeLogger->logExit("value_conformant_array_specification");
}

void Parser::value_parameter_specification(){
    parseTreeLogger->logEntry("value_parameter_specification");
    throw NotImplementedError("value_parameter_specification");
    parseTreeLogger->logExit("value_parameter_specification");
}

Type Parser::variable_access(){
    parseTreeLogger->logEntry("variable_access");
    Type t;
    switch(curtoken.getTag()){
        case TK_A_VAR:
            t = entire_variable();
            break;
        case TK_A_ARRAY:
            t = component_variable();
            break;
        default:
            throw NotImplementedError("variable_access on non TK_A_VAR variable");
    }
    parseTreeLogger->logExit("variable_access");
    return t;
}

void Parser::variable_conformant_array_specification(){
    parseTreeLogger->logEntry("variable_conformant_array_specification");
    throw NotImplementedError("variable_conformant_array_specification");
    parseTreeLogger->logExit("variable_conformant_array_specification");
}

void Parser::variable_declaration(){
    parseTreeLogger->logEntry("variable_declaration");
    vector<string> list = identifier_list();
    match(COLON);
    Type t = type_denoter();
    cout << "switching on type_denoter in variable_declaration" << endl;
    switch(t.getKind()){
        case STRING_K:
            cout << "In STRING_K" << endl;
            for(int i = 0; i < list.size(); ++i){
                cout << "Checking lis[" << i << "]" << endl;
                cout << "list[i]: " << list[i] << endl;
                symboltable->erase(list[i].c_str());
                symboltable->insert(
                    make_pair<string, Token>(
                        list[i].c_str(),
                        Token(
                            TK_A_VAR,
                            list[i].c_str(),
                            STRING_K,
                            synthesizer->allocateStringVariableInHeader()
                        )
                    )
                );
                cout << "list[i]: " << list[i] << endl;
            }
            break;
        case INTEGER_K:
            for(int i = 0; i < list.size(); ++i){
                symboltable->erase(list[i].c_str());
                symboltable->insert(
                    make_pair<string, Token>(
                        list[i].c_str(),
                        Token(
                            TK_A_VAR,
                            list[i].c_str(),
                            INTEGER_K,
                            synthesizer->allocatIntegerVariableInHeader()
                        )
                    )
                );
            }
            break;
        case REAL_K:
            for(int i = 0; i < list.size(); ++i){
                symboltable->erase(list[i].c_str());
                symboltable->insert(
                    make_pair<string, Token>(
                        list[i].c_str(),
                        Token(
                            TK_A_VAR,
                            list[i].c_str(),
                            REAL_K,
                            synthesizer->allocateRealVariableInHeader()
                        )
                    )
                );
            }
            break;
        case BOOLEAN_K:
            for(int i = 0; i < list.size(); ++i){
                symboltable->erase(list[i].c_str());
                symboltable->insert(
                    make_pair<string, Token>(
                        list[i].c_str(),
                        Token(
                            TK_A_VAR,
                            list[i].c_str(),
                            BOOLEAN_K,
                            synthesizer->allocateBooleanVariableInHeader()
                        )
                    )
                );
            }
            break;
        case ARRAY_K:
            for(int i = 0; i < list.size(); ++i){
                symboltable->erase(list[i].c_str());
                symboltable->insert(
                    make_pair<string, Token>(
                        list[i].c_str(),
                        Token(
                            TK_A_ARRAY,
                            list[i].c_str(),
                            t.getElemKind(),
                            t.getIndexKind(),
                            t.getIntLow(),
                            t.getIntHigh(),
                            synthesizer->allocateArrayVariableInHeader(t)
                        )
                    )
                );
            }
            break;
        default:
            cout << "We should not be here..." << endl;
            throw "Variable declarations for this type is not implemented.";
            break;
    }
    parseTreeLogger->logExit("variable_declaration");
}

void Parser::variable_declaration_part(){
    parseTreeLogger->logEntry("variable_declaration_part");
    if(curtoken.getTag() == VAR){
        match(VAR);
        while(curtoken.getTag() == ID){
            variable_declaration();
            cout << "back in variable_declaration" << endl;
            match(SEMICOLON);
        }
    }
    parseTreeLogger->logExit("variable_declaration_part");
}

Type Parser::variable_identifier(){
    parseTreeLogger->logEntry("variable_identifier");
    Type t;
    switch(curtoken.getKind()){
        case STRING_K:
            t = Type(STRING_K);
            synthesizer->genAddress(curtoken.getAddress());
            match(TK_A_VAR);
            break;
        case INTEGER_K:
            t = Type(INTEGER_K);
            synthesizer->genAddress(curtoken.getAddress());
            match(TK_A_VAR);
            break;
        case REAL_K:
            t = Type(REAL_K);
            synthesizer->genAddress(curtoken.getAddress());
            match(TK_A_VAR);
            break;
        case BOOLEAN_K:
            t = Type(BOOLEAN_K);
            synthesizer->genAddress(curtoken.getAddress());
            match(TK_A_VAR);
            break;
        default:
            throw NotImplementedError("variable_identifier Kind not implemented");
    }
    parseTreeLogger->logExit("variable_identifier");
    return t;
}

void Parser::variable_parameter_specification(){
    parseTreeLogger->logEntry("variable_parameter_specification");
    throw NotImplementedError("variable_parameter_specification");
    parseTreeLogger->logExit("variable_parameter_specification");
}

void Parser::variant(){
    parseTreeLogger->logEntry("variant");
    throw NotImplementedError("variant");
    parseTreeLogger->logExit("variant");
}

void Parser::variant_part(){
    parseTreeLogger->logEntry("variant_part");
    throw NotImplementedError("variant_part");
    parseTreeLogger->logExit("variant_part");
}

void Parser::variant_selector(){
    parseTreeLogger->logEntry("variant_selector");
    throw NotImplementedError("variant_selector");
    parseTreeLogger->logExit("variant_selector");
}

void Parser::while_statement(){
    parseTreeLogger->logEntry("while_statement");
    match(WHILE);
    size_t condAddress = synthesizer->getInstructionAddress();
    Boolean_expression();
    synthesizer->genOpCode(JUMP_FALSE);
    size_t placeHolder = synthesizer->makePlaceHolderAddress();
    match(DO);
    statement();
    synthesizer->genOpCode(JUMP);
    synthesizer->genAddress(condAddress);
    synthesizer->fillPlaceHolderAddress(placeHolder);
    parseTreeLogger->logExit("while_statement");
}

void Parser::with_statement(){
    parseTreeLogger->logEntry("with_statement");
    throw NotImplementedError("with_statement");
    parseTreeLogger->logExit("with_statement");
}

void Parser::word_symbol(){
    parseTreeLogger->logEntry("word_symbol");
    throw NotImplementedError("word_symbol");
    parseTreeLogger->logExit("word_symbol");
}

void Parser::write_parameter(){
    parseTreeLogger->logEntry("write_parameter");
    Type t = expression();
    synthesizer->genPrintCode(t);
    if(curtoken.getTag() == COLON){
        t = expression();
        //synthesizer->genPrintCode(t);
    }
    if(curtoken.getTag() == COLON){
        t = expression();
        //synthesizer->genPrintCode(t);
    }
    parseTreeLogger->logExit("write_parameter");
}

void Parser::write_parameter_list(){
    parseTreeLogger->logEntry("write_parameter_list");
    match(LPAREN);
    if(curtoken.getTag() == TK_A_FILE){
        file_variable();
    } else {
        write_parameter();
    }
    while(curtoken.getTag() == COMMA){
        match(COMMA);
        write_parameter();
    }
    match(RPAREN);
    parseTreeLogger->logExit("write_parameter_list");
}

void Parser::writeln_parameter_list(){
    parseTreeLogger->logEntry("writeln_parameter_list");
    if(curtoken.getTag() == LPAREN){
        match(LPAREN);
        if(curtoken.getTag() == TK_A_FILE){
            file_variable();
        } else {
            write_parameter();
        }
        while(curtoken.getTag() == COMMA){
            match(COMMA);
            write_parameter();
        }
        synthesizer->genPrintLn();
        match(RPAREN);
    }
    parseTreeLogger->logExit("writeln_parameter_list");
}

#endif
