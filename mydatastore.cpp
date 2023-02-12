#include <string>
#include <set>
#include "book.h"
#include <sstream>
#include <iostream>
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){

}
  
MyDataStore::~MyDataStore(){

  vector<Product*>::iterator ITproduct;

  for(ITproduct  = PRODUCT.begin(); ITproduct != PRODUCT.end(); ++ITproduct){
    delete *ITproduct;
  }

  vector<User*>::iterator ITuser;

  for(ITuser = USERVECTOR.begin(); ITuser != USERVECTOR.end(); ++ITuser){
    delete *ITuser;
  }
}
  
void MyDataStore::addProduct(Product* p){

  PRODUCT.push_back(p);

  set<string> keywords = p->keywords();

  set<string>::iterator IT1;
  map<string, set<Product*>>::iterator IT2;

  for(IT1 = keywords.begin(); IT1 != keywords.end(); ++IT1){
    IT2 = KEYWORD.find(*IT1);
    
    if(IT2 == KEYWORD.end()){
      set<Product*> tempkey;
      tempkey.insert(p);

      KEYWORD.insert({*IT1,tempkey});
    }else{
      IT2->second.insert(p);
    }
  }

}
  
void MyDataStore::addUser(User* u){
  string newuser = u->getName();
  USER.insert({newuser, u});

  vector<Product*> newcart;

  CARTMAP.insert({newuser,newcart});

  USERVECTOR.push_back(u);

}
  
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  set<Product*> temp;
  if (type == 0) 
  {
    for(size_t i = 0; i < terms.size(); i++)
    {
      for (string str : terms)
      {
        if (KEYWORD.find(str) != KEYWORD.end()){
        temp = setIntersection<Product*>(temp, KEYWORD[str]); 
        }
      } 
    }
  }
  else if (type == 1) 
  {
    for(size_t i = 0; i < terms.size(); i++)
    {
      for (string str : terms)
      {
        if (KEYWORD.find(str) != KEYWORD.end()){
        temp = setUnion<Product*>(temp, KEYWORD[str]); 
        }
      } 
    }
  }
  vector<Product*> temp2(temp.begin(), temp.end());   
  hits = temp2;
  return hits; 
}

  
void MyDataStore::dump(std::ostream& ofile){
  vector<Product*>:: iterator IT;
  map<string, User*>:: iterator IT2;

  ofile << "<products>" << endl;

  for(IT = PRODUCT.begin(); IT != PRODUCT.end(); ++IT){
    (**IT).dump(ofile);

  }
  ofile << "</products>" << endl;
  
  ofile << "<users>" << endl;

  for(IT2 = USER.begin(); IT2 != USER.end(); ++IT2){
    IT2 ->second->dump(ofile);
  }
  ofile << "</users>" << endl;
}

  
void MyDataStore::addCart(std::string user, Product* p){

  map<string, vector<Product*>>::iterator IT = CARTMAP.find(user);
  (IT->second).push_back(p);
  cout << "Added to Cart" << endl;

  if(IT == CARTMAP.end()){
    cout << "Invalid Request" << endl;
  }
}
  
void MyDataStore::viewCart(std::string user){
  if(CARTMAP.find(user) != CARTMAP.end()){
    int x = 1;
    for(vector<Product*>::iterator IT = CARTMAP[user].begin(); IT != CARTMAP[user].end(); ++IT){
      cout << "Item " << x++ << endl;
      cout << (*IT)->displayString() << endl;

    }
  }
  else{
    cout << "Invalid Username" << endl;
  }
}
  
void MyDataStore::buyCart(string user){
  
   map<string, vector<Product*>>::iterator IT = CARTMAP.find(user);
    
    if(IT == CARTMAP.end()){
    cout << "Invalid username" << endl;
    return;
  }
  User* u = (USER.find(user))->second;
   vector<Product*> newcart;
   vector<Product*> oldcart = IT ->second;


    for(vector<Product*>::iterator IT2 = oldcart.begin(); IT2 != oldcart.end(); ++IT2){
      Product* tempProd = *IT2;
      if(tempProd->getQty() >= 1 && u->getBalance() >= tempProd->getPrice()){
        tempProd->subtractQty(1);
        u->deductAmount(tempProd->getPrice());
      }
      else{
        newcart.push_back(tempProd);

      }
    }
  
  CARTMAP[user] = newcart;


  /*else{

    for(vector<Product*>::iterator IT2 = CARTMAP[user].begin(); IT2 != CARTMAP[user].end(); ++IT2){
      if((*IT2)->getQty() > 0 && USER[user]->getBalance() >= (*IT2)->getPrice()){
        (*IT2)->subtractQty(1);
        USER[user]->deductAmount((*IT2)->getPrice());
        CARTMAP[user].erase(IT2);
      }
      else{
        ++IT2;
      }
    }
  }*/
}

