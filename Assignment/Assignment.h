#ifndef Assignment_H
#define Assignment_H
#include <iostream>
using namespace std;

class Assignment{
private:
  string name;
  double pointsPossible;
  double pointsEarned;
  bool isEdited;
  bool isCompleted;
public:
  Assignment(string name, double pointsEarn, double pointsPoss);
  double getPointsPossible()const;
  double getPointsEarned()const;
  void setPointsEarned(double points);
  void markCompleted(bool isComplete);
  void markEdited(bool isEdit );
};







#endif