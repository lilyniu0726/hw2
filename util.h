#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  typename std::set<T>::iterator it1 = s1.begin();
  typename std::set<T>::iterator it2 = s2.begin();
  std::set<T> intersected;
  while(it1 != s1.end() && it2 != s2.end()){
    if(*it1 > *it2){
      ++it2;
    }
    else if(*it1 < *it2){
      ++it1;
    }
    else{
      intersected.insert(*it1);
      ++it1;
      ++it2;
    }
  }
  return intersected;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  typename std::set<T>::iterator it1 = s1.begin();
  typename std::set<T>::iterator it2 = s2.begin();
  std::set<T> uni;
  while(it1 != s1.end() || it2 != s2.end()){
    if(it1 != s1.end() && it2 != s2.end()){
      if(*it1 < *it2){
        uni.insert(*it1);
        ++it1;
      }
      else if(*it2 < *it1){
        uni.insert(*it2);
        ++it2;
      }

      else{
        uni.insert(*it1);
        ++it1;
        ++it2;
      }
    }
    else if(it1 == s1.end()){
        uni.insert(*it2);
        ++it2;
      }
    
    else if(it2 == s2.end()){
        uni.insert(*it1);
        ++it1;
      }
    }
  return uni;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
