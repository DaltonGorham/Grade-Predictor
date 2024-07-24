#include "GradePredictor.h"
#include <fstream>
#include <string>
#include <vector>
#include<ios>
#include<limits> 
using namespace std;


/*If the line starts with "Category:", it indicates the start of a new category:
  If the current category has assignments, it is added to the vector.
  Extracts the category name and weight from the line.
  Initializes a new Category object with the extracted name and weight.
  If the line is an assignment line:
  Extracts the assignment details (number, name, points possible, points earned, and completion status).
*/
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

    int colon = line.find(':');

    int number = stoi(line.substr(0, colon));

    string assignmentName = line.substr(0, firstComma);

    double pointsPossible = stod(line.substr(firstComma + 1, secondComma - firstComma - 1 ));

    double pointsEarned = stod(line.substr(secondComma + 1, thirdComma - secondComma - 1));

    bool completed = (line.substr(thirdComma + 1) == "1");

    Assignment dummy;

    dummy.setName(assignmentName);
    dummy.setPointsEarned(pointsEarned);
    dummy.setPointsPossible(pointsPossible);
    dummy.markCompleted(completed);
    dummy.setAssignmentNumber(number);

    

    category.addAssignment(dummy);
  } 
  }

  if (category.getAssignments().size() != 0){
    categories.push_back(category);
  }

  gradeBook.close();
  return categories; //Returns Category objects with assignments.
}


void GradePredictor::printCategorySummary(vector<Category> &categories){

  
  for (Category& c : categories){
    c.calculateTotalCompleted();
    cout << "Category Name: " << c.getName() << endl;
    cout << "Category Weight: " << c.getWeight() << endl;
    cout << "Assignments Completed: " << c.getTotalCompleted() << endl;
    cout << "Current Grade: " << c.calculateCurrentGrade() << "%" << endl;
    cout << "---------------------" << endl << endl;
  }
}

void GradePredictor::printCategoryDetails(vector<Category>& categories, const string& name){
  clearScreen();
  cout << "User entered category name: [" << name << "]" << endl << endl;
  for (Category& c : categories){
      if (name == c.getName()){
      cout << "Assignments: " << endl;
      for (Assignment& assignment : c.getAssignments()){
      cout << assignment.getName(); printEdited(assignment);
      cout << "Points Possible: " << assignment.getPointsPossible() << endl;
      cout << "Points Earned: " << assignment.getPointsEarned() << endl;
      if (assignment.getCompleted()) cout << "Grade: " << assignment.getPointsEarned() / assignment.getPointsPossible() * 100.0 << "%" << endl; 
      else cout << "Grade: " << "N/a" << endl;
      cout << "Completed: " << (assignment.getCompleted() ? "Yes" : "No") << endl << endl; 
    }
    break;
      } 
    }
  }


string GradePredictor::getCategoryName(const vector<Category> & categories)const{
  string name;
  bool found = false;

  while(!found){
    
    cout << "Enter a category name to get a full report: ";
    getline(cin, name);

    for (const Category &c : categories){
      if (name == c.getName()){
        found = true;
        return name;
      }
    }
  if (!found){
    cout << "Category Not Found. Please Try Again." << endl;
  }
  

  }
  return "Something went wrong.";
}




bool GradePredictor:: askForEdit(){
  char answer;
  cout << "Do you wish to edit anything? (Y/N) ";
  cin >> answer;

  return (answer == 'y' || answer == 'Y');
}



void GradePredictor:: editAssignment(vector<Category>& categories){
  int number;
  string editToken;
  char answer;
  cout << "Enter the assignment number you wish to edit: ";
  cin >> number;
  cin.ignore();
  bool found = false;


  for (Category& c : categories){
    for ( Assignment& a : c.getAssignments()){
      if (number == a.getAssignmentNumber()){
        found = true;
        cout << "Now Editing Assignment: " << a.getName() << endl; 
        string newName;
        double newPointsPossible, newPointsEarned;
        bool newCompleted;

        do {
        cout << "What do you want to edit? Name, Points Possible, Points Earned, or Completed ";

        getline(cin,editToken);

        if (editToken == "Name"){
          cout << "Enter new name with assignment number and colon in front: ";
          getline(cin, newName);
          a.setName(newName);
          a.markEdited();
        }
        else if (editToken == "Points Possible"){
          cout << "Enter new Points Possible: ";
          cin >> newPointsPossible;
          a.setPointsPossible(newPointsPossible);
          cin.ignore();
          a.markEdited();
        }
        else if (editToken == "Points Earned"){
          cout << "Enter new Points Earned: ";
          cin >> newPointsEarned;
          a.setPointsEarned(newPointsEarned);
          cin.ignore();
          a.markEdited();
        }
        else if (editToken == "Completed"){
          cout << "Is this assignment Complete? (1 for Yes, 0 for No)";
          cin >> newCompleted;
          a.markCompleted(newCompleted);
          cin.ignore();
          a.markEdited();
        }
        else {
          cout << "No Assignment Edited.";
        }
        cout << "Are you done editing? (Y/N) ";
        cin >> answer;
        cin.ignore();
        } while (answer != 'y' && answer != 'Y');
        
        cout << "Assignment Succefully Edited" << endl;
        return;
      }
    }
    if (found) break;
     
  }
  if (!found){
    cout << "Assignment Number Not Valid." << endl;
  }


}


void GradePredictor::clearScreen(){
  cout << "\033[2J\033[H";
}

void GradePredictor::printEdited(Assignment& assignment){
 cout << "\t" << (assignment.getIfEdited() ? "**Edited**\n" : "\n");
}