#include <stdio.h>
#include <string>

int main(int argc, char** argv, char** env)
{
	std::string	name;
	std::string	var;

	for (int i = 0; env[i] != NULL; i++) {
		var = env[i];
		if (var.rfind("QUERY_STRING=", 0) != std::string::npos)
		{
			var.erase(0, var.find('=')+1);
			while (!var.empty())
			{
				if (var.rfind("name=", 0) != std::string::npos) {
					var.erase(0, 5);
					name = var.substr(0, var.find('&'));
					break;
				}
				if (var.find('&') == std::string::npos)
					break;
				var.erase(0, var.find('&')+1);
			}
			break ;
		}
	}

	if (name.empty())
		name = "<Unknown>";

	printf("Content-type: text/plain\n\n");
	printf("\n");
	printf("   //\\\n");
	printf("  | \\/ ~~ Hello %s, CPP-written CGI speaking?\n", name.c_str());
	printf("  ||~                                             _     _\n");
	printf("  ||_                                            [ L___I ]\n");
	printf("  | /\\                                          |   ...   |\n");
	printf(" ,@\\\\/    ,@@@,            ,@@@@@,              |   :::   |\n");
	printf(" @,    ,@@\"   \"@@@,     ,@@\"     \"@@@,    ,@@@@\"|   '''   |\n");
	printf(" \"@@@@@\"          \"@@@@@\"            \"@@@@\"     '========='\n");
	printf("\n");
}