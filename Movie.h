#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>

using namespace std;

class Movie {
    private:
        string mTitle;
        int mYear;
        float mScore;

    public:
        // TODO: Separar dupla set/get
        void setTitle(const string& mTitle);
        string getTitle() const;

        void setYear(int mYear);
        int getYear() const;

        void setScore(float mScore);
        float getScore() const;

};


#endif // !_MOVIE_H_




