#pragma once

#include "Scanner.h"
#include "Symbol.h"

class ParserClass {
	public:
		ParserClass(ScannerClass *sc, SymbolTableClass *st);
		StartNode* Start();
		ProgramNode* Program();
		BlockNode* Block();
		TokenClass Match(TokenType tt);
		StatementGroupNode* StatementGroup();
		StatementNode* Statement();
		StatementNode* Declaration();
		StatementNode* Assignment();
		StatementNode* Cout();
		StatementNode* If();
		StatementNode* While();
		ExpressionNode* Expression();
		ExpressionNode* Or();
		ExpressionNode* And();
		ExpressionNode* Relational();
		ExpressionNode* PlusMinus();
		ExpressionNode* TimesDivide();
		ExpressionNode* Not();
		ExpressionNode* Factor();
		IdentifierNode* Identifier();
		ExpressionNode* Integer();

	private:
		ScannerClass *mScanner;
		SymbolTableClass *mTable;
};