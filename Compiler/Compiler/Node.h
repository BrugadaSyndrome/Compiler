#pragma once

#include <vector>

#include "Instructions.h"
#include "Symbol.h"

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class IdentifierNode;
class AssignmentStatementNode;
class ExpressionNode;
class CoutStatementNode;
class IntegerNode;
class ExpressionNode;
class BinaryOperatorNode;

// Base Nodes
class Node {
	public:
		virtual ~Node() {};
		virtual void Interpret()=0;
		virtual void Code(InstructionsClass &machineCode)=0;
	private:
};

class StatementNode : public Node {
	public:
	private:
};

class ExpressionNode {
public:
	virtual ~ExpressionNode() { INITMSG("Delete ExpressionNode"); }
	virtual int Evaluate()=0;
	virtual void CodeEvaluate(InstructionsClass &machineCode)=0;
private:
};

class StatementGroupNode : public Node {
	public:
		StatementGroupNode() { INITMSG("New StatementGroupNode"); };
		~StatementGroupNode();
		void AddStatement(StatementNode *sn) { nodes.push_back(sn); };
		void Interpret();
		void Code(InstructionsClass &machineCode);
	private:
		std::vector <StatementNode*> nodes;
};

class BlockNode : public StatementNode {
	public:
		BlockNode(StatementGroupNode *nsgn, SymbolTableClass *st) :sgn(nsgn), table(st) { INITMSG("New BlockNode"); };
		~BlockNode();
		void Interpret() { table->PushScope(); sgn->Interpret(); table->PopScope(); }
		void Code(InstructionsClass &machineCode) { table->PushScope(); sgn->Code(machineCode); table->PopScope(); }
	private:
		StatementGroupNode *sgn;
		SymbolTableClass *table;
};

class ProgramNode : public Node {
	public:
		ProgramNode(BlockNode *nbn) :bn(nbn) { INITMSG("New ProgramNode"); };
		~ProgramNode();
		void Interpret() { bn->Interpret(); }
		void Code(InstructionsClass &machineCode) { bn->Code(machineCode); }
	private:
		BlockNode *bn;
};

class StartNode : public Node {
	public:
		StartNode(ProgramNode *npn) :pn(npn) { INITMSG("New StartNode"); }
		~StartNode();
		void Interpret() { pn->Interpret(); }
		void Code(InstructionsClass &machineCode) { pn->Code(machineCode); }
	private:
		ProgramNode *pn;
};

class IdentifierNode : public ExpressionNode {
	public:
		IdentifierNode(std::string nl, SymbolTableClass *st) :label(nl), table(st) { INITMSG("New IdentifierNode"); }
		~IdentifierNode() { INITMSG("Delete IdentifierNode"); }
		void DeclareVariable() { table->AddEntry(label); }
		void SetValue(int v) { table->SetValue(label, v); }
		int GetIndex() { return table->GetIndex(label); }
		int Evaluate() { return table->GetValue(label); }
		void CodeEvaluate(InstructionsClass &machineCode);
	private:
		std::string label;
		SymbolTableClass *table;
};

class DeclarationStatementNode : public StatementNode {
	public:
		DeclarationStatementNode(IdentifierNode *nin) :in(nin) { INITMSG("New DeclarationStatementNode"); }
		~DeclarationStatementNode();
		void Interpret() { in->DeclareVariable(); }
		void Code(InstructionsClass &machineCode);
	private:
		IdentifierNode *in;
};

class AssignmentStatementNode : public StatementNode {
	public:
		AssignmentStatementNode(IdentifierNode *nin, ExpressionNode *nen) :in(nin), en(nen) { INITMSG("New AssignmentStatementNode"); }
		~AssignmentStatementNode();
		void Interpret();
		void Code(InstructionsClass &machineCode);
	private:
		IdentifierNode *in;
		ExpressionNode *en;
};

class PlusAssignmentStatementNode : public StatementNode {
public:
	PlusAssignmentStatementNode(IdentifierNode *nin, ExpressionNode *nen) :in(nin), en(nen) { INITMSG("New AssignmentStatementNode"); }
	~PlusAssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);
private:
	IdentifierNode *in;
	ExpressionNode *en;
};

class MinusAssignmentStatementNode : public StatementNode {
public:
	MinusAssignmentStatementNode(IdentifierNode *nin, ExpressionNode *nen) :in(nin), en(nen) { INITMSG("New AssignmentStatementNode"); }
	~MinusAssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);
private:
	IdentifierNode *in;
	ExpressionNode *en;
};

class TimesAssignmentStatementNode : public StatementNode {
public:
	TimesAssignmentStatementNode(IdentifierNode *nin, ExpressionNode *nen) :in(nin), en(nen) { INITMSG("New AssignmentStatementNode"); }
	~TimesAssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);
private:
	IdentifierNode *in;
	ExpressionNode *en;
};

class DivideAssignmentStatementNode : public StatementNode {
public:
	DivideAssignmentStatementNode(IdentifierNode *nin, ExpressionNode *nen) :in(nin), en(nen) { INITMSG("New AssignmentStatementNode"); }
	~DivideAssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);
private:
	IdentifierNode *in;
	ExpressionNode *en;
};

class CoutStatementNode : public StatementNode {
	public:
		CoutStatementNode() { INITMSG("New CoutStatementNode"); }
		~CoutStatementNode();
		void AddExpression(ExpressionNode *nen) { ens.push_back(nen); }
		void Interpret();
		void Code(InstructionsClass &machineCode);
	private:
		std::vector<ExpressionNode*> ens;
};

class IfStatementNode : public StatementNode {
	public:
		IfStatementNode(ExpressionNode *nen, BlockNode *bn) : test(nen), block(bn) { INITMSG("New IfNode"); }
		~IfStatementNode() { INITMSG("Delete IfNode"); }
		void Interpret();
		void Code(InstructionsClass &machineCode);
	private:
		ExpressionNode *test;
		BlockNode *block;
};

class WhileStatementNode : public StatementNode {
	public:
		WhileStatementNode(ExpressionNode *nen, BlockNode *bn) : test(nen), block(bn) { INITMSG("New WhileNode"); }
		~WhileStatementNode() { INITMSG("Delete WhileNode"); }
		void Interpret();
		void Code(InstructionsClass &machineCode);
	private:
		ExpressionNode *test;
		BlockNode *block;
};

class IntegerNode : public ExpressionNode {
	public:
		IntegerNode(int nv) :value(nv) { INITMSG("New IntegerNode"); }
		~IntegerNode();
		int Evaluate() { return value; }
		void CodeEvaluate(InstructionsClass &machineCode) { machineCode.PushValue(value); };
	private:
		int value;
};

class BinaryOperatorNode : public ExpressionNode {
	public:
		BinaryOperatorNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :lhs(nlhs), rhs(nrhs) { INITMSG("New BinaryOperatorNode"); }
		~BinaryOperatorNode();
	protected:
		ExpressionNode *lhs;
		ExpressionNode *rhs;
	private:
};

class PlusNode : public BinaryOperatorNode {
	public:
		PlusNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New PlusNode"); }
		~PlusNode() { INITMSG("Delete PlusNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "+" << rhs->Evaluate()); return lhs->Evaluate() + rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class MinusNode : public BinaryOperatorNode {
	public:
		MinusNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New MinusNode"); }
		~MinusNode() { INITMSG("Delete MinusNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "-" << rhs->Evaluate()); return lhs->Evaluate() - rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class TimesNode : public BinaryOperatorNode {
	public:
		TimesNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New TimesNode"); }
		~TimesNode() { INITMSG("Delete TimesNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "*" << rhs->Evaluate()); return lhs->Evaluate() * rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class DivideNode : public BinaryOperatorNode {
	public:
		DivideNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New DivideNode"); }
		~DivideNode() { INITMSG("Delete DivideNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "/" << rhs->Evaluate()); return lhs->Evaluate() / rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class LessNode : public BinaryOperatorNode {
	public:
		LessNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New LessNode"); }
		~LessNode() { INITMSG("Delete LessNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "<" << rhs->Evaluate()); return lhs->Evaluate() < rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class LessEqualNode : public BinaryOperatorNode {
	public:
		LessEqualNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New LessEqualNode"); }
		~LessEqualNode() { INITMSG("Delete LessEqualNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "<=" << rhs->Evaluate()); return lhs->Evaluate() <= rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterNode : public BinaryOperatorNode {
	public:
		GreaterNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New GreaterNode"); }
		~GreaterNode() { INITMSG("Delete GreaterNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << ">" << rhs->Evaluate()); return lhs->Evaluate() > rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterEqualNode : public BinaryOperatorNode {
	public:
		GreaterEqualNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New GreaterEqualNode"); }
		~GreaterEqualNode() { INITMSG("Delete GreaterEqualNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << ">=" << rhs->Evaluate()); return lhs->Evaluate() >= rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class EqualNode : public BinaryOperatorNode {
	public:
		EqualNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New EqualNode"); }
		~EqualNode() { INITMSG("Delete EqaulNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "==" << rhs->Evaluate()); return lhs->Evaluate() == rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class NotEqualNode : public BinaryOperatorNode {
	public:
		NotEqualNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New NotEqualNode"); }
		~NotEqualNode() { INITMSG("Delete NotEqualNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "!=" << rhs->Evaluate()); return lhs->Evaluate() != rhs->Evaluate(); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class OrNode : public BinaryOperatorNode {
	public:
		OrNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New OrNode"); }
		~OrNode() { INITMSG("Delete OrNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "||" << rhs->Evaluate()); return (lhs->Evaluate() || rhs->Evaluate()); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class AndNode : public BinaryOperatorNode {
	public:
		AndNode(ExpressionNode *nlhs, ExpressionNode *nrhs) :BinaryOperatorNode(nlhs, nrhs) { INITMSG("New AndNode"); }
		~AndNode() { INITMSG("Delete AndNode"); }
		int Evaluate() { OPERATORMSGNL(lhs->Evaluate() << "&&" << rhs->Evaluate()); return (lhs->Evaluate() && rhs->Evaluate()); }
		void CodeEvaluate(InstructionsClass &machineCode);
};

class UnaryOperatorNode : public ExpressionNode {
	public:
		UnaryOperatorNode(ExpressionNode *nex) :expression(nex) { INITMSG("New UnaryOperatorNode"); }
		~UnaryOperatorNode();
	protected:
		ExpressionNode *expression;
	private:
};

// not necessary for credit (done for midterm test)
class NotNode : public UnaryOperatorNode {
	public:
		NotNode(ExpressionNode *nex) : UnaryOperatorNode(nex) { INITMSG("New NotNode"); }
		~NotNode() { INITMSG("Delete NotNode"); }
		int Evaluate() { OPERATORMSGNL("!" << expression->Evaluate()); return (!expression->Evaluate()); }
		void CodeEvaluate(InstructionsClass &machineCode);
};
