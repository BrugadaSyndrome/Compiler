#pragma once

#include <iostream>

#define ShowMessages 0
#define ShowInit 0
#define DebugMessages 0
#define ScannerMessages 0
#define OperatorMessages 0

#if ShowMessages
	#define MSGNL(x) { std::cout << x << std::endl; }
	#define MSG(x) { std::cout << x; }
#else
	#define MSGNL(x) {}
	#define MSG(x) {}
#endif

#if ShowInit
	#define INITMSG(x) { std::cout << x << std::endl; }
#else
	#define INITMSG(x) { }
#endif

#if DebugMessages
	#define DEBUGMSGNL(x) { std::cout << x << std::endl; }
	#define DEBUGMSG(x) { std::cout << x; }
#else
	#define DEBUGMSGNL(x) { }
	#define DEBUGMSG(x) { }
#endif

#if ScannerMessages
	#define SCANNERMSGNL(x) { std::cout << x << std::endl; }
	#define SCANNERMSG(x) { std::cout << x; }
#else
	#define SCANNERMSGNL(x) { }
	#define SCANNERMSG(x) { }
#endif

#if ScannerMessages
	#define OPERATORMSGNL(x) { std::cout << x << std::endl; }
	#define OPERATORMSG(x) { std::cout << x; }
#else
	#define OPERATORMSGNL(x) { }
	#define OPERATORMSG(x) { }
#endif
