#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm> 

using namespace std;
struct GolfCourse {
    string courseName;
    double courseRating;
    int slopeRating;
};


double calculateHandicap(double score, double courseRating, int slope) {
    return (score - courseRating) * 113.0 / slope;
}


double calculateOverallHandicap(const vector<double>& handicaps) {
    if (handicaps.empty()) return 0.0;
    
    int roundsToUse = min((int)handicaps.size(), 10); 
    vector<double> sortedHandicaps = handicaps;     
    sort(sortedHandicaps.begin(), sortedHandicaps.end()); 
    
    double total = 0.0;
    for (int i = 0; i < roundsToUse; ++i) {
        total += sortedHandicaps[i]; 
    }
    return total / roundsToUse; 
}

int main() {
    
    vector<GolfCourse> courses = {
        {"Gainesville Golf & Country Club", 71.5, 130},
        {"Ironwood Golf Course", 72.0, 128},
        {"The Haile Plantation Golf & Country Club", 73.2, 135},
        {"West End Golf Club", 70.8, 125}
    };

    
    map<string, int> courseMap;
    for (int i = 0; i < courses.size(); ++i) {
        courseMap[courses[i].courseName] = i;
    }

    cout << "Welcome to Jacobo's Gainesville Handicap Calculator." << endl;

    vector<double> handicaps; 
    char continueInput = 'y';

    do {
        
        double golferScore;
        cout << "Enter your golf score: ";
        cin >> golferScore;

      
        cout << "Select a golf course from the following options: \n";
        for (int i = 0; i < courses.size(); ++i) {
            cout << i + 1 << ". " << courses[i].courseName << endl;
        }

        cout << "Enter the number of the course you played: ";
        int courseChoice;
        cin >> courseChoice;

        if (courseChoice < 1 || courseChoice > courses.size()) {
            cout << "Invalid course choice. Try again.\n";
            continue;
        }

        string selectedCourse = courses[courseChoice - 1].courseName;
        cout << "You selected: " << selectedCourse << endl;

       
        int teeSelection; 
        cout << "Select your tee (1 = White Tees, 2 = Blue Tees, 3 = Red Tees): ";
        cin >> teeSelection;

        if (teeSelection < 1 || teeSelection > 3) {
            cout << "Invalid tee selection. Try again.\n";
            continue;
        }

        double adjustedCourseRating = courses[courseChoice - 1].courseRating;
        if (teeSelection == 2) {
            adjustedCourseRating += 1.0;
        } else if (teeSelection == 3) {
            adjustedCourseRating -= 1.0;
        }

        int courseSlope = courses[courseChoice - 1].slopeRating;

        
        double handicap = calculateHandicap(golferScore, adjustedCourseRating, courseSlope);
        handicaps.push_back(handicap);

        cout << "Your handicap for this round is: " << handicap << endl;

       
        cout << "Do you want to enter another round? (y/n): ";
        cin >> continueInput;

    } while (continueInput == 'y' || continueInput == 'Y');

   
    double overallHandicap = calculateOverallHandicap(handicaps);
    cout << "Your overall handicap based on the entered rounds is: " << overallHandicap << endl;

    return 0;
}
