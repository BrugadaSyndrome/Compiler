# This Makefile turns off exec protection
CXXFLAGS=-fno-stack-protector -D_FORTIFY_SOURCE=0

SimpleCompiler: main.o Node.o Parser.o Scanner.o StateMachine.o Symbol.o Token.o Instructions.o
	$(CXX) -o $@ $^ 
	execstack -s $@

Instructions.o: Instructions.cpp Instructions.h
main.o: main.cpp Node.h Parser.h Scanner.h StateMachine.h Symbol.h Token.h
Node.o: Node.cpp Node.h
Parser.o: Parser.cpp Node.h Parser.h Token.h
Scanner.o: Scanner.cpp Debug.h Scanner.h StateMachine.h
StateMachine.o: StateMachine.cpp Debug.h StateMachine.h
Symbol.o: Symbol.cpp Symbol.h
Token.o: Token.cpp Debug.h Token.h

clean:
	rm -f *.o SimpleCompiler
