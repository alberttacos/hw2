#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product
{
  public:
  Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);

  std::string displayString() const;
  std::set<std::string> keywords() const;
  void dump(std::ostream& os) const;

  private:
  std::string size_;
  std::string brand_;
};