#include "Matrix.h"




std::string to_string(double num) {
	 std::string str = std::to_string(num);
	 for (unsigned i = str.length() - 1; i >= 0; i--) {
		 if (str[i] == '0')
			 str.erase(str.begin() + i);
		 else {
			 if(str[i] == '.')
				str.erase(str.begin() + i);
			 return str;
		 }
	 }
	 return str;
}

