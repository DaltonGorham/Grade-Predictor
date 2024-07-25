#ifndef GradePredictor_H
#define GradePredictor_H
#include "../Assignment/Assignment.h"
#include "../Category/Category.h"
#include <iostream>
#include <vector>


class GradePredictor{
private:
  int assignmentNumber;
public:
  std::vector<Category> readFromFile(const string filename);
  void printCategorySummary(vector<Category> &categories);
  void printCategoryDetails(vector<Category>& categories, const string& name);
  string getCategoryName(const vector<Category> & categories)const;
  void editAssignment(vector<Category> & categories);
  void clearScreen();
  void printEdited(Assignment& assignment);
  double calculateOverallGrade(vector<Category>& categories);
  double predictGradeAverage(Category& c);
  
};






#endif