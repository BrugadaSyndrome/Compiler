#include "Debug.h"
#include "Scanner.h"
#include "StateMachine.h"

#include <cstdlib>

ScannerClass::ScannerClass()
	:mLineNumber(1)
{
	INITMSG("New ScannerClass");
	mFin.open("input.txt", std::ifstream::in);
	if (!mFin) {
		std::cout << "input.txt not opened (most likely not found)" << std::endl;
		exit(-1);
	}
}

/*
ScannerClass::ScannerClass(std::string fin)
	:mLineNumber(1)
{
	INITMSG("New ScannerClass");
	mFin.open(fin, std::ifstream::in);
	if (!mFin) {
		std::cout << fin << " not opened (most likely not found)" << std::endl;
		exit(-1);
	}
}
*/

ScannerClass::~ScannerClass()
{
	mFin.close();
}

TokenClass ScannerClass::GetNextToken()
{
	StateMachineClass stateMachine;
	MachineState ms = START_STATE;
	TokenType tok = NONE_TOKEN;
	std::string lexeme = "";
	char c;

	do {
		SCANNERMSG("Scanner: " << stateMachine << " -> ");
		c = mFin.get();
		if (c == '\n') {
			mLineNumber++;
		}
		ms = stateMachine.UpdateState(c, tok);

		SCANNERMSGNL("read: (" << c << ") -> ms: " << stateMachine);
		if (ms == BAD_STATE) {
			std::cout << "GetNextToken: Bad State (" << lexeme << ")" << std::endl;
			exit(-1);
		}
		else if (ms == START_STATE)
			lexeme = "";
		else if (ms != CANTMOVE_STATE)
			lexeme += c;
	} while (ms != CANTMOVE_STATE);

	if (c == '\n') {
		mLineNumber--;
	}
	mFin.unget();
	TokenClass tc(tok, lexeme);
	tc.CheckReserved();
	return tc;
}

TokenClass ScannerClass::PeekNextToken() {
	int line = mLineNumber;
	std::streampos pos = mFin.tellg();
	TokenClass tc = GetNextToken();
	if (!mFin)
		mFin.clear();
	mLineNumber = line;
	mFin.seekg(pos);
	return tc;
}
