#ifndef PARSER_IMPL
#define PARSER_IMPL

#include<iostream>
using std::cout;
using std::endl;
#include "parser.h"
#include "../lexer/lexer.h"
#include "../notimplementederror/notimplementederror.h"

Parser::Parser(const char* sourceFile, Synthesizer *synthesizer) : parseTreeLogger(sourceFile){
    lexer = Lexer(sourceFile, &symboltable);
    this->synthesizer = synthesizer;
    curtoken = lexer.getToken();
}

bool Parser::parse(){
    parseTreeLogger.logEntry("parse");
    try{
        program();
        match(END_OF_FILE);
    } catch (...){
        cout << "caught exception." << endl;
        parseTreeLogger.logExit("parse");
        return false;
    }
    return true;
}

void Parser::match(Tag t){
    cout << "Entering Parser::match" << endl;
    cout << "Tag t: " << t << endl;
    cout << "curtoken.getTag(): " << curtoken.getTag() << endl;
    if(curtoken.getTag() == t){
        curtoken = lexer.getToken();
    } else {
        throw 1;
    }
}

void Parser::actual_parameter(){
    parseTreeLogger.logEntry("actual_parameter");
    throw NotImplementedError("actual_parameter");
    parseTreeLogger.logExit("actual_parameter");
}

void Parser::actual_parameter_list(){
    parseTreeLogger.logEntry("actual_parameter_list");
    throw NotImplementedError("actual_parameter_list");
    parseTreeLogger.logExit("actual_parameter_list");
}

void Parser::adding_operator(){
    parseTreeLogger.logEntry("adding_operator");
    throw NotImplementedError("adding_operator");
    parseTreeLogger.logExit("adding_operator");
}

void Parser::apostrophe_image(){
    parseTreeLogger.logEntry("apostrophe_image");
    throw NotImplementedError("apostrophe_image");
    parseTreeLogger.logExit("apostrophe_image");
}

void Parser::array_type(){
    parseTreeLogger.logEntry("array_type");
    throw NotImplementedError("array_type");
    parseTreeLogger.logExit("array_type");
}

void Parser::array_variable(){
    parseTreeLogger.logEntry("array_variable");
    throw NotImplementedError("array_variable");
    parseTreeLogger.logExit("array_variable");
}

void Parser::assignment_statement(){
    parseTreeLogger.logEntry("assignment_statement");
    throw NotImplementedError("assignment_statement");
    parseTreeLogger.logExit("assignment_statement");
}

void Parser::base_type(){
    parseTreeLogger.logEntry("base_type");
    throw NotImplementedError("base_type");
    parseTreeLogger.logExit("base_type");
}

void Parser::block(){
    parseTreeLogger.logEntry("block");
    label_declaration_part();
    constant_definition_part();
    type_definition_part();
    variable_declaration_part();
    procedure_and_function_declaration_part();
    statement_part();
    parseTreeLogger.logExit("block");
}

void Parser::Boolean_expression(){
    parseTreeLogger.logEntry("Boolean_expression");
    throw NotImplementedError("Boolean_expression");
    parseTreeLogger.logExit("Boolean_expression");
}

void Parser::bound_identifier(){
    parseTreeLogger.logEntry("bound_identifier");
    throw NotImplementedError("bound_identifier");
    parseTreeLogger.logExit("bound_identifier");
}

void Parser::buffer_variable(){
    parseTreeLogger.logEntry("buffer_variable");
    throw NotImplementedError("buffer_variable");
    parseTreeLogger.logExit("buffer_variable");
}

void Parser::case_constant(){
    parseTreeLogger.logEntry("case_constant");
    throw NotImplementedError("case_constant");
    parseTreeLogger.logExit("case_constant");
}

void Parser::case_constant_list(){
    parseTreeLogger.logEntry("case_constant_list");
    throw NotImplementedError("case_constant_list");
    parseTreeLogger.logExit("case_constant_list");
}

void Parser::case_index(){
    parseTreeLogger.logEntry("case_index");
    throw NotImplementedError("case_index");
    parseTreeLogger.logExit("case_index");
}

void Parser::case_list_element(){
    parseTreeLogger.logEntry("case_list_element");
    throw NotImplementedError("case_list_element");
    parseTreeLogger.logExit("case_list_element");
}

void Parser::case_statement(){
    parseTreeLogger.logEntry("case_statement");
    throw NotImplementedError("case_statement");
    parseTreeLogger.logExit("case_statement");
}

Type Parser::character_string(){
    parseTreeLogger.logEntry("character_string");
    StringToken strtok(curtoken.getLexeme());
    size_t addr = synthesizer->writeStringLiteralToHeader(strtok);
    synthesizer->genOpCode(PUSH_STRING);
    synthesizer->genAddress(addr);
    match(STRING);
    parseTreeLogger.logExit("character_string");
    return Type(STRING_K);
}

void Parser::component_type(){
    parseTreeLogger.logEntry("component_type");
    throw NotImplementedError("component_type");
    parseTreeLogger.logExit("component_type");
}

void Parser::component_variable(){
    parseTreeLogger.logEntry("component_variable");
    throw NotImplementedError("component_variable");
    parseTreeLogger.logExit("component_variable");
}

void Parser::compound_statement(){
    parseTreeLogger.logEntry("compound_statement");
    match(BEGIN);
    statement_sequence();
    match(END);
    parseTreeLogger.logExit("compound_statement");
}

void Parser::conditional_statement(){
    parseTreeLogger.logEntry("conditional_statement");
    throw NotImplementedError("conditional_statement");
    parseTreeLogger.logExit("conditional_statement");
}

void Parser::conformant_array_parameter_specification(){
    parseTreeLogger.logEntry("conformant_array_parameter_specification");
    throw NotImplementedError("conformant_array_parameter_specification");
    parseTreeLogger.logExit("conformant_array_parameter_specification");
}

void Parser::conformant_array_schema(){
    parseTreeLogger.logEntry("conformant_array_schema");
    throw NotImplementedError("conformant_array_schema");
    parseTreeLogger.logExit("conformant_array_schema");
}

void Parser::constant(){
    parseTreeLogger.logEntry("constant");
    throw NotImplementedError("constant");
    parseTreeLogger.logExit("constant");
}

void Parser::constant_definition(){
    parseTreeLogger.logEntry("constant_definition");
    throw NotImplementedError("constant_definition");
    parseTreeLogger.logExit("constant_definition");
}

void Parser::constant_definition_part(){
    parseTreeLogger.logEntry("constant_definition_part");
    if(curtoken.getTag() == CONST){
        match(CONST);
        while(curtoken.getTag() == ID){
            constant_definition();
            match(SEMICOLON);
        }
    }
    parseTreeLogger.logExit("constant_definition_part");
}

Type Parser::constant_identifier(){
    parseTreeLogger.logEntry("constant_identifier");
    throw NotImplementedError("constant_identifier");
    parseTreeLogger.logExit("constant_identifier");
}

void Parser::control_variable(){
    parseTreeLogger.logEntry("control_variable");
    throw NotImplementedError("control_variable");
    parseTreeLogger.logExit("control_variable");
}

void Parser::digit(){
    parseTreeLogger.logEntry("digit");
    throw NotImplementedError("digit");
    parseTreeLogger.logExit("digit");
}

void Parser::digit_sequence(){
    parseTreeLogger.logEntry("digit_sequence");
    throw NotImplementedError("digit_sequence");
    parseTreeLogger.logExit("digit_sequence");
}

void Parser::directive(){
    parseTreeLogger.logEntry("directive");
    throw NotImplementedError("directive");
    parseTreeLogger.logExit("directive");
}

void Parser::domain_type(){
    parseTreeLogger.logEntry("domain_type");
    throw NotImplementedError("domain_type");
    parseTreeLogger.logExit("domain_type");
}

void Parser::else_part(){
    parseTreeLogger.logEntry("else_part");
    throw NotImplementedError("else_part");
    parseTreeLogger.logExit("else_part");
}

void Parser::empty_statement(){
    parseTreeLogger.logEntry("empty_statement");
    parseTreeLogger.logExit("empty_statement");
}

void Parser::entire_variable(){
    parseTreeLogger.logEntry("entire_variable");
    throw NotImplementedError("entire_variable");
    parseTreeLogger.logExit("entire_variable");
}

void Parser::enumerated_type(){
    parseTreeLogger.logEntry("enumerated_type");
    throw NotImplementedError("enumerated_type");
    parseTreeLogger.logExit("enumerated_type");
}

Type Parser::expression(){
    parseTreeLogger.logEntry("expression");
    Type t = simple_expression();
    switch(curtoken.getTag()){
        case EQ:
        case NEQ:
        case LT:
        case GT:
        case LEQ:
        case GEQ:
        case IN:
            match(curtoken.getTag());
            simple_expression();
            break;
        default:
            break;
    }
    parseTreeLogger.logExit("expression");
    return t;
}

Type Parser::factor(){
    parseTreeLogger.logEntry("factor");
    Type t;
    switch(curtoken.getTag()){
        case INT:
        case REAL:
        case STRING:
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
        default:
            t = variable_access();
            break;
    }
    parseTreeLogger.logExit("factor");
    return t;
}

void Parser::field_designator(){
    parseTreeLogger.logEntry("field_designator");
    throw NotImplementedError("field_designator");
    parseTreeLogger.logExit("field_designator");
}

void Parser::field_designator_identifier(){
    parseTreeLogger.logEntry("field_designator_identifier");
    throw NotImplementedError("field_designator_identifier");
    parseTreeLogger.logExit("field_designator_identifier");
}

void Parser::field_identifier(){
    parseTreeLogger.logEntry("field_identifier");
    throw NotImplementedError("field_identifier");
    parseTreeLogger.logExit("field_identifier");
}

void Parser::field_list(){
    parseTreeLogger.logEntry("field_list");
    throw NotImplementedError("field_list");
    parseTreeLogger.logExit("field_list");
}

void Parser::field_specififer(){
    parseTreeLogger.logEntry("field_specififer");
    throw NotImplementedError("field_specififer");
    parseTreeLogger.logExit("field_specififer");
}

void Parser::file_type(){
    parseTreeLogger.logEntry("file_type");
    throw NotImplementedError("file_type");
    parseTreeLogger.logExit("file_type");
}

void Parser::file_variable(){
    parseTreeLogger.logEntry("file_variable");
    throw NotImplementedError("file_variable");
    parseTreeLogger.logExit("file_variable");
}

void Parser::final_value(){
    parseTreeLogger.logEntry("final_value");
    throw NotImplementedError("final_value");
    parseTreeLogger.logExit("final_value");
}

void Parser::fixed_part(){
    parseTreeLogger.logEntry("fixed_part");
    throw NotImplementedError("fixed_part");
    parseTreeLogger.logExit("fixed_part");
}

void Parser::for_statement(){
    parseTreeLogger.logEntry("for_statement");
    throw NotImplementedError("for_statement");
    parseTreeLogger.logExit("for_statement");
}

void Parser::formal_parameter_list(){
    parseTreeLogger.logEntry("formal_parameter_list");
    throw NotImplementedError("formal_parameter_list");
    parseTreeLogger.logExit("formal_parameter_list");
}

void Parser::formal_parameter_section(){
    parseTreeLogger.logEntry("formal_parameter_section");
    throw NotImplementedError("formal_parameter_section");
    parseTreeLogger.logExit("formal_parameter_section");
}

void Parser::fractional_part(){
    parseTreeLogger.logEntry("fractional_part");
    throw NotImplementedError("fractional_part");
    parseTreeLogger.logExit("fractional_part");
}

void Parser::function_block(){
    parseTreeLogger.logEntry("function_block");
    throw NotImplementedError("function_block");
    parseTreeLogger.logExit("function_block");
}

void Parser::function_declaration(){
    parseTreeLogger.logEntry("function_declaration");
    throw NotImplementedError("function_declaration");
    parseTreeLogger.logExit("function_declaration");
}

Type Parser::function_designator(){
    parseTreeLogger.logEntry("function_designator");
    throw NotImplementedError("function_designator");
    parseTreeLogger.logExit("function_designator");
}

void Parser::function_heading(){
    parseTreeLogger.logEntry("function_heading");
    throw NotImplementedError("function_heading");
    parseTreeLogger.logExit("function_heading");
}

void Parser::function_identification(){
    parseTreeLogger.logEntry("function_identification");
    throw NotImplementedError("function_identification");
    parseTreeLogger.logExit("function_identification");
}

void Parser::function_identifier(){
    parseTreeLogger.logEntry("function_identifier");
    throw NotImplementedError("function_identifier");
    parseTreeLogger.logExit("function_identifier");
}

void Parser::functional_parameter_specification(){
    parseTreeLogger.logEntry("functional_parameter_specification");
    throw NotImplementedError("functional_parameter_specification");
    parseTreeLogger.logExit("functional_parameter_specification");
}

void Parser::goto_statement(){
    parseTreeLogger.logEntry("goto_statement");
    throw NotImplementedError("goto_statement");
    parseTreeLogger.logExit("goto_statement");
}

void Parser::identified_variable(){
    parseTreeLogger.logEntry("identified_variable");
    throw NotImplementedError("identified_variable");
    parseTreeLogger.logExit("identified_variable");
}

void Parser::identifier(){
    parseTreeLogger.logEntry("identifier");
    match(ID);
    parseTreeLogger.logExit("identifier");
}

void Parser::identifier_list(){
    parseTreeLogger.logEntry("identifier_list");
    throw NotImplementedError("identifier_list");
    parseTreeLogger.logExit("identifier_list");
}

void Parser::if_statement(){
    parseTreeLogger.logEntry("if_statement");
    throw NotImplementedError("if_statement");
    parseTreeLogger.logExit("if_statement");
}

void Parser::index_expression(){
    parseTreeLogger.logEntry("index_expression");
    throw NotImplementedError("index_expression");
    parseTreeLogger.logExit("index_expression");
}

void Parser::index_type(){
    parseTreeLogger.logEntry("index_type");
    throw NotImplementedError("index_type");
    parseTreeLogger.logExit("index_type");
}

void Parser::index_type_specification(){
    parseTreeLogger.logEntry("index_type_specification");
    throw NotImplementedError("index_type_specification");
    parseTreeLogger.logExit("index_type_specification");
}

void Parser::indexed_variable(){
    parseTreeLogger.logEntry("indexed_variable");
    throw NotImplementedError("indexed_variable");
    parseTreeLogger.logExit("indexed_variable");
}

void Parser::initial_value(){
    parseTreeLogger.logEntry("initial_value");
    throw NotImplementedError("initial_value");
    parseTreeLogger.logExit("initial_value");
}

void Parser::label(){
    parseTreeLogger.logEntry("label");
    throw NotImplementedError("label");
    parseTreeLogger.logExit("label");
}

void Parser::label_declaration_part(){
    parseTreeLogger.logEntry("label_declaration_part");
    if(curtoken.getTag() == LABEL){
        match(LABEL);
        label();
        while(curtoken.getTag() == COMMA){
            match(COMMA);
            label();
        }
        match(SEMICOLON);
    }
    parseTreeLogger.logExit("label_declaration_part");
}

void Parser::letter(){
    parseTreeLogger.logEntry("letter");
    throw NotImplementedError("letter");
    parseTreeLogger.logExit("letter");
}

void Parser::member_designator(){
    parseTreeLogger.logEntry("member_designator");
    throw NotImplementedError("member_designator");
    parseTreeLogger.logExit("member_designator");
}

void Parser::multiplying_operator(){
    parseTreeLogger.logEntry("multiplying_operator");
    throw NotImplementedError("multiplying_operator");
    parseTreeLogger.logExit("multiplying_operator");
}

void Parser::new_ordinal_type(){
    parseTreeLogger.logEntry("new_ordinal_type");
    throw NotImplementedError("new_ordinal_type");
    parseTreeLogger.logExit("new_ordinal_type");
}

void Parser::new_pointer_type(){
    parseTreeLogger.logEntry("new_pointer_type");
    throw NotImplementedError("new_pointer_type");
    parseTreeLogger.logExit("new_pointer_type");
}

void Parser::new_structured_type(){
    parseTreeLogger.logEntry("new_structured_type");
    throw NotImplementedError("new_structured_type");
    parseTreeLogger.logExit("new_structured_type");
}

void Parser::new_type(){
    parseTreeLogger.logEntry("new_type");
    throw NotImplementedError("new_type");
    parseTreeLogger.logExit("new_type");
}

void Parser::ordinal_type(){
    parseTreeLogger.logEntry("ordinal_type");
    throw NotImplementedError("ordinal_type");
    parseTreeLogger.logExit("ordinal_type");
}

void Parser::ordinal_type_identifier(){
    parseTreeLogger.logEntry("ordinal_type_identifier");
    throw NotImplementedError("ordinal_type_identifier");
    parseTreeLogger.logExit("ordinal_type_identifier");
}

void Parser::packed_conformant_array_schema(){
    parseTreeLogger.logEntry("packed_conformant_array_schema");
    throw NotImplementedError("packed_conformant_array_schema");
    parseTreeLogger.logExit("packed_conformant_array_schema");
}

void Parser::pointer_type(){
    parseTreeLogger.logEntry("pointer_type");
    throw NotImplementedError("pointer_type");
    parseTreeLogger.logExit("pointer_type");
}

void Parser::procedural_parameter_specification(){
    parseTreeLogger.logEntry("procedural_parameter_specification");
    throw NotImplementedError("procedural_parameter_specification");
    parseTreeLogger.logExit("procedural_parameter_specification");
}

void Parser::procedure_and_function_declaration_part(){
    parseTreeLogger.logEntry("procedure_and_function_declaration_part");
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
    parseTreeLogger.logExit("procedure_and_function_declaration_part");
}

void Parser::procedure_block(){
    parseTreeLogger.logEntry("procedure_block");
    throw NotImplementedError("procedure_block");
    parseTreeLogger.logExit("procedure_block");
}

void Parser::procedure_declaration(){
    parseTreeLogger.logEntry("procedure_declaration");
    throw NotImplementedError("procedure_declaration");
    parseTreeLogger.logExit("procedure_declaration");
}

void Parser::procedure_heading(){
    parseTreeLogger.logEntry("procedure_heading");
    throw NotImplementedError("procedure_heading");
    parseTreeLogger.logExit("procedure_heading");
}

void Parser::procedure_identification(){
    parseTreeLogger.logEntry("procedure_identification");
    throw NotImplementedError("procedure_identification");
    parseTreeLogger.logExit("procedure_identification");
}

ProcedureToken Parser::procedure_identifier(){
    parseTreeLogger.logEntry("procedure_identifier");
    ProcedureToken result = ProcedureToken(curtoken.getLexeme());
    match(curtoken.getTag());
    parseTreeLogger.logExit("procedure_identifier");
    return result;
}

void Parser::procedure_statement(){
    parseTreeLogger.logEntry("procedure_statement");
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
    parseTreeLogger.logExit("procedure_statement");
}

void Parser::program(){
    parseTreeLogger.logEntry("program");
    program_heading();
    match(SEMICOLON);
    program_block();
    match(DOT);
    parseTreeLogger.logExit("program");
}

void Parser::program_block(){
    parseTreeLogger.logEntry("program_block");
    block();
    parseTreeLogger.logExit("program_block");
}

void Parser::program_heading(){
    parseTreeLogger.logEntry("program_heading");
    match(PROGRAM);
    identifier();
    if(curtoken.getTag() == LPAREN){
        match(LPAREN);
        program_parameter_list();
        match(RPAREN);
    }
    parseTreeLogger.logExit("program_heading");
}

void Parser::program_parameter_list(){
    parseTreeLogger.logEntry("program_parameter_list");
    throw NotImplementedError("program_parameter_list");
    parseTreeLogger.logExit("program_parameter_list");
}

void Parser::read_parameter_list(){
    parseTreeLogger.logEntry("read_parameter_list");
    throw NotImplementedError("read_parameter_list");
    parseTreeLogger.logExit("read_parameter_list");
}

void Parser::readln_parameter_list(){
    parseTreeLogger.logEntry("readln_parameter_list");
    throw NotImplementedError("readln_parameter_list");
    parseTreeLogger.logExit("readln_parameter_list");
}

void Parser::real_type_identifier(){
    parseTreeLogger.logEntry("real_type_identifier");
    throw NotImplementedError("real_type_identifier");
    parseTreeLogger.logExit("real_type_identifier");
}

void Parser::record_section(){
    parseTreeLogger.logEntry("record_section");
    throw NotImplementedError("record_section");
    parseTreeLogger.logExit("record_section");
}

void Parser::record_type(){
    parseTreeLogger.logEntry("record_type");
    throw NotImplementedError("record_type");
    parseTreeLogger.logExit("record_type");
}

void Parser::record_variable(){
    parseTreeLogger.logEntry("record_variable");
    throw NotImplementedError("record_variable");
    parseTreeLogger.logExit("record_variable");
}

void Parser::record_variable_list(){
    parseTreeLogger.logEntry("record_variable_list");
    throw NotImplementedError("record_variable_list");
    parseTreeLogger.logExit("record_variable_list");
}

void Parser::relational_operator(){
    parseTreeLogger.logEntry("relational_operator");
    throw NotImplementedError("relational_operator");
    parseTreeLogger.logExit("relational_operator");
}

void Parser::repeat_statement(){
    parseTreeLogger.logEntry("repeat_statement");
    throw NotImplementedError("repeat_statement");
    parseTreeLogger.logExit("repeat_statement");
}

void Parser::repetitive_statement(){
    parseTreeLogger.logEntry("repetitive_statement");
    throw NotImplementedError("repetitive_statement");
    parseTreeLogger.logExit("repetitive_statement");
}

void Parser::result_type(){
    parseTreeLogger.logEntry("result_type");
    throw NotImplementedError("result_type");
    parseTreeLogger.logExit("result_type");
}

void Parser::scale_factor(){
    parseTreeLogger.logEntry("scale_factor");
    throw NotImplementedError("scale_factor");
    parseTreeLogger.logExit("scale_factor");
}

Type Parser::set_constructor(){
    parseTreeLogger.logEntry("set_constructor");
    throw NotImplementedError("set_constructor");
    parseTreeLogger.logExit("set_constructor");
}

void Parser::set_type(){
    parseTreeLogger.logEntry("set_type");
    throw NotImplementedError("set_type");
    parseTreeLogger.logExit("set_type");
}

void Parser::sign(){
    parseTreeLogger.logEntry("sign");
    throw NotImplementedError("sign");
    parseTreeLogger.logExit("sign");
}

void Parser::signed_integer(){
    parseTreeLogger.logEntry("signed_integer");
    throw NotImplementedError("signed_integer");
    parseTreeLogger.logExit("signed_integer");
}

void Parser::signed_number(){
    parseTreeLogger.logEntry("signed_number");
    throw NotImplementedError("signed_number");
    parseTreeLogger.logExit("signed_number");
}

void Parser::signed_real(){
    parseTreeLogger.logEntry("signed_real");
    throw NotImplementedError("signed_real");
    parseTreeLogger.logExit("signed_real");
}

Type Parser::simple_expression(){
    parseTreeLogger.logEntry("simple_expression");
    if(curtoken.getTag() == PLUS || curtoken.getTag() == MINUS) sign();
    Type t1 = term(), t2;
    switch(curtoken.getTag()){
        case PLUS:
            match(PLUS);
            t2 = simple_expression();
            //synthesizer->genOpCode(synthesizer->lookupAdditionCode(t1, t2));
            t1 = synthesizer->genAdditionCode(t1, t2);
            break;
        case MINUS:
        case OR:
            throw NotImplementedError("MINUS and OR addition operators in simple_expression.");
    }
    parseTreeLogger.logExit("simple_expression");
    return t1;
}

void Parser::simple_statement(){
    parseTreeLogger.logEntry("simple_statement");
    switch(curtoken.getTag()){
        case GOTO:
            goto_statement();
            break;
        case TK_A_PROC:
            procedure_statement();
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
    parseTreeLogger.logExit("simple_statement");
}

void Parser::simple_type(){
    parseTreeLogger.logEntry("simple_type");
    throw NotImplementedError("simple_type");
    parseTreeLogger.logExit("simple_type");
}

void Parser::simple_type_identifier(){
    parseTreeLogger.logEntry("simple_type_identifier");
    throw NotImplementedError("simple_type_identifier");
    parseTreeLogger.logExit("simple_type_identifier");
}

void Parser::special_symbol(){
    parseTreeLogger.logEntry("special_symbol");
    throw NotImplementedError("special_symbol");
    parseTreeLogger.logExit("special_symbol");
}

void Parser::statement(){
    parseTreeLogger.logEntry("statement");
    if(curtoken.getTag() == LABEL){
        label();
        match(SEMICOLON);
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
    parseTreeLogger.logExit("statement");
}

void Parser::statement_part(){
    parseTreeLogger.logEntry("statement_part");
    compound_statement();
    parseTreeLogger.logExit("statement_part");
}

void Parser::statement_sequence(){
    parseTreeLogger.logEntry("statement_sequence");
    statement();
    while(curtoken.getTag() == SEMICOLON){
        match(SEMICOLON);
        statement();
    }
    parseTreeLogger.logExit("statement_sequence");
}

void Parser::string_character(){
    parseTreeLogger.logEntry("string_character");
    throw NotImplementedError("string_character");
    parseTreeLogger.logExit("string_character");
}

void Parser::string_element(){
    parseTreeLogger.logEntry("string_element");
    throw NotImplementedError("string_element");
    parseTreeLogger.logExit("string_element");
}

void Parser::structured_statement(){
    parseTreeLogger.logEntry("structured_statement");
    throw NotImplementedError("structured_statement");
    parseTreeLogger.logExit("structured_statement");
}

void Parser::structured_type(){
    parseTreeLogger.logEntry("structured_type");
    throw NotImplementedError("structured_type");
    parseTreeLogger.logExit("structured_type");
}

void Parser::structured_type_identifier(){
    parseTreeLogger.logEntry("structured_type_identifier");
    throw NotImplementedError("structured_type_identifier");
    parseTreeLogger.logExit("structured_type_identifier");
}

void Parser::subrange_type(){
    parseTreeLogger.logEntry("subrange_type");
    throw NotImplementedError("subrange_type");
    parseTreeLogger.logExit("subrange_type");
}

void Parser::tag_field(){
    parseTreeLogger.logEntry("tag_field");
    throw NotImplementedError("tag_field");
    parseTreeLogger.logExit("tag_field");
}

void Parser::tag_type(){
    parseTreeLogger.logEntry("tag_type");
    throw NotImplementedError("tag_type");
    parseTreeLogger.logExit("tag_type");
}

Type Parser::term(){
    parseTreeLogger.logEntry("term");
    Type t = factor();
    while(curtoken.getTag() == STAR ||
          curtoken.getTag() == FSLASH ||
          curtoken.getTag() == DIV ||
          curtoken.getTag() == MOD ||
          curtoken.getTag() == AND){
        match(curtoken.getTag());
        factor();
    }
    parseTreeLogger.logExit("term");
    return t;
}

void Parser::type_definition(){
    parseTreeLogger.logEntry("type_definition");
    throw NotImplementedError("type_definition");
    parseTreeLogger.logExit("type_definition");
}

void Parser::type_definition_part(){
    parseTreeLogger.logEntry("type_definition_part");
    if(curtoken.getTag() == TYP){
        match(TYP);
        while(curtoken.getTag() == ID){
            type_definition();
            match(SEMICOLON);
        }
    }
    parseTreeLogger.logExit("type_definition_part");
}

void Parser::type_denoter(){
    parseTreeLogger.logEntry("type_denoter");
    throw NotImplementedError("type_denoter");
    parseTreeLogger.logExit("type_denoter");
}

void Parser::type_identifier(){
    parseTreeLogger.logEntry("type_identifier");
    throw NotImplementedError("type_identifier");
    parseTreeLogger.logExit("type_identifier");
}

void Parser::unpacked_conformant_array_schema(){
    parseTreeLogger.logEntry("unpacked_conformant_array_schema");
    throw NotImplementedError("unpacked_conformant_array_schema");
    parseTreeLogger.logExit("unpacked_conformant_array_schema");
}

void Parser::unpacked_structured_type(){
    parseTreeLogger.logEntry("unpacked_structured_type");
    throw NotImplementedError("unpacked_structured_type");
    parseTreeLogger.logExit("unpacked_structured_type");
}

Type Parser::unsigned_constant(){
    parseTreeLogger.logEntry("unsigned_constant");
    Type t;
    switch(curtoken.getTag()){
        case INT:
        case REAL:
            t = unsigned_number();
            break;
        case STRING:
            t = character_string();
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
    parseTreeLogger.logExit("unsigned_constant");
    return t;
}

Type Parser::unsigned_integer(){
    parseTreeLogger.logEntry("unsigned_integer");
    //IntegerToken* inttok_ptr = (IntegerToken*) &curtoken;
    cout << "parser value: " << curtoken.getValue() << endl;
    size_t addr = synthesizer->writeUnsignedIntegerLiteralToHeader(curtoken);
    synthesizer->genOpCode(PUSH_INT);
    synthesizer->genAddress(addr);
    match(INT);
    parseTreeLogger.logExit("unsigned_integer");
    return Type(INTEGER_K);
}

Type Parser::unsigned_number(){
    parseTreeLogger.logEntry("unsigned_number");
    Type t;
    if(curtoken.getTag() == INT){
        t = unsigned_integer();
    } else if(curtoken.getTag() == REAL){
        t = unsigned_real();
    } else {
        throw 1;
    }
    parseTreeLogger.logExit("unsigned_number");
    return t;
}

Type Parser::unsigned_real(){
    parseTreeLogger.logEntry("unsigned_real");
    throw NotImplementedError("unsigned_real");
    parseTreeLogger.logExit("unsigned_real");
}

void Parser::value_conformant_array_specification(){
    parseTreeLogger.logEntry("value_conformant_array_specification");
    throw NotImplementedError("value_conformant_array_specification");
    parseTreeLogger.logExit("value_conformant_array_specification");
}

void Parser::value_parameter_specification(){
    parseTreeLogger.logEntry("value_parameter_specification");
    throw NotImplementedError("value_parameter_specification");
    parseTreeLogger.logExit("value_parameter_specification");
}

Type Parser::variable_access(){
    parseTreeLogger.logEntry("variable_access");
    throw NotImplementedError("variable_access");
    parseTreeLogger.logExit("variable_access");
}

void Parser::variable_conformant_array_specification(){
    parseTreeLogger.logEntry("variable_conformant_array_specification");
    throw NotImplementedError("variable_conformant_array_specification");
    parseTreeLogger.logExit("variable_conformant_array_specification");
}

void Parser::variable_declaration(){
    parseTreeLogger.logEntry("variable_declaration");
    throw NotImplementedError("variable_declaration");
    parseTreeLogger.logExit("variable_declaration");
}

void Parser::variable_declaration_part(){
    parseTreeLogger.logEntry("variable_declaration_part");
    if(curtoken.getTag() == VAR){
        match(VAR);
        while(curtoken.getTag() == ID){
            variable_declaration();
            match(SEMICOLON);
        }
    }
    parseTreeLogger.logExit("variable_declaration_part");
}

void Parser::variable_identifier(){
    parseTreeLogger.logEntry("variable_identifier");
    throw NotImplementedError("variable_identifier");
    parseTreeLogger.logExit("variable_identifier");
}

void Parser::variable_parameter_specification(){
    parseTreeLogger.logEntry("variable_parameter_specification");
    throw NotImplementedError("variable_parameter_specification");
    parseTreeLogger.logExit("variable_parameter_specification");
}

void Parser::variant(){
    parseTreeLogger.logEntry("variant");
    throw NotImplementedError("variant");
    parseTreeLogger.logExit("variant");
}

void Parser::variant_part(){
    parseTreeLogger.logEntry("variant_part");
    throw NotImplementedError("variant_part");
    parseTreeLogger.logExit("variant_part");
}

void Parser::variant_selector(){
    parseTreeLogger.logEntry("variant_selector");
    throw NotImplementedError("variant_selector");
    parseTreeLogger.logExit("variant_selector");
}

void Parser::while_statement(){
    parseTreeLogger.logEntry("while_statement");
    throw NotImplementedError("while_statement");
    parseTreeLogger.logExit("while_statement");
}

void Parser::with_statement(){
    parseTreeLogger.logEntry("with_statement");
    throw NotImplementedError("with_statement");
    parseTreeLogger.logExit("with_statement");
}

void Parser::word_symbol(){
    parseTreeLogger.logEntry("word_symbol");
    throw NotImplementedError("word_symbol");
    parseTreeLogger.logExit("word_symbol");
}

void Parser::write_parameter(){
    parseTreeLogger.logEntry("write_parameter");
    Type t = expression();
    synthesizer->genPrintCode(t);
    if(curtoken.getTag() == COLON){
        t = expression();
        synthesizer->genPrintCode(t);
    }
    if(curtoken.getTag() == COLON){
        t = expression();
        synthesizer->genPrintCode(t);
    }
    parseTreeLogger.logExit("write_parameter");
}

void Parser::write_parameter_list(){
    parseTreeLogger.logEntry("write_parameter_list");
    throw NotImplementedError("write_parameter_list");
    parseTreeLogger.logExit("write_parameter_list");
}

void Parser::writeln_parameter_list(){
    parseTreeLogger.logEntry("writeln_parameter_list");
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
    parseTreeLogger.logExit("writeln_parameter_list");
}

#endif
