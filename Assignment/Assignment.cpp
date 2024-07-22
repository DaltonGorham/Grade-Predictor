#include "Assignment.h"
using namespace std;


Assignment::Assignment()
{

}

Assignment::Assignment(string n, double pointsEarn, double pointsPoss)
: name(n), pointsEarned(pointsEarn), pointsPossible(pointsPoss), isCompleted(false), isEdited(false)
{

}

void Assignment::setName(const string n){
  name = n;
}


string Assignment::getName()const {
    return name;
}

void Assignment::setPointsEarned(double points){
  pointsEarned = points;
}

double Assignment::getPointsEarned()const{
  return pointsEarned;
}


void Assignment::setPointsPossible(double points){
  pointsPossible = points;
}

double Assignment::getPointsPossible()const{
  return pointsPossible;
}

void Assignment::markCompleted(bool complete){
  isCompleted = complete;
}

bool Assignment::getCompleted()const{
  return isCompleted;
}

void Assignment::markEdited(){
  isEdited = true;
}