#ifndef PARSER
#define PARSER

#include "token.h"
#include "lexer.h"

class Parser{

    public:
        bool parse();
        Parser(const char* sourceFile):lexer(sourceFile){}

    private:
        Lexer lexer;
        Token curtoken;

        void program();
        void program_heading();
        void program_parameter_list();
        void program_block();

        void identifier();
        void identifier_list();

        void block();
        void label_declaration_part();
        void constant_definition_part();
        void type_definition_part();
        void variable_declaration_part();
        void procedure_and_function_declaration_part();
        void statement_part();

        void label();
        void constant_definition();
        void constant();
        void sign();
        void unsigned_number();
        void constant_identifier();
        void character_string();

        void unsigned_integer();
        void unsigned_real();
        void digit_sequence();
        void fractional_part();
        void scale_factor();

        void type_definition();
        void type_denoter();
        void type_identifier();
        void new_type();

        void new_ordinal_type();
        void new_structured_type();
        void new_pointer_type();

        void enumerated_type();
        void subrange_type();

}

#endif
