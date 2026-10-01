
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include "product.h"
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty, 
  const std::string genre, const std::string rating) : 
  Product("movie", name, price, qty), genre_(genre), rating_(rating){
}

std::set<std::string> Movie::keywords() const{
  set <string> keyname = parseStringToWords(name_);
  keyname.insert(convToLower(genre_));
  return keyname;
}

std::string Movie::displayString() const{
  stringstream ss;
  ss << name_ <<endl;
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss<< price_ <<" " <<qty_ << " left.";

  return ss.str();
}

void Movie::dump(std::ostream& os) const{
  Product::dump(os);
  os << genre_ << endl << rating_ << endl;
}