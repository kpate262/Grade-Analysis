#include <string>
#include <sstream>
#include <vector>
#include<iterator>
#include <regex>
#include <algorithm>
#include <iostream>
#include "gradeutil.h"
#include <fstream>
#include <iomanip>

using namespace std;


void info(const College &c){
	int courseCounter = 0;
	int studentCounter = 0;
	GradeStats g = GetGradeDistribution(c);
	int dfw = 0;
	int n = 0;
	for(const Dept &d: c.Depts){
		courseCounter += d.Courses.size();
		for(const Course &s: d.Courses){
			studentCounter += s.getNumStudents();
		}
	}
	
	cout << "# of courses taught: " << courseCounter << endl;
	cout << "# of students taught: " << studentCounter << endl;
	cout << "grade distribution (A-F): " << g.PercentA << "%, " <<
		g.PercentB << "%, " << g.PercentC << "%, " << g.PercentD 
		<< "%, " << g.PercentF << "% " << endl;
	cout << "DFW rate: " <<  GetDFWRate(c, dfw, n) << "%" << endl << endl;
	
	return;
}


string parseHeader(string line, string &season, string &year){
	string collegeName;
	stringstream ss(line);
	getline(ss, collegeName, ',');
	getline(ss, season, ',');
	getline(ss, year, ',');
	return collegeName;
}


void parseDept(Course &s, College &c){
	
	auto r = find_if(c.Depts.begin(), c.Depts.end(),
					 [&](const Dept d){
						 if(d.Name.compare(s.Dept) == 0){
							 return true;
						 }
						 else{
							 return false;
						 }
					 });
	
	if(r == c.Depts.end()){
		Dept d(s.Dept);
		d.Courses.push_back(s);
		c.Depts.push_back(d);
	}
	else{
		r->Courses.push_back(s);
	}
}


Dept findDept(const College &c, string line){
	Dept q;
	auto r = find_if(c.Depts.begin(), c.Depts.end(), 
					[&](const Dept &d){
						if(d.Name.compare(line) == 0){
							q = d;
							return true;
						}
						else{
							return false;
						}
					});
	if(r == c.Depts.end()){
		cout << "**dept not found" << endl;
		Dept d("empty");
		return d;
	}
	else{
		return q;
	}
	Dept d("empty");
	return d;
}


void getSummary(const Dept &y){
	int stuCount = 0;
	int dfw, n;
	cout << y.Name << ":" << endl;
	cout << " # courses taught: " << y.Courses.size() << endl;
	for (const Course &u: y.Courses){
		stuCount += u.getNumStudents();
	}

	GradeStats g = GetGradeDistribution(y);

	cout << " # students taught: " << stuCount << endl;
	cout << " grade distribution (A-F): " << g.PercentA << "%, " <<
			g.PercentB << "%, " << g.PercentC << "%, " << g.PercentD 
			<< "%, " << g.PercentF << "% " << endl; 
	cout << " DFW rate: " <<  GetDFWRate(y, dfw, n) << "%" << endl;
}



void summary(const College &c){
	string line = "";
	cout << "dept name, or all? ";
	getline(cin, line);
	
	if(line.compare("all") == 0){
		for(const Dept &d: c.Depts){
			getSummary(d);
		}
	}else{
		Dept y = findDept(c, line);
		if(y.Name.compare("empty") != 0){
			getSummary(y);
		}
	
	}
	
	return;
}



string gradingType(int p){
	if(p == 0)
		return "letter";
	else if(p == 1)
		return "satisfactory";
	else if(p == 2)
		return "unknown";
	return "";
}


void getCourseInfo(const Course &y){
	//int stuCount = 0;
	int dfw, n;
	cout << y.Dept << " " << y.Number << " (section " << y.Section << "): " 
		<< y.Instructor<< endl;
	GradeStats g = GetGradeDistribution(y);

	cout << " # students: " << y.getNumStudents() << endl;
	cout << " course type: " << gradingType(y.getGradingType()) << endl;
	cout << " grade distribution (A-F): " << g.PercentA << "%, " <<
			g.PercentB << "%, " << g.PercentC << "%, " << g.PercentD 
			<< "%, " << g.PercentF << "% " << endl; 
	cout << " DFW rate: " <<  GetDFWRate(y, dfw, n) << "%" << endl;
}



void stringSearch(string line1, string line2, const College &c){
	if(line1.compare("all") == 0){
		vector<Course> temp = FindCourses(c, line2);
		if(temp.size() == 0){
			cout << "**none found" << endl;
		}
		for(const Course &p: temp){
			getCourseInfo(p);
		}
	}
	else{
		Dept y = findDept(c, line1);
		if(y.Name.compare("empty") != 0){
			vector<Course> temp = FindCourses(y, line2);
			if(temp.size() == 0){
			cout << "**none found" << endl;
		}
			for(const Course &p: temp){
				getCourseInfo(p);
			}//for loop
		}//inner if
		else{
			//cout << "**none found" << endl;
		}
	}//else
}


void numericSearch(string line1, int courseNum, const College &c){
	if(line1.compare("all") == 0){
		vector<Course> temp = FindCourses(c, courseNum);
		if(temp.size() == 0){
			cout << "**none found" << endl;
		}
		for(const Course &p: temp){
			getCourseInfo(p);
		}
	}
	else{
		Dept y = findDept(c, line1);
		if(y.Name.compare("empty") != 0){
			vector<Course> temp = FindCourses(y, courseNum);
			if(temp.size() == 0){
				cout << "**none found" << endl;
			}
			for(const Course &p: temp){
				getCourseInfo(p);
			}//for loop
		}//inner if
		else{
			//cout << "**none found" << endl;
		}
	}//else
}

void search(const College &c){
	string line1 = "";
	cout << "dept name, or all? ";
	getline(cin, line1);
	string line2 = "";
	cout << "course # or instructor prefix? ";
	getline(cin, line2);
	
	int courseNum;
	stringstream ss(line2);
	ss >> courseNum;
	
	if(ss.fail()){
		stringSearch(line1, line2, c);
	}
	else{
		numericSearch(line1, courseNum, c);
	}

	return;
}



void unknown(const College &c){
	string line = "";
	cout << "dept name, or all? ";
	getline(cin, line);
	int count = 0;
	
	if(line.compare("all") == 0){
		for(const Dept &d: c.Depts){
			for(const Course &w: d.Courses){
				if(w.getGradingType() == 2){
					count++;
					getCourseInfo(w);
				}
			}
		}
	}else{
		Dept y = findDept(c, line);
		if(y.Name.compare("empty") != 0){
			for(const Course &w: y.Courses){
				if(w.getGradingType() == 2){
					count++;
					getCourseInfo(w);
				}
			}
		}
		
	}
	
	if(count == 0){
		cout << "**none found" << endl;
	}
	return;
}


void sortCourses(vector<Course> &s){
	int dfw, n;
	sort(s.begin(), s.end(),
		[&](Course a, Course b){
			if(GetDFWRate(a, dfw, n) > GetDFWRate(b, dfw, n)){
				return true;
			}
			else{
				return false;
			}
		});
}


void dfw(const College &c){
	int dfw, n;
	string line = "";
	cout << "dept name, or all? ";
	getline(cin, line);
	double threshold;
	cout << "dfw threshold? ";
	cin >> threshold;
	vector<Course> sortByDFW;
	int count = 0;
	//cout << threshold << endl;
	if(line.compare("all") == 0){
		for(const Dept &d: c.Depts){
			for(Course w: d.Courses){
				if(GetDFWRate(w, dfw, n) >= threshold){
					count++;
					sortByDFW.push_back(w);
				}
			}
		}
		
	}else{
		Dept y = findDept(c, line);
		if(y.Name.compare("empty") != 0){
			for( Course w: y.Courses){
				if(GetDFWRate(w, dfw, n) >= threshold){
					count++;
					sortByDFW.push_back(w);
				}
			}
			
		}
	}
	
	sortCourses(sortByDFW);
	if(count == 0){
		cout << "**none found" << endl;
		return;
	}
	for(const Course &f: sortByDFW){
		getCourseInfo(f);
	}
	return;
}



void sortA(vector<Course> &s){
	sort(s.begin(), s.end(),
		[&](Course a, Course b){
			if(GetGradeDistribution(a).PercentA > GetGradeDistribution(b).PercentA){
				return true;
			}
			else if(GetGradeDistribution(a).PercentA == GetGradeDistribution(b).PercentA){
				if(a.Dept < b.Dept){
					return true;
				}
				else if(a.Dept == b.Dept){
					if(a.Number < b.Number){
						return true;
					}
					else if(a.Number == b.Number){
						if(a.Section < b.Section){
							return true;
						}
						else{
							return false;
						}
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
			else{
				return false;
			}
		});
}


void letterA(const College &c){
	string line = "";
	cout << "dept name, or all? ";
	getline(cin, line);
	double threshold;
	cout << "letter A threshold? ";
	cin >> threshold;
	int count = 0;
	vector<Course> sortByA;
	
	if(line.compare("all") == 0){
		for(const Dept &d: c.Depts){
			for(const Course &w: d.Courses){
				if(GetGradeDistribution(w).PercentA >= threshold){
					count++;
					sortByA.push_back(w);
				}
			}
		}
	}else{
		Dept y = findDept(c, line);
		if(y.Name.compare("empty") != 0){
			for(const Course w: y.Courses){
				if(GetGradeDistribution(w).PercentA >= threshold){
					count++;
					sortByA.push_back(w);
				}
			}
		}
	}
	
	sortA(sortByA);
	if(count == 0){
		cout << "**none found" << endl;
		return;
	}
	
	for(const Course &f: sortByA){
		getCourseInfo(f);
	}
	return;
}



void queries(const College &c){
	vector<string> commands{"summary", "search", "unknown", "dfw", "letterA"};
	string command = "";
	while (command.compare("#") != 0){
		cout << "Enter a command> ";
		getline(cin, command);
		if(command.compare("#") == 0){
			exit(0);
		}
		auto r = find_if(commands.begin(), commands.end(),
			   [&](string s){
				  if(command.compare(s) == 0){
					  return true;
				  }
				   else{
					   return false;
				   }
			   });
		if(r == commands.end()){
			cout << "**unknown command" << endl;
		}
		else{
			if(r->compare("search") == 0){
				search(c);
			}
			else if(r->compare("summary") == 0){
				summary(c);
			}
			else if(r->compare("unknown") == 0){
				unknown(c);
			}
			else if(r->compare("dfw") == 0){
				dfw(c);
				string tu;
				getline(cin, tu);
			}
			else if(r->compare("letterA") == 0){
				letterA(c);
				string tu;
				getline(cin, tu);
			}
		}
	}
	
	return;
}


void sortCourses(Dept &s){
	sort(s.Courses.begin(), s.Courses.end(),
		[](Course a, Course b){
			if(a.Number < b.Number){
				return true;
			}
			else{
				return false;
			}
		});
}


void sortDept(College &c){
	sort(c.Depts.begin(), c.Depts.end(),
		[](Dept a, Dept b){
			if(a.Name < b.Name){
				return true;
			}
			
			else{
				return false;
			}
		});
	
	for(Dept &i: c.Depts){
		sortCourses(i);
	}
}



int main(){
	cout <<fixed;
	cout <<setprecision(2);
	
	string fileName;
	getline(cin, fileName);
	ifstream inData;
	inData.open(fileName);
	
	if(!inData.good()){
		cout << "File is bad/Couldn't open it";
		exit(-1);
	}
	
	string line, season, college, year;
	
	getline(inData, line);
	college = parseHeader(line, season, year);
	College c(college);
	getline(inData, line);
	
	cout << "** College of " << college << ", " << season << " " << year << " **" << endl;
	
	while(getline(inData, line)){
		Course n = ParseCourse(line);
		parseDept(n, c);
	}
	
	inData.close();
	sortDept(c);
	info(c);
	
	queries(c);
	
	
	
	return 0;
}
