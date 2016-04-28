#include <iostream>
#include <string>

#include "Node.h"
#include "Parser.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Symbol.h"
#include "Token.h"

const bool interpret = false;
const bool code = true;

int main() {

	ScannerClass* scanner = new ScannerClass();
	SymbolTableClass* table = new SymbolTableClass();
	ParserClass* parser = new ParserClass(scanner, table);
	StartNode* root = parser->Start();

	if (interpret) {
		root->Interpret();
	}

	if (code) {
		InstructionsClass machinecode;
		root->Code(machinecode);
		machinecode.Finish();
		machinecode.Execute();
	}

	delete root;

	return 0;
}
