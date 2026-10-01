
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include "product.h"
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, 
  const std::string size, const std::string brand) : 
  Product("clothing", name, price, qty), size_(size), brand_(brand){
}

std::set<std::string> Clothing::keywords() const{
  set <string> keyname = parseStringToWords(name_);
  set <string> keybrand = parseStringToWords(brand_);
  set <string> result = setUnion(keyname, keybrand);
  return result;
}

std::string Clothing::displayString() const{
  stringstream ss;
  ss << name_ <<endl;
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss<< price_ <<" " <<qty_ << " left.";

  return ss.str();
}

void Clothing::dump(std::ostream& os) const{
  Product::dump(os);
  os << size_ << endl << brand_ << endl;
}