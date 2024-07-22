#include "GradePredictor.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;



vector<Category> GradePredictor::readFromFile(const string filename){
  ifstream gradeBook(filename);

  if(!gradeBook){
    cout << "Error Opening Source File";
  }
  vector<Category> categories;
  string line;

  Category category;

  while (getline(gradeBook, line)){
    int firstComma = line.find(',');

    if (line.substr(0, 9) == "Category:"){
      if (category.getAssignments().size() != 0){
      categories.push_back(category);
      }
    

    string categoryName = line.substr(10, firstComma - 10);
    double categoryWeight = stod(line.substr(firstComma + 1));

    category = Category(categoryName, categoryWeight);
    }
   else{
    int secondComma = line.find(',', firstComma + 1);
    int thirdComma = line.find(',', secondComma + 1);

    string name = line.substr(0, firstComma);

    double pointsPossible = stod(line.substr(firstComma + 1, secondComma - firstComma - 1 ));

    double pointsEarned = stod(line.substr(secondComma + 1, thirdComma - secondComma - 1));

    bool completed = (line.substr(thirdComma + 1) == "1");

    Assignment dummy;

    dummy.setName(name);
    dummy.setPointsEarned(pointsEarned);
    dummy.setPointsPossible(pointsPossible);
    dummy.markCompleted(completed);

    

    category.addAssignment(dummy);
  } 
  }

  if (category.getAssignments().size() != 0){
    categories.push_back(category);
  }

  gradeBook.close();
  return categories;
}


void GradePredictor::printCategory(const vector<Category> &categories){

  
  for (Category c : categories){
    c.calculateTotalCompleted();
    cout << "Category Name: " << c.getName() << endl;
    cout << "Category Weight: " << c.getWeight() << endl;
    cout << "Assignments Completed: " << c.getTotalCompleted() << endl;
    cout << "Current Grade: " << c.calculateCurrentGrade() << "%" << endl;

      cout << endl << "Assignments: " << endl ;

    for (Assignment assignment : c.getAssignments()){
      cout << assignment.getName() << endl;
      cout << "Points Possible: " << assignment.getPointsPossible() << endl;
      cout << "Points Earned: " << assignment.getPointsEarned() << endl;
      if (assignment.getCompleted()) cout << "Grade: " << assignment.getPointsEarned() / assignment.getPointsPossible() * 100.0 << "%" << endl; 
      else cout << "Grade: " << "N/a" << endl;
      cout << "Completed: " << (assignment.getCompleted() ? "Yes" : "No") << endl << endl; 
    }
    cout << "---------------------" << endl << endl;
  }
}