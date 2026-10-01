
#ifndef MYDATA_H
#define MYDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "datastore.h"


class MyDataStore : public DataStore{
    public:
    /**
     * Adds a product to my data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void addCart(std::string username, Product* p);

    void viewCart(std::string username);

    void buyCart(std::string username);

     ~MyDataStore();
    
    private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif