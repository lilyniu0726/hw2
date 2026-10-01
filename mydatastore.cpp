#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "mydatastore.h"
#include "util.h"

using namespace std;

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);

  set<string> keys = p->keywords();

  for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it){
    keywordMap_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  users_[u->getName()] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  vector<Product*> results;
  set<Product*> resultSet;

  if(terms.size() == 0){
    return results;
  }

  if(type == 0){
    map<string, set<Product*> >::iterator it = keywordMap_.find(terms[0]);

    if(it == keywordMap_.end()){
      return results;
    }

    resultSet = it->second;

    for(size_t i = 1; i < terms.size(); i++){
      it = keywordMap_.find(terms[i]);

      if(it == keywordMap_.end()){
        resultSet.clear();
        break;
      }

      resultSet = setIntersection(resultSet, it->second);
    }
  }
  else{
    for(size_t i = 0; i < terms.size(); i++){
      map<string, set<Product*> >::iterator it = keywordMap_.find(terms[i]);

      if(it != keywordMap_.end()){
        resultSet = setUnion(resultSet, it->second);
      }
    }
  }

  for(set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it){
    results.push_back(*it);
  }

  return results;
}

void MyDataStore::dump(ostream& ofile){
  ofile << "<products>" << endl;

  for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    (*it)->dump(ofile);
  }

  ofile << "</products>" << endl;
  ofile << "<users>" << endl;

  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    it->second->dump(ofile);
  }

  ofile << "</users>" << endl;
}

void MyDataStore::addCart(std::string username, Product* p){
  if(users_.find(username)==users_.end()){
    cout <<"Invalid request" <<endl;
    return;
  }
  carts_[username].push_back(p);
}

void MyDataStore::viewCart(std::string username){
  if(users_.find(username)==users_.end()){
    cout <<"Invalid username" <<endl;
    return;
  }
  map<string, vector<Product*> >::iterator cartIt = carts_.find(username);
  if(cartIt == carts_.end()){
    return;
  }

  for(size_t i = 0; i < cartIt->second.size(); ++i){
    cout << "Item " << i+1 << endl;
    cout << cartIt->second[i]->displayString() << endl;
  }
}
    

void MyDataStore::buyCart(std::string username){
  map<string, User*>::iterator userIt = users_.find(username);

  if(userIt == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }

  User* user = userIt->second;
  map<string, vector<Product*> >::iterator cartIt = carts_.find(username);

  if(cartIt == carts_.end()){
    return;
  }

  vector<Product*> newCart;

  for(vector<Product*>::iterator it = cartIt->second.begin(); it != cartIt->second.end(); ++it){
    Product* p = *it;
    if(p->getQty() > 0 && user->getBalance() >= p->getPrice()){
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    }
    else{
      newCart.push_back(p);
    }
  }
  carts_[username] = newCart;
}


MyDataStore::~MyDataStore(){
  for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    delete *it;
  }

  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    delete it->second;
  }
}