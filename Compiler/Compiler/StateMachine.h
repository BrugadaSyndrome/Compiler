#pragma once

#include <iostream>
#include <string>

#include "Token.h"

enum MachineState {
	// Relational Operators:
	LESS_STATE, LESSEQUAL_STATE, GREATER_STATE, GREATEREQUAL_STATE, EQUAL_STATE, NOT_STATE, NOTEQUAL_STATE,
	// Other Operators:
	INSERTION_STATE, ASSIGNMENT_STATE, PLUS_STATE, PLUS_EQUAL_STATE, MINUS_STATE, MINUS_EQUAL_STATE, TIMES_STATE, TIMES_EQUAL_STATE, DIVIDE_STATE, DIVIDE_EQUAL_STATE, OR_STATE, AND_STATE,
	// Other Characters:
	SEMICOLON_STATE, LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE,
	// Other STATE Types:
	IDENTIFIER_STATE, INTEGER_STATE, BAD_STATE, ENDFILE_STATE, PIPE_STATE, AMPERSAND_STATE,
	// Comment States
	BLOCKCOMMENTSTART_STATE, BLOCKCOMMENTEND_STATE, LINECOMMENT_STATE,
	// Special states
	START_STATE, CANTMOVE_STATE, LAST_STATE
};

const std::string gMachineStateNames[] = {
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOT", "NOTEQUAL",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE", "OR", "AND",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IDENTIFIER", "INTEGER", "BAD", "ENDFILE", "PIPE", "AMPERSAND",
	"BLOCKCOMMENTSTART", "BLOCKCOMMENTEND", "LINECOMMENT",
	"START", "CANTMOVE", "LAST"
};

enum CharacterType {
	// Normal chars
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR,
	// Symbol chars
	PLUS_CHAR, UNDERBAR_CHAR, LESS_CHAR, EQUAL_CHAR, GREATER_CHAR,
	NOT_CHAR, MINUS_CHAR, TIMES_CHAR, DIVIDE_CHAR, SEMICOLON_CHAR,
	LPAREN_CHAR, RPAREN_CHAR, LCURLY_CHAR, RCURLY_CHAR, EOF_CHAR,
	NEWLINE_CHAR, PIPE_CHAR, AMPERSAND_CHAR,
	// Special chars
	BAD_CHAR, LAST_CHAR
};

class StateMachineClass {
	public:
		StateMachineClass();
		MachineState UpdateState(char currenCharacter, TokenType & correspondingTokenType);
		const std::string &GetStateMachineName() const { return gMachineStateNames[mCurrentState]; }

	private:
		MachineState mCurrentState;
		MachineState mLegalMoves[LAST_STATE][LAST_CHAR];
		TokenType mCorrespondingTokenTypes[LAST_STATE];
};

std::ostream &operator<<(std::ostream &out, const StateMachineClass &sm);