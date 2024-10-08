#ifndef Category_H
#define Category_H
#include "../Assignment/Assignment.h"
#include <vector>


class Category{
private: 
  string name;
  double weight;
  vector<Assignment> assignments;
  int totalCompleted;
  int totalNotCompleted;
  double totalPointsPossible = 0;
  double totalPointsEarned = 0;
public:
  Category();
  Category(string n, double weight);
  void setName(string n);
  void setWeight(double d);
  void addAssignment(Assignment assignment);
  string getName()const;
  double getWeight()const;
  vector<Assignment>& getAssignments();
  int getTotalCompleted()const;
  int getTotalNotCompleted()const;
  void calculateTotalNotCompleted();
  void calculateTotalCompleted();
  double calculateCurrentGrade();
};







#endif