#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


vector<string> semesterinput;
vector<string> subjectinput;
vector<string> professor_nameinput;
vector<string> creditinput;
vector<string> branchinput;


const int Total_Rooms = 23; 
const int Total_slots = 5;


vector<vector<vector<string> > > Course_Allocation(Total_Rooms, vector<vector<string> >(Total_slots, vector<string>(5, "0")));


bool Is_Prof_Avail(int timing, int day, string Prof, int room);
void Generate_Timetable();
void WriteTimetableToFile(const string& filename);
void Professor_TimeTable(const string& professorName);
void Semester_TimeTable();

int main() {
    string semester;
    cout << "Enter semester (winter/autumn): ";
    cin >> semester;
    
    string filename = (semester == "winter") ? "winter.txt" : "autumn.txt";
    ifstream input(filename);
    
    if (!input) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 1;
    }

    string perticularline;
    while (getline(input, perticularline)) {
        istringstream iss(perticularline);
        string sem, sub, pro_n, cre, br;
        if (getline(iss, sem, ',') && getline(iss, sub, ',') && getline(iss, pro_n, ',') && getline(iss, cre, ',') && getline(iss, br, ',')) {
            semesterinput.push_back(sem);
            subjectinput.push_back(sub);
            professor_nameinput.push_back(pro_n);
            creditinput.push_back(cre);
            branchinput.push_back(br);
        }
    }

    Generate_Timetable();

    WriteTimetableToFile("timetable.csv");
    cout << endl << "Time Table has been Saved" << endl << endl << endl;

    cout << "Do you want time table with respect to Professor? (YES/NO)" << endl;
    string yesno;
    cin >> yesno;
    cout << endl;
    
    if(yesno=="YES"){
        string proff_name;
        cout << "Enter the Professor code for whome you need Timetable." << endl;
        cin >> proff_name;
        Professor_TimeTable(proff_name);
        cout << endl;
        cout << "Time table for " << proff_name << " has been saved successfully" << endl;
    }
    Semester_TimeTable();
    return 0;
}

bool string_match(int branch_index,int k)
{
    vector<string>branch_index2;
    vector<string>curr_branch;
    curr_branch.push_back(branchinput[k]);
    branch_index2.push_back(branchinput[branch_index]);
    bool found = (curr_branch[0].find(branch_index2[0]) != string::npos);

    if (found) {
        return true;
    } else {
        bool found = (branch_index2[0].find(curr_branch[0]) != string::npos);
        if(found){
            return true;
        }
        else{
            return false;
        }
    }
}

bool Is_Prof_Avail(int timing, int day, string Prof, int room,int branch_index) { 
    vector<string> code; 
    //code is the vector that contains all course of the Professor which is passed as argument 
    for (int i = 0; i < professor_nameinput.size(); ++i) { 
        if (Prof == professor_nameinput[i]) { 
            code.push_back(subjectinput[i]); 
        } 
    } 
     //the loop below  checks if any course of given Professor is already alocated in this slot or not 
    if(timing<4) 
        { 
         if(timing>0) 
         { 
              for(int t=timing-1;t<=timing+1;++t) 
              { 
                for (int j = 0; j < code.size(); ++j) { 
                    for (int i = 0; i <= room; ++i) { 
                        if (Course_Allocation[i][t][day] == code[j]) { 
                            return false; 
                        } 
                    } 
                } 
              } 
         } 
         else 
         { 
             for(int t=timing;t<=timing+1;++t) 
              { 
                for (int j = 0; j < code.size(); ++j) { 
                    for (int i = 0; i <= room; ++i) { 
                        if (Course_Allocation[i][t][day] == code[j]) { 
                            return false; 
                        } 
                    } 
                } 
              } 
         } 
        } 
        else 
        { 
            for(int t=timing-1;t<=timing;++t) 
              { 
                for (int j = 0; j < code.size(); ++j) { 
                    for (int i = 0; i <= room; ++i) { 
                        if (Course_Allocation[i][t][day] == code[j]) { 
                            return false; 
                        } 
                    } 
                } 
              } 
        } 
    for(int i=0;i<room;++i)
   {
    for(int k=0;k<subjectinput.size();++k)
    {
        if(Course_Allocation[i][timing][day]==subjectinput[k])
        {
            if(((branchinput[k]==branchinput[branch_index])||(string_match(branch_index,k)))&&(semesterinput[k]==semesterinput[branch_index]))
            {
                return false;
            }
        }
    }
  }
    return true; 
}


void Generate_Timetable() {
    int course_index = 0;
    for (int i = 0; i < Total_Rooms; i++) {
        for (int j = 0; j < Total_slots; j++) {
            for (int k = 0; k < 5; k++) {
                if (course_index < subjectinput.size() && Is_Prof_Avail(j, k, professor_nameinput[course_index], i,course_index) && stoi(creditinput[course_index]) > 0) {
                    Course_Allocation[i][j][k] = subjectinput[course_index];
                    creditinput[course_index] = to_string(stoi(creditinput[course_index]) - 1); 
                    if(stoi(creditinput[course_index])==0)
                    course_index++; 
                }
            }
        }
    }
}


void Professor_TimeTable(const string& professorName) {
    string filename = professorName + "_timetable.csv";
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Write headers
    outfile << "Day,Time,Course,Semester,Branch,Room" << endl;
    for(int f = 0; f < professor_nameinput.size(); f++) {
        if(professor_nameinput[f] == professorName) {
            for (int i = 0; i < Total_Rooms; i++) {
                for (int j = 0; j < Total_slots; j++) {
                    for (int k = 0; k < 5; k++) {
                        if(subjectinput[f] == Course_Allocation[i][j][k]) {
                            if(k==0) outfile << "Monday" << ",";
                            else if(k==1) outfile << "Tuesday" << ",";
                            else if(k==2) outfile << "Wednesday" << ",";
                            else if(k==3) outfile << "Thursday" << ",";
                            else if(k==4) outfile << "Friday" << ",";

                            if(j==0) outfile << "8:00 AM - 9:00 AM" << ",";
                            else if(j==1) outfile << "9:00 AM - 10:00 AM" << ",";
                            else if(j==2) outfile << "10:00 AM - 11:00 AM" << ",";
                            else if(j==3) outfile << "11:00 AM - 12:00 PM" << ",";
                            else if(j==4) outfile << "12:00 PM - 1:00 PM" << ",";

                            outfile << subjectinput[f] << ",";
                            outfile << semesterinput[f] << ",";
                            outfile << branchinput[f] << ",";

                            if (i == 0) outfile << "LT1" << ",";
                            else if (i == 1) outfile << "LT2" << ",";
                            else if (i == 2) outfile << "LT3" << ",";
                            else if (i == 3) outfile << "CEP-003" << ",";
                            else if (i == 4) outfile << "CEP-102" << ",";
                            else if (i == 5) outfile << "CEP-103" << ",";
                            else if (i == 6) outfile << "CEP-104" << ",";
                            else if (i == 7) outfile << "CEP-105" << ",";
                            else if (i == 8) outfile << "CEP-106" << ",";
                            else if (i == 9) outfile << "CEP-107" << ",";
                            else if (i == 10) outfile << "CEP-108" << ",";
                            else if (i == 11) outfile << "CEP-109" << ",";
                            else if (i == 12) outfile << "CEP-110" << ",";
                            else if (i == 13) outfile << "CEP-202" << ",";
                            else if (i == 14) outfile << "CEP-203" << ",";
                            else if (i == 15) outfile << "CEP-204" << ",";
                            else if (i == 16) outfile << "CEP-205" << ",";
                            else if (i == 17) outfile << "CEP-206" << ",";
                            else if (i == 18) outfile << "CEP-207" << ",";
                            else if (i == 19) outfile << "CEP-209" << ",";
                            else if (i == 20) outfile << "CEP-210" << ",";
                            else if (i == 21) outfile << "CEP-211" << ",";
                            else if (i == 22) outfile << "CEP-212" << ",";

                            
                            outfile << endl;
                        }
                    }
                }
            }
        }
    }

    outfile.close();
}



void WriteTimetableToFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Write headers
    outfile << "Day,Time,Room,Course,Professor,Semester,Branch" << endl;

    vector<string> days;
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;
    times.push_back("8:00 AM - 9:00 AM");
    times.push_back("9:00 AM - 10:00 AM");
    times.push_back("10:00 AM - 11:00 AM");
    times.push_back("11:00 AM - 12:00 PM");
    times.push_back("12:00 PM - 1:00 PM");

    bool printedDays[5] = {false};
    bool printedTimes[5] = {false};


    for (int k = 0; k < 5; ++k) {
        string day = days[k];

        // Check if the day has been printed already
        if (!printedDays[k]) {
            bool dayPrinted = false;
            for (int j = 0; j < 5; ++j) {
                string time=times[j];
                bool timeprinted = false;

                bool slotPrinted = false;
                for (int i = 0; i < 23; ++i) {
                    if (Course_Allocation[i][j][k] != "0") {
                        if (!dayPrinted) {
                            outfile << day << ",";
                            dayPrinted = true;
                            printedDays[k] = true;
                        } else {
                            outfile << ",";
                        }
                        if(!timeprinted) {
                            outfile << time << ",";
                            timeprinted = true;
                            printedTimes[k] = true;
                        }
                        else{
                            outfile<< ",";
                        }

                        
                        if (i == 0) outfile << "LT1";
                        else if (i == 1) outfile << "LT2";
                        else if (i == 2) outfile << "LT3";
                        else if (i == 3) outfile << "CEP-003";
                        else if (i == 4) outfile << "CEP-102";
                            else if (i == 5) outfile << "CEP-103";
                            else if (i == 6) outfile << "CEP-104";
                            else if (i == 7) outfile << "CEP-105";
                            else if (i == 8) outfile << "CEP-106";
                            else if (i == 9) outfile << "CEP-107";
                            else if (i == 10) outfile << "CEP-108";
                            else if (i == 11) outfile << "CEP-109";
                            else if (i == 12) outfile << "CEP-110";
                            else if (i == 13) outfile << "CEP-202";
                            else if (i == 14) outfile << "CEP-203";
                            else if (i == 15) outfile << "CEP-204";
                            else if (i == 16) outfile << "CEP-205";
                            else if (i == 17) outfile << "CEP-206";
                            else if (i == 18) outfile << "CEP-207";
                            else if (i == 19) outfile << "CEP-209";
                            else if (i == 20) outfile << "CEP-210";
                            else if (i == 21) outfile << "CEP-211";
                            else if (i == 22) outfile << "CEP-212";
                        outfile << "," << Course_Allocation[i][j][k] << ",";

                        int courseIndex = -1;
                        for (int idx = 0; idx < subjectinput.size(); ++idx) {
                            if (Course_Allocation[i][j][k] == subjectinput[idx]) {
                                courseIndex = idx;
                                break;
                            }
                        }
                        if (courseIndex != -1) {
                            outfile << professor_nameinput[courseIndex] << ",";
                            outfile << semesterinput[courseIndex] << ",";
                            outfile << branchinput[courseIndex];
                        }
                        outfile << endl;
                        slotPrinted = true;
                    }
                }
                if (!slotPrinted && dayPrinted) {
                    outfile << "," << time << endl;
                }
            }
        }
    }

    outfile.close();
}



void Semester_TimeTable() {

    cout << endl << "Do you want Time Table according to semester? (YES/NO)" << endl;
    string yesno;
    cin >> yesno;
    string Semester;
    if(yesno=="YES"){
        cout << "Enter Semester Number.";
        cin >> Semester;
    }

    string filename = Semester + "_timetable.csv";
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    outfile << "Day,Time,Course,Professor,Branch,Room" << endl;

    vector<string> days;
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;
    times.push_back("8:00 AM - 9:00 AM");
    times.push_back("9:00 AM - 10:00 AM");
    times.push_back("10:00 AM - 11:00 AM");
    times.push_back("11:00 AM - 12:00 PM");
    times.push_back("12:00 PM - 1:00 PM");

    bool printedDays[5] = {false};
    bool printedTimes[5] = {false};

    for (int k = 0; k < 5; k++) {
        string day = days[k];

        if (!printedDays[k]) {
            bool dayPrinted = false;
            for (int j = 0; j < Total_slots; j++) {
                string time = times[j];
                bool timeprinted = false;
                bool slotPrinted = false;
                for (int i = 0; i < Total_Rooms; i++) { 
                    for (int f = 0; f < professor_nameinput.size(); f++) { 
                        if (semesterinput[f] == Semester && subjectinput[f] == Course_Allocation[i][j][k]) { 
                            if (!dayPrinted) {
                                outfile << day << ",";
                                dayPrinted = true;
                                printedDays[k] = true;
                            } else {
                                outfile << ",";
                            }
                            if (!timeprinted) {
                                outfile << time << ",";
                                timeprinted = true;
                                printedTimes[k] = true;
                            } else {
                                outfile << ",";
                            }

                            outfile << subjectinput[f] << ",";
                            outfile << professor_nameinput[f] << ",";
                            outfile << branchinput[f] << ",";
                            if (i == 0) outfile << "LT1" << ",";
                            else if (i == 1) outfile << "LT2" << ",";
                            else if (i == 2) outfile << "LT3" << ",";
                            else if (i == 3) outfile << "CEP-003" << ",";
                            else if (i == 4) outfile << "CEP-102" << ",";
                            else if (i == 5) outfile << "CEP-103" << ",";
                            else if (i == 6) outfile << "CEP-104" << ",";
                            else if (i == 7) outfile << "CEP-105" << ",";
                            else if (i == 8) outfile << "CEP-106" << ",";
                            else if (i == 9) outfile << "CEP-107" << ",";
                            else if (i == 10) outfile << "CEP-108" << ",";
                            else if (i == 11) outfile << "CEP-109" << ",";
                            else if (i == 12) outfile << "CEP-110" << ",";
                            else if (i == 13) outfile << "CEP-202" << ",";
                            else if (i == 14) outfile << "CEP-203" << ",";
                            else if (i == 15) outfile << "CEP-204" << ",";
                            else if (i == 16) outfile << "CEP-205" << ",";
                            else if (i == 17) outfile << "CEP-206" << ",";
                            else if (i == 18) outfile << "CEP-207" << ",";
                            else if (i == 19) outfile << "CEP-209" << ",";
                            else if (i == 20) outfile << "CEP-210" << ",";
                            else if (i == 21) outfile << "CEP-211" << ",";
                            else if (i == 22) outfile << "CEP-212" << ",";
                            outfile << endl;
                        }
                    }
                }
            }
        }
    }

    outfile.close();
}
