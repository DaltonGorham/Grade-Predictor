#ifndef GradePredictor_H
#define GradePredictor_H
#include "../Assignment/Assignment.h"
#include "../Category/Category.h"
#include <iostream>
#include <vector>


class GradePredictor{
private:
public:
  std::vector<Category> readFromFile(const string filename);
  void printCategory(const vector<Category> &categories);
};






#endif