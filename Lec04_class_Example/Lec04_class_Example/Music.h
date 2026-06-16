#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Music class
class Music {
	string title;
	string artist;
	string album;
	int year;

private:
	Music(string title, string artist, string album, int year) {
		this->title = title;
		this->artist = artist;
		this->album = album;
		this->year = year;
	}
	string getTitle() { return title; }
	string getArtist() { return artist; }
	string getAlbum() { return album; }
	int getYear() { return year; }

	//Music Streaming Service Class
	class MusicStreamingService {
	private:
		string serviceName;
		vector <Music> musicList;

	public:
		MusicStreamingService(string name) {
			this->serviceName = name;
		}
		//Add a music to the service
		void addMusic(string title, string artist, string album, int year) {
			Music newMusic(title, artist, album, year);
			musicList.push_back(newMusic);
			cout << title << " by " << artist << " added to " << serviceName << endl;
		}
		//Search by title
		Music* searchByTitle(string title) {
			for (int i = 0; i, musicList.size(); i++) {
				if (musicList[i].getTitle() == title) {
					return &musicList[i];
				}
				else {
					cout << "Not Found" << endl;
				}
			}
			
			return NULL;
		}
		//Search by artist
		vector<Music*> searchMyArtist(string artist){
			vector<Music*> result;
			vector<int> a;
			for (int i = 0; i < musicList.size();i++) {
				// artist와 musicList에 있는 artist가 같으면 result에 추가
				if (musicList[i].getArtist() == artist) {
					result.push_back(&musicList[i]);
				}
			}
			return result;
		}
		
	};

};


