#include "movie.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

Movie::Movie() = default;

Movie::Movie(int movieID, string tconst, string title , string desc, int runtime, int maturity, string genre, float rating, string maincast, string language){
    this -> movieID = movieID; //a unique running number for the system
    this -> tconst = tconst; //a unique indentifier for the movie
    this -> title = title; //title of move
    this -> desc = desc; //breif description of movie
    this -> genre = genre; //Genres of the movie
    this -> runtime = runtime; //duration in mins
    this -> maturity = maturity; // maturity of movie
    this -> rating = rating; //rating upon 10
    this -> mainCast = maincast; //main casts of movie
    this -> language = language; //main langauge of movie
}
//getters and setters of movies class
int Movie::getmovieID(){ return (this->movieID);}
void Movie::setmovieID(int movieID){this->movieID = movieID;}
string Movie::getTitle(){ return this->title;}
string Movie::getDesc(){ return this->desc;}
string Movie::getGenre(){ return this-> genre;}
int Movie::getDuration()(){ return this->duration;}
int Movie::getMaturity(){ return this->maturity;}
float Movie::getRating(){ return this->rating;}
string Movie::getMainCast(){return this->mainCast;}
string Movie::getLanguage(){return this->language;}
bool Movie::getIsShowing(){return this->isShowing;}
void Movie::setIsShowing(bool isShowing){this->isShowing = isShowing;}


Movie::~Movie(){cout << this->title << " is deleted." << endl;}
string Movie::serialize(){
    string serializedString = this->getTitle();
    serializedString += "," + this->getDesc();
    serializedString += "," + this->getGenre();
    serializedString += "," + to_string(this->getDuration());
    return serializedString;
}
void Movie::deserialize(string dataString) {
    vector<string> attributes = Movie::extractAttributesFromDataString(dataString);
    cout << attributes.size() << endl;
    if (attributes.size() < 4) throw ParseAttributeMismatchException();
    this->setTitle(attributes[0]);
    this->setDesc(attributes[1]);
    this->setGenre(attributes[2]);
    this->setDuration(stoi(attributes[3]));
}
