#ifndef Assignment_H
#define Assignment_H
#include <iostream>
using namespace std;

class Assignment{
private:
  string name;
  double pointsPossible;
  double pointsEarned;
  bool isEdited = false;
  bool isCompleted = false;
public:
  Assignment();
  Assignment(string name, double pointsEarn, double pointsPoss);
  double getPointsPossible()const;
  double getPointsEarned()const;
  void setName(const string n);
  void setPointsEarned(double points);
  void setPointsPossible(double points);
  void markCompleted(bool complete);
  bool getCompleted()const;
  void markEdited();
  string getName()const;
};


#endif