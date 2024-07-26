#include "GradePredictor.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;


/*
  Reads in lines from a file called gradeBook: 
  If the line starts with "Category:", it indicates the start of a new category:
  If the current category has assignments, it is added to the vector.
  Extracts the category name and weight from the line in file.
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
  // If the first 9 characters are Category:
    if (line.substr(0, 9) == "Category:"){
      if (category.getAssignments().size() != 0){
      categories.push_back(category);
      }
    
    //Gets the name by going to the fist character after category:
    //and getting the length by subtracting 10 to the first comma.
    string categoryName = line.substr(10, firstComma - 10);
    double categoryWeight = stod(line.substr(firstComma + 1));

    category = Category(categoryName, categoryWeight);
    }
    //Else the the line does not start with Category: thus it is an assignment line
   else{
    int secondComma = line.find(',', firstComma + 1);
    int thirdComma = line.find(',', secondComma + 1);

    int colon = line.find(':');

    int number = stoi(line.substr(0, colon));

    string assignmentName = line.substr(0, firstComma);

    double pointsPossible = stod(line.substr(firstComma + 1, secondComma - firstComma - 1 ));

    double pointsEarned = stod(line.substr(secondComma + 1, thirdComma - secondComma - 1));

    bool completed = (line.substr(thirdComma + 1) == "1");

    //Creates an assignment object to gather data for each category.

    Assignment dummy;

    dummy.setName(assignmentName);
    dummy.setPointsEarned(pointsEarned);
    dummy.setPointsPossible(pointsPossible);
    dummy.markCompleted(completed);
    dummy.setAssignmentNumber(number);

    
    category.addAssignment(dummy);
  } 
  }
  //Pushes the new category object inside the vector of categories.
  if (category.getAssignments().size() != 0){
    categories.push_back(category);
  }

  gradeBook.close();
  return categories; //Returns Category objects with assignments.
}


/*
Displays a summary of each category within the categories vector. 
*/

void GradePredictor::printCategorySummary(vector<Category> &categories){
  
  for (Category& c : categories){
    c.calculateTotalCompleted();
    c.calculateTotalNotCompleted();
    cout << "Category Name: " << c.getName() << endl;
    cout << "Category Weight: " << c.getWeight() << endl;
    cout << "Assignments Completed: " << c.getTotalCompleted() << endl;
    cout << "Assignments Remaining: " << c.getTotalNotCompleted() << endl;
    cout << "Predicted Grade on Remaining Assignments: ";
    if (predictGradeAverage(c) != 0.0){
      cout << predictGradeAverage(c) << endl;
    }
    else cout << "N/a" << endl;
    cout << "Current Grade: " << c.calculateCurrentGrade() << "%" << endl;
    cout << "-------------------------" << endl << endl << endl;
  }
}

/*
Displays all of the assignments and their details. If a certain assignment has been edited within the category it will display a **edited** message beside the assignment name. 
*/

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
      else cout << "Grade: " << "N/a" <<  endl;
      cout << "Completed: " << (assignment.getCompleted() ? "Yes" : "No") << endl << endl; 
    }
    break;
      } 
    }
  }

/*
Gets the name of the category the user wants to get a full report on.
*/
string GradePredictor::getCategoryName(const vector<Category> & categories)const{
  string name;
  bool found = false;

  while(!found){
    
    cout << "Enter a category name to get a full report or edit an assignment: ";
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

/*
Asks the user for the assignment number of the assignment they want to edit. If that number is an assignment number within that category it will then enter edit mode and begin asking what they want to edit, until they choose to quit. 
*/

void GradePredictor:: editAssignment(vector<Category>& categories){
  int number;
  string editToken;
  char answer;
  cout << "Enter the assignment number you wish to edit, or 0 to quit: ";
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
        cout << "What do you want to edit? Name, Points Possible, Points Earned, or Completed: " << endl;

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
          cout << "Invalid Choice. No Assignment Edited.";
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
  if (!found ){
    cout << "Exiting Assignments..." << endl;
  }


}


void GradePredictor::clearScreen(){
  cout << "\033[2J\033[H";
}

void GradePredictor::printEdited(Assignment& assignment){
 cout << "\t" << (assignment.getIfEdited() ? "**Edited**\n" : "\n");
}



double GradePredictor::calculateOverallGrade(vector<Category>& categories){
  double totalWeightedGrade = 0.0;
  double totalWeight = 0.0;

  for (Category& c : categories){
    double categoryWeight = c.getWeight();
    double currentGrade = c.calculateCurrentGrade();

    totalWeight += categoryWeight;
    totalWeightedGrade += (currentGrade / 100) * categoryWeight;

    if (totalWeight == 0){
      return 0.0;
    }

    
  }
  return (totalWeightedGrade / totalWeight) * 100;
}


/*
Returns the predicted grade for any assignments that are not completed.
The grade is the average grade for all the completed assignments.
 If all assignments are completed it will return 0.0.
*/

double GradePredictor::predictGradeAverage(Category& c){

  int remaingPointsPossible = 0;
  double currentAverage = c.calculateCurrentGrade();

  for (Assignment& a : c.getAssignments()){
    if (!a.getCompleted()){
      remaingPointsPossible += a.getPointsPossible();
    }
  }

  double predictedGrade = 0.0;

  if (remaingPointsPossible > 0){
    predictedGrade = currentAverage;
  }

  return predictedGrade;
}



