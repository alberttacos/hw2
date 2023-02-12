#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <list> 
#include <map>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, const string size, const string brand): Product(category, name, price, qty){
  size_ = size;
  brand_ = brand;
}
string Clothing::displayString() const{
  stringstream ss;
  ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << "\n";
  
  return ss.str();
}
set<string> Clothing::keywords() const{
  string nameL = convToLower(name_);
  string brandL = convToLower(brand_);
  set<string> list1 = parseStringToWords(nameL);
  set<string> list2 = parseStringToWords(brandL);

  set<string> keys = setUnion(list1,list2);

  keys.insert(size_);

  return keys;
}
void Clothing::dump(ostream& os) const{
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << size_ << endl;
  os << brand_<< endl;
}