#pragma once
#include <string>
#include <vector>
#include "show.h"
#include "repository_template.h"
#include "repository_exception.h"

using namespace std;

class Movie : public AbstractDataModel {
private:
	string title; //title of move
	string desc; //breif description of movie
	string genre; //Genres of the movie
  
  //resolve this later
	int duration{};
  int runtime; //duration in mins
  
  int movieID; //a unique running number for the system
  string tconst; //a unique indentifier for the movie
	
	
    int maturity; //0 =G, 1 = PG, 2 = PG13, 3 = NC16, 4 = M18, 5 =R21
    float rating; //rating upon 10
    string mainCast; //main casts of movie
    string language;
    bool isShowing; //if the movie is showing
    vector<Show> shows;
public:
    //Constructors
    Movie(); // for deserialization
	Movie(int, string, string, string, int, int, string, float, string, string);
	~Movie();
    //Parameterised Constructor
    //Getters and Setters
    int getmovieID();
    void setmovieID(int);
	string getTitle();
    void setTitle(string);
	string getDesc();
    void setDesc(string);
	string getGenre();
    void setGenre(string);
	int getDuration() const;
    void setDuration(int);
    int getMaturity();
    float getRating();
    string getMainCast();
    string getLanguage();
    bool getIsShowing();
    void setIsShowing(bool);
    
    // AbstractDataModel
    string serialize() override;
    void deserialize(string) override;
};
