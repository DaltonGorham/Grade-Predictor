#ifndef Assignment_H
#define Assignment_H
#include <iostream>
using namespace std;

class Assignment{
private:
  string name;
  double pointsPossible;
  double pointsEarned;
  int assignmentNumber;
  bool isEdited = false;
  bool isCompleted = false;
public:
  Assignment();
  Assignment(string name, double pointsEarn, double pointsPoss, int num);
  double getPointsPossible()const;
  double getPointsEarned()const;
  void setName(const string n);
  void setAssignmentNumber(int num);
  void setPointsEarned(double points);
  void setPointsPossible(double points);
  void markCompleted(bool complete);
  bool getCompleted()const;
  int getAssignmentNumber() const;
  void markEdited();
  bool getIfEdited()const;
  string getName()const;
  
};


#endif