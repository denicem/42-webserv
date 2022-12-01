#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main(void)
{
	vector<string>	split;

	stringstream stream(",,,,");
	string buffer;

	while (getline(stream, buffer, ','))
	{
		split.push_back(buffer);
	}
	if (split.empty())
		std::cout << "ssplit is empty";
	std::cout << split.empty();
	for (auto i : split) cout << i.empty() << endl;
}