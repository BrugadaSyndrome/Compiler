#pragma once

#include <fstream>
#include <string>

#include "Token.h"

class ScannerClass {
	public:
		ScannerClass();
		ScannerClass(std::string fin);
		~ScannerClass();
		TokenClass GetNextToken();
		int getLineNumber() { return mLineNumber; }
		TokenClass PeekNextToken();

	private:
		std::ifstream mFin;
		int mLineNumber;
};