#include "Debug.h"
#include "StateMachine.h"

StateMachineClass::StateMachineClass()
	:mCurrentState(START_STATE)
{
	INITMSG("New StateMachine");

	// default all move states
	for (int i = 0; i < LAST_STATE; i++) {
		for (int j = 0; j < LAST_CHAR; j++) {
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}

	// less / less equal / insertion (cout)
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;

	// greater / greater equal
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
	mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;

	// assignment / equal / not / notequal
	mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;
	mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
	mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;

	// + / += / - / -= / * / *= / \ / \=
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUS_EQUAL_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MINUS_EQUAL_STATE;
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[TIMES_STATE][EQUAL_CHAR] = TIMES_EQUAL_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[DIVIDE_STATE][EQUAL_CHAR] = DIVIDE_EQUAL_STATE;

	// or / and
	mLegalMoves[START_STATE][PIPE_CHAR] = PIPE_STATE;
	mLegalMoves[PIPE_STATE][PIPE_CHAR] = OR_STATE;
	mLegalMoves[START_STATE][AMPERSAND_CHAR] = AMPERSAND_STATE;
	mLegalMoves[AMPERSAND_STATE][AMPERSAND_CHAR] = AND_STATE;

	// semicolon / lparen / rparen / lcurly / rcurly
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;

	// identifier
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[START_STATE][UNDERBAR_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][UNDERBAR_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;

	// integer
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;

	// EOF
	mLegalMoves[START_STATE][EOF_CHAR] = ENDFILE_STATE;

	// whitespace
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;

	// block comment
	for (int i = 0; i < LAST_CHAR; i++) {
		mLegalMoves[BLOCKCOMMENTSTART_STATE][i] = BLOCKCOMMENTSTART_STATE;
		mLegalMoves[BLOCKCOMMENTEND_STATE][i] = BLOCKCOMMENTSTART_STATE;
	}
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENTSTART_STATE;
	mLegalMoves[BLOCKCOMMENTSTART_STATE][TIMES_CHAR] = BLOCKCOMMENTEND_STATE;
	mLegalMoves[BLOCKCOMMENTEND_STATE][TIMES_CHAR] = BLOCKCOMMENTEND_STATE;
	mLegalMoves[BLOCKCOMMENTEND_STATE][DIVIDE_CHAR] = START_STATE;

	// line comment
	for (int i = 0; i < LAST_CHAR; i++) {
		mLegalMoves[LINECOMMENT_STATE][i] = LINECOMMENT_STATE;
	}
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;
	mLegalMoves[LINECOMMENT_STATE][EOF_CHAR] = START_STATE;

	// default all tokens
	for (int i = 0; i < LAST_STATE; i++) {
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}
	// assign all defined tokens
	mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[NOT_STATE] = NOT_TOKEN;
	mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[PLUS_EQUAL_STATE] = PLUS_EQUAL_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[MINUS_EQUAL_STATE] = MINUS_EQUAL_TOKEN;
	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[TIMES_EQUAL_STATE] = TIMES_EQUAL_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_EQUAL_STATE] = DIVIDE_EQUAL_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
	mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currenCharacter, TokenType & correspondingTokenType)
{
	CharacterType charType = BAD_CHAR;

	if (isdigit(currenCharacter))
		charType = DIGIT_CHAR;
	else if (isalpha(currenCharacter))
		charType = LETTER_CHAR;
	else if (isspace(currenCharacter) && currenCharacter != '\n')
		charType = WHITESPACE_CHAR;
	else if (currenCharacter == '+')
		charType = PLUS_CHAR;
	else if (currenCharacter == '_')
		charType = MINUS_CHAR;
	else if (currenCharacter == '<')
		charType = LESS_CHAR;
	else if (currenCharacter == '=')
		charType = EQUAL_CHAR;
	else if (currenCharacter == '>')
		charType = GREATER_CHAR;
	else if (currenCharacter == '!')
		charType = NOT_CHAR;
	else if (currenCharacter == '-')
		charType = MINUS_CHAR;
	else if (currenCharacter == '*')
		charType = TIMES_CHAR;
	else if (currenCharacter == '/')
		charType = DIVIDE_CHAR;
	else if (currenCharacter == ';')
		charType = SEMICOLON_CHAR;
	else if (currenCharacter == '(')
		charType = LPAREN_CHAR;
	else if (currenCharacter == ')')
		charType = RPAREN_CHAR;
	else if (currenCharacter == '{')
		charType = LCURLY_CHAR;
	else if (currenCharacter == '}')
		charType = RCURLY_CHAR;
	else if (currenCharacter == '|')
		charType = PIPE_CHAR;
	else if (currenCharacter == '&')
		charType = AMPERSAND_CHAR;
	else if (currenCharacter == EOF)
		charType = EOF_CHAR;
	else if (currenCharacter == '\n')
		charType = NEWLINE_CHAR;
	else {
		std::cerr << "UpdateState: unhandled/bad char: (" << currenCharacter << ")" << std::endl;
		exit(-1);
	}

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}

std::ostream & operator<<(std::ostream & out, const StateMachineClass & sm) {
	out << sm.GetStateMachineName();
	return out;
}
