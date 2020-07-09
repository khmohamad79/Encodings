#include <iostream>
#include <string>
#include "Base64.h"

int main()
{
	char message[] = "HelloWorld!";		// length is 11
	std::cout << message << std::endl;
	
	char* encoded = Base64::encode(message, 11);
	std::cout << encoded << std::endl;

	char* decoded = Base64::decode(encoded, strlen(encoded));
	std::cout << decoded;
}