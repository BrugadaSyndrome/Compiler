#pragma once

#include <iostream>
#include <string>

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IF_TOKEN, WHILE_TOKEN, TRUE_TOKEN, FALSE_TOKEN, ENDL_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, PLUS_EQUAL_TOKEN, MINUS_TOKEN, MINUS_EQUAL_TOKEN, TIMES_TOKEN, TIMES_EQUAL_TOKEN, DIVIDE_TOKEN, DIVIDE_EQUAL_TOKEN, OR_TOKEN, AND_TOKEN, NOT_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, BAD_TOKEN, ENDFILE_TOKEN,
	// None Type:
	NONE_TOKEN
};

const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "IF", "WHILE", "TRUE", "FALSE", "ENDL",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL", 
	"INSERTION", "ASSIGNMENT", "PLUS", "PLUS_EQUAL", "MINUS", "MINUS_EQUAL", "TIMES", "TIMES_EQUAL", "DIVIDE", "DIVIDE_EQUAL", "OR", "AND", "NOT",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IDENTIFIER", "INTEGER", "BAD", "ENDFILE",
	"NONE"
};

class TokenClass {

	private:
		TokenType mType;
		std::string mLexeme;

	public:
		TokenClass(TokenType type, const std::string &lexeme);
		TokenType GetTokenType() const { return mType; }
		const std::string &GetTokenTypeName() const { return gTokenTypeNames[mType]; }
		std::string GetLexeme() const { return mLexeme; }
		void CheckReserved();
};

std::ostream &operator<<(std::ostream &out, const TokenClass &tc);