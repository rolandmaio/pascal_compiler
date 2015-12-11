#ifndef PARSER
#define PARSER

#include<list>
using std::list;
#include<unordered_map>
using std::unordered_map;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include "../token/token.h"
#include "../token/identifiertoken.h"
#include "../token/proceduretoken.h"
#include "../token/integertoken.h"
#include "../lexer/lexer.h"
#include "../token/tag.h"
#include "../parsetreelogger/parsetreelogger.h"
#include "../type/type.h"
#include "../type/kind.h"
#include "../type/subrangetype.h"
#include "../synthesizer/synthesizer.h"
#include "../symboltablemanager/symboltablemanager.h"

class Parser{

    public:
        bool parse();
        Parser(
            const char* sourceFile,
            Lexer *lexer,
            Synthesizer *synthesizer,
            ParseTreeLogger *parseTreeLogger,
            unordered_map<string, Token> *symboltable
        );
        void setSymbolTable(const char* lexeme);
        void chainSymbolTable(unordered_map<string, Token>* newSymbolTable);

    private:
        Lexer *lexer;
        list<unordered_map<string, Token>*> symboltables;
        unordered_map<string, Token> *symboltable;
        Token curtoken;
        bool isProcVar;
        int level;
        ParseTreeLogger *parseTreeLogger;
        Synthesizer *synthesizer;
        string headLabel;
        SymbolTableManager symboltablemanager;

        void match(Tag t);
        void fillGotoPlaceHolders();

        void actual_parameter();
        void actual_parameter_list();
        void adding_operator();
        void apostrophe_image();
        Type array_type();
        void array_variable();
        void assignment_statement();
        void base_type();
        void block();
        void Boolean_expression();
        void bound_identifier();
        void buffer_variable();
        void case_constant();
        void case_constant_list();
        void case_index();
        void case_list_element();
        void case_statement();
        Type character_string();
        Type component_type();
        Type component_variable();
        void compound_statement();
        void conditional_statement();
        void conformant_array_parameter_specification();
        void conformant_array_schema();
        void constant();
        void constant_definition();
        void constant_definition_part();
        Type constant_identifier();
        Type control_variable();
        void digit();
        void digit_sequence();
        void directive();
        void domain_type();
        void else_part();
        void empty_statement();
        Type entire_variable();
        void enumerated_type();
        Type expression();
        Type factor();
        void field_designator();
        void field_designator_identifier();
        void field_identifier();
        void field_list();
        void field_specififer();
        void file_type();
        void file_variable();
        Type final_value();
        void fixed_part();
        void for_statement();
        void formal_parameter_list();
        void formal_parameter_section();
        void fractional_part();
        void function_block();
        void function_declaration();
        Type function_designator();
        void function_heading();
        void function_identification();
        void function_identifier();
        void functional_parameter_specification();
        void goto_statement();
        void identified_variable();
        string identifier();
        vector<string> identifier_list();
        void if_statement();
        Type index_expression();
        Type index_type();
        void index_type_specification();
        Type indexed_variable();
        Type initial_value();
        string label();
        void label_declaration_part();
        void letter();
        void member_designator();
        void multiplying_operator();
        Type new_ordinal_type();
        void new_pointer_type();
        Type new_structured_type();
        Type new_type();
        Type ordinal_type();
        void ordinal_type_identifier();
        void packed_conformant_array_schema();
        void pointer_type();
        void procedural_parameter_specification();
        void procedure_and_function_declaration_part();
        void procedure_block();
        void procedure_declaration();
        void procedure_heading();
        void procedure_identification();
        ProcedureToken procedure_identifier();
        void procedure_statement();
        void program();
        void program_block();
        void program_heading();
        void program_parameter_list();
        void read_parameter_list();
        void readln_parameter_list();
        void real_type_identifier();
        void record_section();
        void record_type();
        void record_variable();
        void record_variable_list();
        void relational_operator();
        void repeat_statement();
        void repetitive_statement();
        void result_type();
        void scale_factor();
        Type set_constructor();
        void set_type();
        void sign();
        void signed_integer();
        void signed_number();
        void signed_real();
        Type simple_expression();
        void simple_statement();
        void simple_type();
        void simple_type_identifier();
        void special_symbol();
        void statement();
        void statement_part();
        void statement_sequence();
        void string_character();
        void string_element();
        void structured_statement();
        void structured_type();
        void structured_type_identifier();
        Type subrange_type();
        void tag_field();
        void tag_type();
        Type term();
        void type_definition();
        void type_definition_part();
        Type type_denoter();
        string type_identifier();
        void unpacked_conformant_array_schema();
        void unpacked_structured_type();
        Type unsigned_constant();
        Type unsigned_integer();
        Type unsigned_number();
        Type unsigned_real();
        void value_conformant_array_specification();
        void value_parameter_specification();
        Type variable_access();
        void variable_conformant_array_specification();
        void variable_declaration();
        void variable_declaration_part();
        Type variable_identifier();
        void variable_parameter_specification();
        void variant();
        void variant_part();
        void variant_selector();
        void while_statement();
        void with_statement();
        void word_symbol();
        void write_parameter();
        void write_parameter_list();
        void writeln_parameter_list();

};

#endif
