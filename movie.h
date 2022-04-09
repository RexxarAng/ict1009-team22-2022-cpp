#ifndef ICT1009_TEAM22_2022_MOVIE_H
#define ICT1009_TEAM22_2022_MOVIE_H
#include <string>
#include <vector>
#include "repository_template.h"
#include "repository_exception.h"

using namespace std;

class Movie : public AbstractDataModel {
private:
    string movieID;
	string title;
	string desc;
	string genre;
	int duration{};
    int maturity;
    float rating;
    string mainCast;
    string language;

public:
    Movie(); // for deserialization
	Movie(string, string, string, int);
    string getMovieID();
    void setMovieID(string);
	string getTitle();
	void setTitle(string);
	string getDesc();
	void setDesc(string);
	string getGenre();
	void setGenre(string);
	int getDuration() const;
	void setDuration(int);
    int getMaturity();
    void setMaturity(int);
    float getRating();
    void setRating(float);
    string getMainCast();
    void setMainCast(string);
    string getLanguage();
    void setLanguage(string);
	friend istream& operator>>(istream&, Movie*);
    friend ostream& operator<<(ostream&, Movie*);
    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};
#endif
