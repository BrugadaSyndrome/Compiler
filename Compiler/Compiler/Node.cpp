#include "Node.h"

StartNode::~StartNode() {
	INITMSG("Delete StartNode");
	if (pn) {
		delete(pn);
		pn = 0;
	}
}

ProgramNode::~ProgramNode() {
	INITMSG("Delete ProgramNode");
	if (bn) {
		delete(bn);
		bn = 0;
	}
}

BlockNode::~BlockNode() {
	INITMSG("Delete BlockNode");
	if (sgn) {
		delete(sgn);
		sgn = 0;
	}
}

StatementGroupNode::~StatementGroupNode() {
	INITMSG("Delete StatementGroupNode");
	for (unsigned int i = 0; i < nodes.size(); i++)
		delete(nodes[i]);
}

void StatementGroupNode::Interpret() {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->Interpret();
	}
}

void StatementGroupNode::Code(InstructionsClass & machineCode){
	for (unsigned int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->Code(machineCode);
	}
}

IntegerNode::~IntegerNode() {
	INITMSG("Delete IntegerNode");
}

BinaryOperatorNode::~BinaryOperatorNode() {
	INITMSG("Delete BinaryOperatorNode");
	if (lhs) {
		DEBUGMSG("BON.LHS: ");
		delete(lhs);
		lhs = 0;
	}
	if (rhs) {
		DEBUGMSG("BON.RHS: ");
		delete(rhs);
		rhs = 0;
	}
}

void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode) {
	machineCode.PushVariable(table->GetIndex(label));
}

DeclarationStatementNode::~DeclarationStatementNode() {
	INITMSG("Delete DeclarationStatementNode");
	if (in) {
		delete(in);
		in = 0;
	}
}

void DeclarationStatementNode::Code(InstructionsClass &machineCode) {
	in->DeclareVariable();
	machineCode.PushValue(0);
	machineCode.PopAndStore(in->GetIndex());
}

DeclarationAssignmentStatementNode::~DeclarationAssignmentStatementNode() {
	INITMSG("Delete DeclarationAssignmentStatementNode");
	if (in) {
		delete(in);
		in = 0;
	}
}

void DeclarationAssignmentStatementNode::Interpret() {
	in->DeclareVariable();
	in->SetValue(en->Evaluate());
}

void DeclarationAssignmentStatementNode::Code(InstructionsClass & machineCode) {
	in->DeclareVariable();
	machineCode.PushValue(0);
	machineCode.PopAndStore(in->GetIndex());
	en->CodeEvaluate(machineCode);
	machineCode.PopAndStore(in->GetIndex());
}

AssignmentStatementNode::~AssignmentStatementNode() {
	INITMSG("Delete AssignmentNode");
	if (in) {
		delete(in);
		in = 0;
	}
	if (en) {
		delete(en);
		en = 0;
	}
}

void AssignmentStatementNode::Interpret() {
	in->SetValue(en->Evaluate());
}

void AssignmentStatementNode::Code(InstructionsClass &machineCode) {
	en->CodeEvaluate(machineCode);
	machineCode.PopAndStore(in->GetIndex());
}

PlusAssignmentStatementNode::~PlusAssignmentStatementNode() {
	INITMSG("Delete PlusAssignmentNode");
	if (in) {
		delete(in);
		in = 0;
	}
	if (en) {
		delete(en);
		en = 0;
	}
}

void PlusAssignmentStatementNode::Interpret() {
	in->SetValue(in->Evaluate() + en->Evaluate());
}

void PlusAssignmentStatementNode::Code(InstructionsClass &machineCode) {
	// push vars value on stack
	machineCode.PushVariable(in->GetIndex());
	// put modifier on stack
	en->CodeEvaluate(machineCode);
	// add those values
	machineCode.PopPopAddPush();
	// store result
	machineCode.PopAndStore(in->GetIndex());
}

MinusAssignmentStatementNode::~MinusAssignmentStatementNode() {
	INITMSG("Delete MinusAssignmentNode");
	if (in) {
		delete(in);
		in = 0;
	}
	if (en) {
		delete(en);
		en = 0;
	}
}

void MinusAssignmentStatementNode::Interpret() {
	in->SetValue(in->Evaluate() - en->Evaluate());
}

void MinusAssignmentStatementNode::Code(InstructionsClass &machineCode) {
	// push vars value on stack
	machineCode.PushVariable(in->GetIndex());
	// put modifier on stack
	en->CodeEvaluate(machineCode);
	// subtract those values
	machineCode.PopPopSubPush();
	// store result
	machineCode.PopAndStore(in->GetIndex());
}

TimesAssignmentStatementNode::~TimesAssignmentStatementNode() {
	INITMSG("Delete TimesAssignmentNode");
	if (in) {
		delete(in);
		in = 0;
	}
	if (en) {
		delete(en);
		en = 0;
	}
}

void TimesAssignmentStatementNode::Interpret() {
	in->SetValue(in->Evaluate() * en->Evaluate());
}

void TimesAssignmentStatementNode::Code(InstructionsClass &machineCode) {
	// push vars value on stack
	machineCode.PushVariable(in->GetIndex());
	// put modifier on stack
	en->CodeEvaluate(machineCode);
	// multiply those values
	machineCode.PopPopMulPush();
	// store result
	machineCode.PopAndStore(in->GetIndex());
}

DivideAssignmentStatementNode::~DivideAssignmentStatementNode() {
	INITMSG("Delete DivideAssignmentNode");
	if (in) {
		delete(in);
		in = 0;
	}
	if (en) {
		delete(en);
		en = 0;
	}
}

void DivideAssignmentStatementNode::Interpret() {
	in->SetValue(in->Evaluate() / en->Evaluate());
}

void DivideAssignmentStatementNode::Code(InstructionsClass &machineCode) {
	// push vars value on stack
	machineCode.PushVariable(in->GetIndex());
	// put modifier on stack
	en->CodeEvaluate(machineCode);
	// divide those values
	machineCode.PopPopDivPush();
	// store result
	machineCode.PopAndStore(in->GetIndex());
}

CoutStatementNode::~CoutStatementNode() {
	INITMSG("Delete CoutStatementNode");
	for (unsigned int i = 0; i < ens.size(); i++) {
		if (ens.at(i)) {
			delete(ens.at(i));
		}
	}
	ens.resize(0);
}

void CoutStatementNode::Interpret() {
	for (unsigned int i = 0; i < ens.size(); i++) {
		if (ens.at(i) != NULL) {
			ens.at(i)->Evaluate();
		}
	}
}

void CoutStatementNode::Code(InstructionsClass &machineCode) {
	for (unsigned int i = 0; i < ens.size(); i++) {
		if (ens.at(i) == NULL) {
			machineCode.WriteEndl();
		}
		else {
			ens.at(i)->CodeEvaluate(machineCode);
			machineCode.PopAndWrite();
		}
	}
}

void IfStatementNode::Interpret() {
	if (test->Evaluate()) {
		block->Interpret();
	}
}

void IfStatementNode::Code(InstructionsClass &machineCode) {
	// evaluate test and put on stack
	test->CodeEvaluate(machineCode);
	// get variable to record 'size' of block
	unsigned char* jump_address = machineCode.SkipIfZeroStack();
	// measure block 'size'
	unsigned char* block_start = machineCode.GetAddress();
	block->Code(machineCode);
	unsigned char* block_end = machineCode.GetAddress();
	// set variable that records 'size' of block
	machineCode.SetOffset(jump_address, block_end - block_start);
}

void WhileStatementNode::Interpret() {
	while (test->Evaluate()) {
		block->Interpret();
	}
}

void WhileStatementNode::Code(InstructionsClass &machineCode) {
	// store beginning of while evaluate
	unsigned char* begin_address = machineCode.GetAddress();
	// evaluate test and put on stack
	test->CodeEvaluate(machineCode);
	// get variable to record 'size' of block
	unsigned char* jump_address = machineCode.SkipIfZeroStack();
	// measure block 'size'
	unsigned char* block_start = machineCode.GetAddress();
	block->Code(machineCode);
	unsigned char* jump_address2 = machineCode.Jump();
	unsigned char* block_end = machineCode.GetAddress();
	// set variable that records 'size' of block
	machineCode.SetOffset(jump_address, block_end - block_start);
	// set variable that jumps to the while loop evaluate
	machineCode.SetOffset(jump_address2, begin_address - block_end);
}

void PlusNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}

void MinusNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}

void TimesNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

void DivideNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
}

void LessNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopLessPush();
}

void LessEqualNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

void GreaterNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterPush();
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterEqualPush();
}

void EqualNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopEqualPush();
}

void NotEqualNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopNotEqualPush();
}

void OrNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopOrPush();
}

void AndNode::CodeEvaluate(InstructionsClass & machineCode) {
	lhs->CodeEvaluate(machineCode);
	rhs->CodeEvaluate(machineCode);
	machineCode.PopPopAndPush();
}

UnaryOperatorNode::~UnaryOperatorNode() {
	INITMSG("Delete UnaryOperatorNode");
	if (expression) {
		delete(expression);
		expression = 0;
	}
}

void NotNode::CodeEvaluate(InstructionsClass & machineCode) {
	expression->CodeEvaluate(machineCode);
	machineCode.LogicalNot();
}
