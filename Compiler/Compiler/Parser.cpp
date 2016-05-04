#include "Node.h"
#include "Parser.h"
#include "Token.h"

#include <cstdlib>
#include <iostream>

ParserClass::ParserClass(ScannerClass *sc, SymbolTableClass *st) : mScanner(sc), mTable(st) {
}

StartNode* ParserClass::Start() {
	DEBUGMSGNL("Start");
	ProgramNode *program = Program();
	Match(ENDFILE_TOKEN);
	StartNode *start = new StartNode(program);
	return start;
}

ProgramNode* ParserClass::Program() {
	DEBUGMSGNL("Program");
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode *block = Block();
	ProgramNode *program = new ProgramNode(block);
	return program;
}

BlockNode* ParserClass::Block() {
	DEBUGMSGNL("Block");
	Match(LCURLY_TOKEN);
	BlockNode* bn = new BlockNode(StatementGroup(), mTable);
	Match(RCURLY_TOKEN);
	return bn;
}

TokenClass ParserClass::Match(TokenType expectedType) {
	TokenClass currentToken = mScanner->GetNextToken();

	if (currentToken.GetTokenType() != expectedType) {
		MSGNL("Match: read " << currentToken.GetTokenTypeName() << " with value: " << currentToken.GetLexeme());
		MSGNL("Match: expected " << gTokenTypeNames[expectedType]);
		std::cerr << "Match: expected " << gTokenTypeNames[expectedType] << std::endl;
		exit(1);
	}
	else {
		MSGNL("Match: consumed " << currentToken.GetTokenTypeName() << " with value: " << currentToken.GetLexeme())
	}
	return currentToken;
}

StatementGroupNode* ParserClass::StatementGroup() {
	DEBUGMSGNL("StatementGroup");
	StatementGroupNode *sg = new StatementGroupNode();
	while (true) {
		StatementNode* sn = Statement();
		if (sn == NULL)
			break;
		DEBUGMSGNL("StatementGroup: Add Statement");
		sg->AddStatement(sn);
	}
	return sg;
}

StatementNode* ParserClass::Statement() {
	DEBUGMSGNL("Statement");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == INT_TOKEN) {
		Match(tt);
		return Declaration();
	}
	else if (tt == IDENTIFIER_TOKEN) {
		return Assignment();
	}
	else if (tt == COUT_TOKEN) {
		Match(tt);
		return Cout();
	}
	else if (tt == IF_TOKEN) {
		Match(tt);
		return If();
	}
	else if (tt == WHILE_TOKEN) {
		Match(tt);
		return While();
	}
	else {
		return NULL;
	}
}

StatementNode* ParserClass::Declaration() {
	IdentifierNode* id = Identifier();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();

	StatementNode* stmt;
	if (tt == SEMICOLON_TOKEN) {
		DEBUGMSGNL("Declaration");
		stmt = new DeclarationStatementNode(id);
	}
	else if (tt == ASSIGNMENT_TOKEN) {
		DEBUGMSGNL("Declaration Assignment");
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode* expression = Expression();
		stmt = new DeclarationAssignmentStatementNode(id, expression);
	}
	Match(SEMICOLON_TOKEN);
	return stmt;
}

StatementNode* ParserClass::Assignment() {
	TokenClass tc = Match(IDENTIFIER_TOKEN);
	IdentifierNode* identifier = new IdentifierNode(tc.GetLexeme(), mTable);
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	
	StatementNode* stmt;
	ExpressionNode* expression;
	if (tt == ASSIGNMENT_TOKEN) {
		DEBUGMSGNL("Assignment");
		Match(ASSIGNMENT_TOKEN);
		expression = Expression();
		stmt = new AssignmentStatementNode(identifier, expression);
	}
	else if (tt == PLUS_EQUAL_TOKEN) {
		DEBUGMSGNL("PlusAssignment");
		Match(PLUS_EQUAL_TOKEN);
		expression = Expression();
		stmt = new PlusAssignmentStatementNode(identifier, expression);
	}
	else if (tt == MINUS_EQUAL_TOKEN) {
		DEBUGMSGNL("MinusAssignment");
		Match(MINUS_EQUAL_TOKEN);
		expression = Expression();
		stmt = new MinusAssignmentStatementNode(identifier, expression);
	}
	else if (tt == TIMES_EQUAL_TOKEN) {
		DEBUGMSGNL("timesAssignment");
		Match(TIMES_EQUAL_TOKEN);
		expression = Expression();
		stmt = new TimesAssignmentStatementNode(identifier, expression);
	}
	else if (tt == DIVIDE_EQUAL_TOKEN) {
		DEBUGMSGNL("DivideAssignment");
		Match(DIVIDE_EQUAL_TOKEN);
		expression = Expression();
		stmt = new DivideAssignmentStatementNode(identifier, expression);
	}
	
	Match(SEMICOLON_TOKEN);
	return stmt;
}

StatementNode* ParserClass::Cout() {
	DEBUGMSGNL("Cout");
	// multiple insertions
	CoutStatementNode* cout = new CoutStatementNode();
	while (true) {
		Match(INSERTION_TOKEN);
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == ENDL_TOKEN) {
			Match(ENDL_TOKEN);
			cout->AddExpression(NULL);
		}
		else {
			ExpressionNode* expression = Expression();
			cout->AddExpression(expression);
		}

		if (mScanner->PeekNextToken().GetTokenType() != INSERTION_TOKEN)
			break;
	}
	Match(SEMICOLON_TOKEN);
	return cout;
}

StatementNode* ParserClass::If() {
	DEBUGMSGNL("If");
	Match(LPAREN_TOKEN);
	ExpressionNode* expression = Expression();
	Match(RPAREN_TOKEN);
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	BlockNode* block;
	// Curly's are present
	if (tt == LCURLY_TOKEN)
		block = Block();
	// Single statement with no curly's
	else {
		StatementNode* statement = Statement();
		StatementGroupNode* group = new StatementGroupNode();
		group->AddStatement(statement);
		block = new BlockNode(group, mTable);
	}
	return new IfStatementNode(expression, block);
}

StatementNode* ParserClass::While() {
	DEBUGMSGNL("While");
	Match(LPAREN_TOKEN);
	ExpressionNode* expression = Expression();
	Match(RPAREN_TOKEN);
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	BlockNode* block;
	// Curly's are present
	if (tt == LCURLY_TOKEN)
		block = Block();
	// Single statement with no curly's
	else {
		StatementNode* statement = Statement();
		StatementGroupNode* group = new StatementGroupNode();
		group->AddStatement(statement);
		block = new BlockNode(group, mTable);
	}
	return new WhileStatementNode(expression, block);
}

ExpressionNode* ParserClass::Expression() {
	DEBUGMSGNL("Expresison");
	ExpressionNode* c = Or();
	return c;
}

ExpressionNode* ParserClass::Or() {
	DEBUGMSGNL("AndOr");
	ExpressionNode *c = And();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == OR_TOKEN) {
			Match(OR_TOKEN);
			ExpressionNode *rhs = And();
			c = new OrNode(c, rhs);
		}
		else
			break;
	}
	return c;
}

ExpressionNode* ParserClass::And() {
	DEBUGMSGNL("AndOr");
	ExpressionNode *c = Relational();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == AND_TOKEN) {
			Match(AND_TOKEN);
			ExpressionNode *rhs = Relational();
			c = new AndNode(c, rhs);
		}
		else
			break;
	}
	return c;
}

ExpressionNode* ParserClass::Relational() {
	DEBUGMSGNL("Relational");
	ExpressionNode* c = PlusMinus();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN || tt == LESSEQUAL_TOKEN || tt == GREATER_TOKEN || tt == GREATEREQUAL_TOKEN || tt == EQUAL_TOKEN || tt == NOTEQUAL_TOKEN) {
		Match(tt);
		if (tt == LESS_TOKEN)
			c = new LessNode(c, PlusMinus());
		else if (tt == LESSEQUAL_TOKEN)
			c = new LessEqualNode(c, PlusMinus());
		else if (tt == GREATER_TOKEN)
			c = new GreaterNode(c, PlusMinus());
		else if (tt == GREATEREQUAL_TOKEN)
			c = new GreaterEqualNode(c, PlusMinus());
		else if (tt == EQUAL_TOKEN)
			c = new EqualNode(c, PlusMinus());
		else if (tt == NOTEQUAL_TOKEN)
			c = new NotEqualNode(c, PlusMinus());
	}
	return c;
}

ExpressionNode* ParserClass::PlusMinus() {
	DEBUGMSGNL("PlusMinus");
	ExpressionNode *c = TimesDivide();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN) {
			Match(PLUS_TOKEN);
			ExpressionNode *rhs = TimesDivide();
			c = new PlusNode(c, rhs);
		}
		else if (tt == MINUS_TOKEN) {
			Match(MINUS_TOKEN);
			ExpressionNode *rhs = TimesDivide();
			c = new MinusNode(c, rhs);
		}
		else {
			break;
		}
	}
	return c;
}

ExpressionNode* ParserClass::TimesDivide() {
	DEBUGMSGNL("TimesDivide");
	ExpressionNode *c = Not();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN) {
			Match(TIMES_TOKEN);
			ExpressionNode *rhs = Not();
			c = new TimesNode(c, rhs);
		}
		else if (tt == DIVIDE_TOKEN) {
			Match(DIVIDE_TOKEN);
			ExpressionNode *rhs = Not();
			c = new DivideNode(c, rhs);
		}
		else
			break;
	}
	return c;
}

ExpressionNode* ParserClass::Not() {
	DEBUGMSGNL("Not");
	ExpressionNode *c;
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == NOT_TOKEN) {
		Match(NOT_TOKEN);
		ExpressionNode *exp = Not();
		c = new NotNode(exp);
	}
	else {
		c = Factor();
	}
	return c;
}

ExpressionNode* ParserClass::Factor() {
	DEBUGMSGNL("Factor");
	ExpressionNode *c;
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == IDENTIFIER_TOKEN) {
		c = Identifier();
	}
	else if (tt == INTEGER_TOKEN) {
		c = Integer();
	}
	else if (tt == LPAREN_TOKEN) {
		Match(LPAREN_TOKEN);
		c = Expression();
		Match(RPAREN_TOKEN);
	}
	else {
		std::cerr << "Factor: bad input " << gTokenTypeNames[tt] << std::endl;
		exit(1);
	}
	return c;
}

IdentifierNode* ParserClass::Identifier() {
	DEBUGMSGNL("Identifier");
	IdentifierNode *c;
	TokenClass tc = mScanner->PeekNextToken();
	if (tc.GetTokenType() == IDENTIFIER_TOKEN) {
		Match(IDENTIFIER_TOKEN);
		c = new IdentifierNode(tc.GetLexeme(), mTable);
	}
	else {
		std::cout << "identifier: not an identifier: " << tc.GetTokenTypeName() << std::endl;
		exit(-1);
	}
	return c;
}

ExpressionNode* ParserClass::Integer() {
	DEBUGMSGNL("Integer");
	ExpressionNode *c;
	TokenClass tc = mScanner->PeekNextToken();
	if (tc.GetTokenType() == INTEGER_TOKEN) {
		Match(INTEGER_TOKEN);
		c = new IntegerNode(atoi(tc.GetLexeme().c_str()));
	}
	else {
		std::cout << "Integer: not an integer: " << tc.GetTokenTypeName() << std::endl;
		exit(-1);
	}
	return c;
}
