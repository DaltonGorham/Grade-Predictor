#include "Category.h"
#include <iomanip>
#include <vector>
using namespace std;



Category::Category(){}

Category::Category(string n, double w) : name(n), weight(w), totalCompleted(0) {}



void Category::setName(string n){ name = n; }

void Category::setWeight(double w){ weight = w; }

string Category::getName() const {
    return name;
}

double Category::getWeight() const {
    return weight;
}

vector<Assignment> Category::getAssignments()const{
  return assignments;
}

void Category::addAssignment(Assignment assignment){
  assignments.push_back(assignment);
}

int Category::getTotalCompleted(){
  return totalCompleted;
}


void Category::calculateTotalCompleted(){
  totalCompleted = 0;
  const vector<Assignment> &assignments = getAssignments();

  for (const Assignment& a : assignments){
    if (a.getCompleted()){
      totalCompleted++;
    }
  }
}


double Category::calculateCurrentGrade()const {
  double totalPointsPossible = 0;
  double totalPointsEarned = 0;
  cout << fixed << showpoint << setprecision(2);

  for (const Assignment& a : getAssignments()) {
      if (a.getCompleted()) {
          totalPointsPossible += a.getPointsPossible();
          totalPointsEarned += a.getPointsEarned();
      }
  }

  if (totalPointsPossible == 0) {
      return 0.0;
  }

  return (totalPointsEarned / totalPointsPossible) * 100.0;
}