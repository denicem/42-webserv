#include <string>
#include <iostream>

int main(void)
{
	std::string str("hello:yes");

	std::cout << str.erase(0, str.find(':')+1) << '\n';
}