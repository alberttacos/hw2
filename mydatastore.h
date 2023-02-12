#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore
{
  public:
  MyDataStore();
  
  ~MyDataStore();
  
  void addProduct(Product* p);
  
  void addUser(User* u) ;
  
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  
  void dump(std::ostream& ofile);

  
  void addCart(std::string user, Product* p);
  
  void viewCart(std::string user);
  
  void buyCart(std::string user);

  protected:
  std::map<std::string, User*> USER;
  std::vector<Product*> PRODUCT;
  std::map<std::string, std::vector<Product*>> CARTMAP;
  std::map<std::string, std::set<Product*>> KEYWORD;
  std::vector<Product*> hits;
  std::vector<User*> USERVECTOR;
};