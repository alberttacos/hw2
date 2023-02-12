#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <list>
#include <map>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string category, const string name, double price, int qty, const string isbn, const string author) : Product(category, name, price, qty){
  isbn_ = isbn;
  author_ = author;
}
string Book::displayString() const{
  stringstream ss;
  ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << "\n";

  return ss.str();
}

set<string> Book::keywords() const{
  string nameL = convToLower(name_);
  string authorL = convToLower(author_);
  set<string> list1 = parseStringToWords(authorL);
  set<string> list2 = parseStringToWords(nameL);

  set<string> keys = setUnion<string>(list1,list2);
  keys.insert(isbn_);

  return keys;
}
void Book::dump(ostream& os) const{
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << isbn_ << endl;
  os << author_ << endl;
  
}
