#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <list>
#include <map>
#include "movie.h"
#include "util.h"

using namespace std;

  Movie::Movie(const string category, const string name, double price, int qty, const string genre, const string rating): Product(category, name, price, qty){
    genre_ = genre;
    rating_ = rating;
  }
  string Movie::displayString() const{
  stringstream ss;
  ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left." << "\n";

  return ss.str();
  }

  set<std::string> Movie::keywords() const{
  string nameL = convToLower(name_);
  string genreL = convToLower(genre_);
  set<string> list1 = parseStringToWords(genreL);
  set<string> list2 = parseStringToWords(nameL);

  set<string> keys = setUnion(list1,list2);
  keys.insert(rating_);

  return keys;
  }
  void Movie::dump(ostream& os) const{
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << genre_ << endl;
  os << rating_ << endl;
  }


