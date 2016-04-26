#include "Debug.h"
#include "Token.h"

#include <string>

TokenClass::TokenClass(TokenType type, const std::string & lexeme)
	:mType(type), mLexeme(lexeme) {
}

void TokenClass::CheckReserved() {
	DEBUGMSG("CheckReserved: (" << mLexeme << ") = ");
	if (mLexeme == "void")
		mType = VOID_TOKEN;
	else if (mLexeme == "main")
		mType = MAIN_TOKEN;
	else if (mLexeme == "int")
		mType = INT_TOKEN;
	else if (mLexeme == "cout")
		mType = COUT_TOKEN;
	else if (mLexeme == "if")
		mType = IF_TOKEN;
	else if (mLexeme == "while")
		mType = WHILE_TOKEN;
	else if (mLexeme == "true")
		mType = TRUE_TOKEN;
	else if (mLexeme == "false")
		mType = FALSE_TOKEN;
	else if (mLexeme == "endl")
		mType = ENDL_TOKEN;
	DEBUGMSGNL(gTokenTypeNames[mType]);
}

std::ostream & operator<<(std::ostream & out, const TokenClass & tc) {
	out << tc.GetTokenType() << " " << tc.GetTokenTypeName() << " " << tc.GetLexeme();
	return out;
}
