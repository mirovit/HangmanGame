#include<string>
using namespace std;

#ifndef _RUNTIME_EXCEPTIONS_

#define _RUNTIME_EXCEPTIONS_

class RuntimeException {  // generic run-time exception
private:
	string errorMsg;
public:
	RuntimeException(const string& err) { errorMsg = err; }
	string getMessage() const { return errorMsg; }
};

inline std::ostream& operator<<(std::ostream& out, const RuntimeException& e)
{
	return out << e.getMessage();
}

class FileDoesnotExist : public RuntimeException {
public:
	FileDoesnotExist(const string& err) : RuntimeException(err) {};
};


#endif // _RUNTIME_EXCEPTIONS_