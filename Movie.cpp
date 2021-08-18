#include "Movie.h"
#include <string>
using namespace std;

void Movie::setTitle(const string& title) {
	mTitle = title;
}

string Movie::getTitle() const {
	return mTitle;
}

void Movie::setYear(int year) {
	mYear = year;
}

int Movie::getYear() const {
	return mYear;
}

void Movie::setScore(float score) {
	mScore = score;
}
float Movie::getScore() const {
	return mScore;
}