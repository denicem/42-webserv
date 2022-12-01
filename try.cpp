#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void	splitSettingValues(string& values, vector<string>& split)
{
	stringstream stream(values);
	string buffer;

	while (getline(stream, buffer, ','))
	{
		split.push_back(buffer);
	}
}

int main(void)
{
	string			str("yes");
	vector<string>	split;

	splitSettingValues(str, split);
	for (auto i : split) cout << i << endl;
}