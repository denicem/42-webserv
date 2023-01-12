from bs4 import BeautifulSoup
import requests, csv

url_link = "https://myanimelist.net/topanime.php?type=tv&limit="

print("Content-type: text/plain\r\n\r\n")

with open("myAnimeList.csv", "w") as file:
	header = ["Rank", "Title", "Episodes", "Airing Time", "Score"]
	w = csv.writer(file, delimiter=',')
	w.writerow(header)
	for i in range(0, 500, 50):
		full_link = url_link + str(i)
		try:
			source = requests.get(full_link)
			source.raise_for_status()

			soup = BeautifulSoup(source.text, 'html.parser')

			anime_series = soup.find("table", class_="top-ranking-table").find_all("tr")
			for anime in anime_series:
				if anime.find("td").text == "Rank":
					continue
				rank = anime.find("td", class_="rank").text.strip(" \n")
				title = anime.find("td", class_="title").h3.text
				episodes = anime.find("td", class_="title").find("div", class_="information").text.split("\n")[1].strip(" ")
				airing_time = anime.find("td", class_="title").find("div", class_="information").text.split("\n")[2].strip(" ")
				score = anime.find("td", class_="score").text.strip(" \n")
				w.writerow([rank, title, episodes, airing_time, score])
				print(rank, title, episodes, airing_time, score)

		except Exception as e:
			print(e)

# TODO: implement with top current airing animes and it should add, not overwrite it