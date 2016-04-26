#pragma once

#include <string>
#include <vector>

#include "Debug.h"

class SymbolTableClass {

	struct Variable {
		std::string mLabel;
		int mValue;

		Variable(std::string label, int value) : mLabel(label), mValue(value) {};
	};

	public:
		SymbolTableClass();
		bool Exists(std::string s);
		void AddEntry(std::string s);
		int GetValue(std::string s);
		void SetValue(std::string s, int v);
		int GetIndex(std::string s);
		int GetCount() { return symbols.size(); }

		//void removeScope(int end, int begin);
		void PushScope();
		void PopScope();

	private:
		std::vector<Variable> symbols;
		std::vector<int> mScope;

};

//std::ostream &operator<<(std::ostream &out, const SymbolTableClass &sm);