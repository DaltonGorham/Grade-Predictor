#include "Assignment.h"
using namespace std;


Assignment::Assignment(string n, double pointsEarn, double pointsPoss)
: name(n), pointsEarned(pointsEarn), pointsPossible(pointsPoss)
{

}

void Assignment::setPointsEarned(double points){
  pointsEarned = points;
}

double Assignment::getPointsEarned()const{
  return pointsEarned;
}

double Assignment::getPointsPossible()const{
  return pointsPossible;
}

void Assignment::markCompleted(bool isComplete){
  isCompleted = isComplete;
}

void Assignment::markEdited(bool isEdit){
  isEdited = isEdit;
}