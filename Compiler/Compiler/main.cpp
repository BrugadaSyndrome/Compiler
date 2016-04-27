#include <iostream>
#include <string>

#include "Node.h"
#include "Parser.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Symbol.h"
#include "Token.h"

int main() {

	///////
	// 1 //
	///////
	/*
	TokenType tt = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass tok1(tt, lexeme);
	std::cout << tok1 << std::endl;
	*/

	///////
	// 2 //
	///////
	/*
	std::string input_file = "input.txt";
	ScannerClass scanner(input_file);
	TokenClass tc(NONE_TOKEN, "");

	do {
		tc = scanner.GetNextToken();
		std::cout << scanner.getLineNumber() << ": " << tc.GetTokenTypeName() << " " << tc.GetLexeme() <<  std::endl;
	} while (tc.GetTokenType() != ENDFILE_TOKEN);
	*/

	///////
	// 3 //
	///////
	/*
	SymbolTableClass sc = SymbolTableClass();
	int size = 5;
	std::string symbols[] = { "symbol1" , "symbol2" , "symbol3" , "symbol4" , "symbol5" };
	int         values[] = { 1, 2, 3, 4, 5 };

	// break stuff
	//sc.GetValue("junk");
	//sc.SetValue("junk", 12345);
	//std::cout << sc.GetIndex("junk") << std::endl;

	for (int i = 0; i < 5; i++) {
		// Add
		sc.AddEntry(symbols[i]);
		std::cout << "AddEntry(" << symbols[i] << ")" << std::endl;

		// Set
		sc.SetValue(symbols[i], values[i]);
		std::cout << "SetValue(" << symbols[i] << "," << values[i] << ")" << std::endl;
		
		// Get
		int j = sc.GetValue(symbols[i]);
		std::cout << "GetValue(" << symbols[i] << ") returned Value: (" << j << ")" << std::endl;
		

		if (sc.Exists(symbols[i]))
			std::cout << "Symbol: (" << symbols[i] << ") exists at Index(" << sc.GetIndex(symbols[i]) << ") with Value: (" << sc.GetValue(symbols[i]) << ")" << std::endl;
		else
			std::cout << "Symbol: (" << symbols[i] << ") does not exist" << std::endl;
	}
	
	// break stuff
	//sc.AddEntry("symbol1");
	*/

	///////
	// 4 //
	///////
	/*
	StatementGroupNode *sn = new StatementGroupNode();

	IdentifierNode *n1 = new IdentifierNode("node1");
	DeclarationStatementNode *dsn = new DeclarationStatementNode(n1);
	sn->AddStatement(dsn);

	IdentifierNode *n2 = new IdentifierNode("node2");
	AssignmentStatementNode *asn = new AssignmentStatementNode(n2);
	sn->AddStatement(asn);

	IntegerNode *in1 = new IntegerNode(10);
	IntegerNode *in2 = new IntegerNode(20);
	IntegerNode *in3 = new IntegerNode(30);
	IntegerNode *in4 = new IntegerNode(40);
	IntegerNode *in5 = new IntegerNode(50);
	PlusNode *plusn = new PlusNode(in1, in2);
	MinusNode *mn = new MinusNode(plusn, in3);
	TimesNode *tn = new TimesNode(in4, mn);
	DivideNode *dn = new DivideNode(tn, in5);
	CoutStatementNode *csn = new CoutStatementNode(plusn);
	sn->AddStatement(csn);

	BlockNode *bn = new BlockNode(sn);
	ProgramNode *pn = new ProgramNode(bn);
	StartNode *start = new StartNode(pn);
	delete(start);
	*/

	///////
	// 5 //
	///////
	/*
	std::cout << std::endl;
	IntegerNode *a = new IntegerNode(5);
	IntegerNode *b = new IntegerNode(5);
	LessNode *ln = new LessNode(a, b);
	LessEqualNode *len = new LessEqualNode(a, b);
	GreaterNode *gn = new GreaterNode(a, b);
	GreaterEqualNode *gen = new GreaterEqualNode(a, b);
	EqualNode *en = new EqualNode(a, b);
	NotEqualNode *nen = new NotEqualNode(a, b);
	std::cout << std::endl
		<< "(" << a->Evaluate() << "<" << b->Evaluate() << ")=" << ln->Evaluate() << std::endl
		<< "(" << a->Evaluate() << "<=" << b->Evaluate() << ")=" << len->Evaluate() << std::endl
		<< "(" << a->Evaluate() << ">" << b->Evaluate() << ")=" << gn->Evaluate() << std::endl
		<< "(" << a->Evaluate() << ">=" << b->Evaluate() << ")=" << gen->Evaluate() << std::endl
		<< "(" << a->Evaluate() << "==" << b->Evaluate() << ")=" << en->Evaluate() << std::endl
		<< "(" << a->Evaluate() << "!=" << b->Evaluate() << ")=" << nen->Evaluate() << std::endl;
	*/

	///////
	// 6 //
	///////
	/*
	std::string input_file = "input.txt";
	ScannerClass scanner(input_file);
	TokenClass tc(NONE_TOKEN, "");
	TokenClass peek(NONE_TOKEN, "");

	do {
		peek = scanner.PeekNextToken();
		tc = scanner.GetNextToken();
		if (peek.GetLexeme() != tc.GetLexeme())
			std::cout << "uh-oh" << std::endl;
		std::cout << "PeekNextToken: " << scanner.getLineNumber() << ": " << peek.GetTokenTypeName() << " " << peek.GetLexeme() << std::endl;
		std::cout << "GetNextToken: " << scanner.getLineNumber() << ": " << tc.GetTokenTypeName() << " " << tc.GetLexeme() << std::endl << std::endl;
	} while (tc.GetTokenType() != ENDFILE_TOKEN);
	
	std::string input_file = "input.txt";
	ScannerClass* scanner = new ScannerClass(input_file);
	SymbolTableClass* table = new SymbolTableClass();
	ParserClass* parser = new ParserClass(scanner, table);
	StartNode* start = parser->Start();
	*/

	///////////
	// 7,8,9 //
	///////////
	ScannerClass* scanner = new ScannerClass();
	SymbolTableClass* table = new SymbolTableClass();
	ParserClass* parser = new ParserClass(scanner, table);
	StartNode* root = parser->Start();
	root->Interpret();
	InstructionsClass machinecode;
	root->Code(machinecode);
	machinecode.Finish();
	//machinecode.PrintAllMachineCodes();
	machinecode.Execute();

	delete root;

	return 0;
}
