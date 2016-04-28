#include "Symbol.h"

#include <cstdlib>
#include <iostream>

SymbolTableClass::SymbolTableClass() {
	INITMSG("New SymbolTableClass");
}

bool SymbolTableClass::Exists(std::string s) {
	for (unsigned int i = symbols.size()-1; i >= 0; i--) {
		if (s == symbols.at(i).mLabel) {
			return true;
		}
	}
	return false;
}

void SymbolTableClass::AddEntry(std::string s) {
	for (int i = symbols.size()-1; i >= mScope.back(); i--) {
		if (s == symbols.at(i).mLabel) {
			std::cerr << "SymbolTableClass::AddEntry: Symbol already exists: (" << s << ")" << std::endl;
			exit(-1);
		}
	}
	symbols.push_back(Variable(s, 0));
}

int SymbolTableClass::GetValue(std::string s) {
	for (int i = symbols.size()-1; i >=  0; i--) {
		if (s == symbols.at(i).mLabel) {
			return symbols.at(i).mValue;
		}
	}
	std::cerr << "SymbolTableClass::GetValue: No such symbol exists: (" << s << ")" << std::endl;
	exit(-1);
}

void SymbolTableClass::SetValue(std::string s, int v) {
	for (unsigned int i = symbols.size()-1; i >= 0; i--) {
		if (s == symbols.at(i).mLabel) {
			symbols.at(i).mValue = v;
			return;
		}
	}
	std::cerr << "SymbolTableClass::SetValue: No such symbol exists: (" << s << ")" << std::endl;
	exit(-1);
}

int SymbolTableClass::GetIndex(std::string s) {
	for (int i = symbols.size()-1; i >= 0; i--) {
		if (s == symbols.at(i).mLabel) {
			return i;
		}
	}
	std::cerr << "SymbolTableClass::GetIndex: No such index exists: (" << s << ")" << std::endl;
	exit(-1);
}

void SymbolTableClass::PushScope() {
	mScope.push_back(GetCount());
}

void SymbolTableClass::PopScope() {
	for (int i = GetCount(); i > mScope.back(); i--) {
		symbols.pop_back();
	}
	mScope.pop_back();
}
