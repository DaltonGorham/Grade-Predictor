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
  vector<Assignment> getAssignments()const;
  int getTotalCompleted();
  void calculateTotalCompleted();
  double calculateCurrentGrade()const;



};







#endif