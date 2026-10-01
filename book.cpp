
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include "product.h"
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string name, double price, int qty, 
  const std::string ISBN, const std::string Author) : 
  Product("book", name, price, qty), ISBN_(ISBN), Author_(Author){
  
}

std::set<std::string> Book::keywords() const{
  set <string> keyname = parseStringToWords(name_);
  set <string> keyauthor = parseStringToWords(Author_);
  set<string> result = setUnion(keyname, keyauthor);
  result.insert(ISBN_);
  return result;
}

std::string Book::displayString() const{
  stringstream ss;
  ss << name_ <<endl;
  ss << "Author: " << Author_ << " ISBN: " << ISBN_ << "\n";
  ss<< price_ <<" " <<qty_ << " left.";

  return ss.str();
}

void Book::dump(std::ostream& os) const{
  Product::dump(os);
  os << ISBN_ << endl << Author_ << endl;
}