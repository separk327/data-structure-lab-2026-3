#include "Rectangle.h"
#include "Pet.h"
#include "Music.h"
using namespace std;
int main() {
	Rectangle rect1(4, 6);
	cout << "Rectangle 1:" << endl;
	//printf("Rectangle 1:\n");
	cout << "Area: " << rect1.getArea() << endl;
	//printf("Area: %lf\n".rect1.getArea());
	cout << "Perimeter: " << rect1.getPerimeter() << endl;
	cout << "Is Square? " << boolalpha << rect1.isSquare() << endl;
	printf("===========================================\n");

	Pet myPet("Lucky", 5, "dog");
	cout << "My pet's name is " << myPet.getName() << endl;
	cout << "My pet's age is " << myPet.getAge() << endl;
	cout << "My puppy's breed is " << myPet.getType() << endl;

	//Creat a new music streaming service
	Music::MusicStreamingService myService("Melon");
	//Add some music to the service
	myService.addMuisc("Jump", "Blackpink", "Jump", 2025);
	myService.addMuisc("Swim", "BTS", "ARIRANG", 2026);
	myService.addMuisc("BANG BANG", "IVE", "REVIVE", 2026);
	myService.addMuisc("404", "KiiiKiii", "Delulu", 2026);
	//Search by title
	string music_title;
	cout << "Enter the Music Title: ";
	cin >> music_title;
	Music* result = myService.searchByTitle(music_title);
	if (result != NULL) {
		cout << "Found: " << result->getTitle()
	}

	return 0;
}