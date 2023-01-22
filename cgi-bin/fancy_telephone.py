import os
import sys

def print_phone(the_name):
	print("Content-type: text/html\r\n\r\n")
	print("	<!DOCTYPE html>")
	print(" ")
	print("<html>")
	print("    <head>")
	print("        <title>")
	print("            [Analog Server] - from DMS")
	print("        </title>")
	print("		<link rel=\"icon\" href=\"favicon.ico\">")
	print("    </head>")
	print(" ")
	print("    <body style=\"text-align: left; ")
	print("        background-color: #ffa9cc;")
	print("        font-family:'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\"")
	print("        >")
	print("        <h1>This time in html!</h1>")
	print("<p>Hello " + the_name + ", Python CGI speaking?</p>")
	print("    </body>")
	print("</html>")

QUERY_STRING = os.getenv('QUERY_STRING')

if QUERY_STRING is None:
	print_phone("<Unknown>")
	sys.exit(0)

if QUERY_STRING.find('name') == -1:
	print_phone("<Unknown>")
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