#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;


vector<string> semesterinput;
vector<string> subjectinput;
vector<string> professor_nameinput;
vector<string> creditinput;
vector<string> branchinput;
unordered_map<string,string> shortToFullName;
unordered_map<string,string> branch;


const int Total_Rooms = 23; 
const int Total_slots = 5;


vector<vector<vector<string> > > Course_Allocation(Total_Rooms, vector<vector<string> >(Total_slots, vector<string>(5, "0")));


bool Is_Prof_Avail(int timing, int day, string Prof, int room);
void Generate_Timetable();
void WriteTimetableToFile(const string& filename);
void Professor_TimeTable(const string& professorName);
void Semester_TimeTable(const string& Semester);

int main() {

    branch["ICT"] = "B.Tech ICT";
    branch["CS"] = "B.Tech ICT+CS";
    branch["CSEVD"] = "B.Tech ICT+CS; EVD";
    branch["CSEVDCSMNC"] = "B.Tech ICT+CS; MNC; EVD";
    branch["EVD"] = "B.Tech EVD";
    branch["MNC"] = "B.Tech MnC";
    branch["CSMNC"] = "B.Tech ICT+CS; MnC";
    branch["MICT"] = "M.Tech ICT";
    branch["MEC"] = "M.Tech EC";
    branch["MSCIT"] = "M.Sc IT";
    branch["MSCDS"] = "M.Sc DS";
    branch["MSCAA"] = "M.Sc AA";
    branch["MDES"] = "M.Des CD";


    shortToFullName["AJ"] = "Abhishek Jindal";
    shortToFullName["AKM"] = "Amit Mankodi";
    shortToFullName["AG"] = "Anjan Ghosh";
    shortToFullName["AR"] = "Arnab Ray";
    shortToFullName["AT"] = "Aditya Tatu";
    shortToFullName["AKR"] = "Anil K Roy";
    shortToFullName["AT2"] = "Anuj Tawari";
    shortToFullName["AMM"] = "Anish Mathuria";
    shortToFullName["AR2"] = "Arpit Rana";
    shortToFullName["BD"] = "Binita Desai";
    shortToFullName["BK"] = "Bharani Kollipara";
    shortToFullName["BC"] = "Bhaskar Chaudhury";
    shortToFullName["BG"] = "Bakul Gohel";
    shortToFullName["BM"] = "Biswajit Mishra";
    shortToFullName["DKG"] = "Deepak K Ghodgaonkar";
    shortToFullName["GD"] = "Gautam Dutta";
    shortToFullName["GP"] = "Gopinath Panda";
    shortToFullName["GV"] = "Gaurav Vaidya";
    shortToFullName["HP"] = "Hemn Patil";
    shortToFullName["JP"] = "JayPrakash";
    shortToFullName["JM"] = "Jaydeep Mulherkar";
    shortToFullName["JJ"] = "Jensen Joseph";
    shortToFullName["PKS"] = "Kalyan Sasidhar";
    shortToFullName["LS"] = "Lavneet Singh";
    shortToFullName["MB"] = "Minal Bhise";
    shortToFullName["MK"] = "Manish Khare";
    shortToFullName["MK2"] = "Manish Kumar";
    shortToFullName["MM"] = "Madhumita Mazumdar";
    shortToFullName["MS"] = "Madhukant Sharma";
    shortToFullName["MT"] = "Mukesh Tiwari";
    shortToFullName["MKG"] = "Manish K Gupta";
    shortToFullName["MKR"] = "Manoj K Raut";
    shortToFullName["MLD"] = "Manik Lal Das";
    shortToFullName["MVJ"] = "Manjunath V Joshi";
    shortToFullName["NKS"] = "Nabin K Sahu";
    shortToFullName["PM"] = "Prasenjit Majumder";
    shortToFullName["PMJ"] = "Pokhar M Jat";
    shortToFullName["PA"] = "Pritam Anand";
    shortToFullName["PB"] = "Puneet Bhateja";
    shortToFullName["PK"] = "Pankaj Kumar";
    shortToFullName["PK2"] = "Prosenjit Kundu";
    shortToFullName["RG"] = "Ranendu Ghosh";
    shortToFullName["RLD"] = "Rajib L Das";
    shortToFullName["RM"] = "Rahul Muthu";
    shortToFullName["RC"] = "Rachit Chhaya";
    shortToFullName["RM2"] = "Rahul Mishra";
    shortToFullName["RP"] = "Rutu Parekh";
    shortToFullName["SDG"] = "Sourish Dasgupta";
    shortToFullName["SR"] = "Sreeja Rajendran";
    shortToFullName["SS"] = "S Srivastava";
    shortToFullName["SJ"] = "Shefali Jha";
    shortToFullName["SRG"] = "Shweta R Garg";
    shortToFullName["SB"] = "Shruti Bhilare";
    shortToFullName["SM"] = "Srimanta Mandal";
    shortToFullName["SB2"] = "Sudip Bera";
    shortToFullName["SK"] = "Sujay Kadam";
    shortToFullName["SP"] = "Supantha Pandit";
    shortToFullName["ST"] = "Saurabh Tiwari";
    shortToFullName["TKM"] = "Tapas K Maity";
    shortToFullName["VP"] = "Vishvajit Pandya";
    shortToFullName["VS"] = "V Sunitha";
    shortToFullName["VSP"] = "Vinay S Palaparthy";
    shortToFullName["YA"] = "Yash Agrawal";
    shortToFullName["YV"] = "Yash Vasavada";
    shortToFullName["NDJ"] = "Naresh D Jotwani";
    shortToFullName["TB"] = "gata Bandyopadhyay";
    shortToFullName["DNC"] = "Dipankar Nag Chaudhury";
    shortToFullName["GKS"] = "Gaurav Kumar Singh";
    shortToFullName["CJ"] = "Cyril Jos";
    shortToFullName["AM"] = "Amishal Modi";
    shortToFullName["NIKITADESAI"] = "Nikita Desai";
    shortToFullName["ANIRBANDUTTAGUPTA"] = "Anirban Duttagupta";
    shortToFullName["KUNTALADASGUPTA"] =  "Kuntala Dasgupta";
    shortToFullName["SANDIP MODHA"] = "Sandip Modha";
    shortToFullName["NANDINISAHA"] = "Nandini Saha";
    shortToFullName["MAYANKLOONKAR"] = "Mayank Loonkar";
    shortToFullName["PROSENJITGANGULY"] = "Prosenjit Ganguly";
    shortToFullName["RUDRANILDAS"] = "Rudranil Das";

    
    string semester;
    label:

    cout << "Enter semester (winter/autumn): ";
    cin >> semester;

    string filename;
    if(semester == "winter"){
        filename = "winter.txt";
    }
    else if(semester == "autumn"){
        filename = "autumn.txt";
    }
    else{
        cout << endl << "Please Enter valid Input. Try again." << endl << endl;
        goto label;
    }

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
    cout << endl << "Do you want Time Table according to semester? (YES/NO)" << endl;
    string yn;
    cin >> yn;
    string Semester;
    if(yn=="YES"){
        cout << "Enter Semester Number.";
        cin >> Semester;
        Semester_TimeTable(Semester);
        cout << endl;
        cout << "Time table for " << Semester << " semester has been saved successfully" << endl;
    }
    return 0;
}

bool string_match(int branch_index,int k)
{
    vector<string>branch_index2;
    vector<string>curr_branch;
    curr_branch.push_back(branchinput[k]);
    branch_index2.push_back(branchinput[branch_index]);
    if(curr_branch[0][0]=='M'&&branch_index2[0][0]!='M')
    {
        return false;
    }
    if(curr_branch[0][0]!='M'&&branch_index2[0][0]=='M')
    {
        return false;
    }
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
    int course_index = 0;  // Initialize the index to keep track of the current course being allocated.

    while(course_index < subjectinput.size())  // Loop until all courses are allocated.
        {
           for (int i = 0; i < Total_Rooms; i++) {  // Loop through each room.
               for (int j = 0; j < Total_slots; j++) {  // Loop through each time slot.
                   for (int k = 0; k < 5; k++) {       // Loop through each day of the week.
                       /*Check it the current slot in the current room on the current day is available, the professor is free to teach the course, and the course still has credit left.*/
                       if (Course_Allocation[i][j][k]=="0" && course_index < subjectinput.size() && Is_Prof_Avail(j, k, professor_nameinput[course_index], i,course_index) && stoi(creditinput[course_index]) > 0) {
                           Course_Allocation[i][j][k] = subjectinput[course_index];   // Allocate the course to the current slot.
                           creditinput[course_index] = to_string(stoi(creditinput[course_index]) - 1); //Decrease the credit by one.
                           if(stoi(creditinput[course_index])==0)   // If the course has no remaining credits, move to the next course.
                           course_index++; 
                      }
                   }
               }
           }
       }
  }


void Professor_TimeTable(const string& professorName) {
    string filename = shortToFullName[professorName] + "_timetable.csv";
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
                            outfile << branch[branchinput[f]] << ",";

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
    ofstream outfile(filename);  // Open the output file stream for writing the timetable.
    if (!outfile) {              // Check if the file stream is successfully opened.
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Write headers for the timetable csv file.
    outfile << "Day,Time,Room,Course,Professor,Semester,Branch" << endl;

    vector<string> days;        // Define vectors for days of the week.
    days.push_back("Monday");
    days.push_back("Tuesday");
    days.push_back("Wednesday");
    days.push_back("Thursday");
    days.push_back("Friday");

    vector<string> times;       // Define vectors for time slots.
    times.push_back("8:00 AM - 9:00 AM");
    times.push_back("9:00 AM - 10:00 AM");
    times.push_back("10:00 AM - 11:00 AM");
    times.push_back("11:00 AM - 12:00 PM");
    times.push_back("12:00 PM - 1:00 PM");

    // Arrays to keep track of whether each day and time slot has been printed.
    bool printedDays[5] = {false};
    bool printedTimes[5] = {false};


    for (int k = 0; k < 5; ++k) {      // Loop through each day of the week.
        string day = days[k];

        // Check if the day has been printed already
        if (!printedDays[k]) {
            bool dayPrinted = false;
            for (int j = 0; j < 5; ++j) {      // Loop through each time slot.
                string time=times[j];
                bool timeprinted = false;

                bool slotPrinted = false;
                for (int i = 0; i < 23; ++i) {        // Loop through each room.
                    if (Course_Allocation[i][j][k] != "0") {        // Check if a course is allocated in the current room, time slot, and day.

                        // Print day if it's not already printed.
                        if (!dayPrinted) {
                            outfile << day << ",";
                            dayPrinted = true;
                            printedDays[k] = true;
                        } else {
                            outfile << ",";
                        }

                        // Print time if it's not already printed.
                        if(!timeprinted) {
                            outfile << time << ",";
                            timeprinted = true;
                            printedTimes[k] = true;
                        }
                        else{
                            outfile<< ",";
                        }

                        // Print room based on its index.
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

                         // Find the index of the course in the input vectors.
                        int courseIndex = -1;
                        for (int idx = 0; idx < subjectinput.size(); ++idx) {
                            if (Course_Allocation[i][j][k] == subjectinput[idx]) {
                                courseIndex = idx;
                                break;
                            }
                        }
                         // If course found, write professor, semester, and branch.
                        if (courseIndex != -1) {
                            outfile << professor_nameinput[courseIndex] << ",";
                            outfile << semesterinput[courseIndex] << ",";
                            outfile << branch[branchinput[courseIndex]];
                        }
                        outfile << endl;
                        slotPrinted = true;   // Mark that a course is printed in this slot
                    }
                }
                if (!slotPrinted && dayPrinted) {
                    outfile << "," << time << endl;
                }
            }
        }
    }
    // Close the output file stream.
    outfile.close();
}



void Semester_TimeTable(const string& Semester) {
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
                            outfile << branch[branchinput[f]] << ",";
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
