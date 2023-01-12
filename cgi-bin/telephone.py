import os
import sys

def print_phone(the_name):
	print("Content-type: text/plain\n\n")
	print("")
	print("   //\\")
	print("  | \\/ ~~ Hello " + the_name + ", Python CGI speaking?")
	print("  ||~                                             _     _")
	print("  ||_                                            [ L___I ]")
	print("  | /\\                                          |   ...   |")
	print(" ,@\\\\/    ,@@@,            ,@@@@@,              |   :::   |")
	print(" @,    ,@@\"   \"@@@,     ,@@\"     \"@@@,    ,@@@@\"|   '''   |")
	print(" \"@@@@@\"          \"@@@@@\"            \"@@@@\"     '========='")
	print("")

QUERY_STRING = os.getenv('QUERY_STRING')

if QUERY_STRING is None:
	print_phone("<Unknown>")
	sys.exit(0)

if QUERY_STRING.find('name') == -1:
	sys.exit(1)

array = QUERY_STRING.split('=')

final_name = ""

for (index, element) in enumerate(array):
	print(element)
	if element.find('name') != -1:
		name = array[index + 1]
		if name.find('&') != -1:
			final_name = name[:name.index('&')]
		else:
			final_name = name
		break

print_phone(final_name)