#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

int UsnToBeUpdated=0;

struct subject{
	int crts;
	double total_marks;
	double value;

};
subject s;
subject s1;
subject s2;
subject s3;
subject s4;
subject s5;
subject s6;
subject s7;
subject s8;


class student 
{
	private:
		char Student_Name[50];
		int usn;
		double student_sgpa;
		char Student_Grade;
		int total_percentage;
		bool flag;
		double total_sub;
		double total_crts;
		double sgpa;
		

		
		
		
		
	public:
		student();
		void getdata();
		void CheckForDuplicationInFile();
		void showdata();
		void TabularDisplay();
		int GetStudentRollNo();
		void ShowStudentRecord(int);
		void Write_Student_Record_In_File();
		void Update_Student_Record(int);
		void Delete_Student_Record(int);
		void Delete_From_Duplicate_File(int);
		void Show_Result_Menu();
		void Display_Class_Result();
		double grade_calculator(double totalMark, int crts);
		void value_of_subj();
		void CalculateGrade();
		
};


void student::getdata()
{
	flag=false;
	cout<<"\nEnter the RollNo of the student : ";
	cin>>usn;
	if(UsnToBeUpdated!=usn)
	CheckForDuplicationInFile();
	
	if(flag==true)
	{
		cout<<"Error duplicate record"<<endl;
		return;
	}
	cout<<"\n\nEnter the name of student: ";
	cin.ignore();
	cin.getline(Student_Name,50);
	cout<<"\nEnter The marks in filestructure out of 100 : ";
    cin>>s1.total_marks;
    cout<<"Its Credit :";
    cin>>s1.crts;
    cout<<"\nEnter The marks in softwaretesting out of 100 : ";
    cin>>s2.total_marks;
    cout<<"Its Credit :";
    cin>>s2.crts;
    cout<<"\nEnter The marks in webtech out of 100 : ";
    cin>>s3.total_marks;
    cout<<"Its Credit :";
    cin>>s3.crts;
    cout<<"\nEnter The marks in datamining/java out of 100 : ";
    cin>>s4.total_marks;
    cout<<"Its Credit :";
    cin>>s4.crts;
    cout<<"\nEnter The marks in NCS/SCM out of 100 : ";
    cin>>s5.total_marks;
    cout<<"Its Credit :";
    cin>>s5.crts;
    cout<<"\nEnter The marks in FS LAB out of 100 : ";
    cin>>s6.total_marks;
    cout<<"Its Credit :";
    cin>>s6.crts;
    cout<<"\nEnter The marks in MAD LAB out of 100 : ";
    cin>>s7.total_marks;
    cout<<"Its Credit :";
    cin>>s7.crts;
    cout<<"\nEnter The marks in ST LAB out of 100 : ";
    cin>>s8.total_marks;
    cout<<"Its Credit :";
    cin>>s8.crts;
    CalculateGrade();
	
}


void student::CheckForDuplicationInFile()
{
	int Current_usn=0;
	flag=false;
	ifstream infile("DuplicateCheckingFile.txt");
	while(!infile.eof())
	{
		infile>>Current_usn;
		if(Current_usn==usn)
		{
			flag=true;
		}
	}
	infile.close();
	if(flag==false)
	{
		ofstream outfile("DuplicateCheckingFile.txt",ios::app);
		outfile<<"\n"<<usn;
		outfile.close();
		
	}
}


void student::showdata()
{
	cout<<"\nRollNo of student = "<<usn;
	cout<<"\nName of the Student = "<<Student_Name;
	cout<<"\nMarks in filestructure = "<<int(s1.total_marks);
	cout<<"\nMarks in softwaretesting = "<<int(s2.total_marks);
	cout<<"\nMarks in webtech = "<<int(s3.total_marks);
	cout<<"\nMarks in datamining/java = "<<int(s4.total_marks);
	cout<<"\nMarks in NCS/SCM = "<<int(s5.total_marks);
	cout<<"\nMarks in FS lab = "<<int(s6.total_marks);
	cout<<"\nMarks in MAD lab = "<<int(s7.total_marks);
	cout<<"\nMarks in ST lab = "<<int(s8.total_marks);
	cout<<"\nSGPA = "<<sgpa;
	cout<<"\nGrade of the student = "<<Student_Grade;
	
}

student::student()
{
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	outFile.close();
	ofstream outDFile;
	outDFile.open("DuplicateCheckingFile.txt",ios::app);
	outDFile.close();
}

void student::Write_Student_Record_In_File()
{
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	
	getdata();
	
	if(flag==false)
	{
		outFile.write(reinterpret_cast<char*>(this),sizeof(student));
		outFile.close();
		cout<<"\n\n student record has been created\n";
	}
	if(flag==true)
	{
		cout<<"student record not created due to duplication\n";
		outFile.close();
	}
	cin.ignore();
	cin.get();
}

void student::Update_Student_Record(int n)
{
	UsnToBeUpdated=n;
	bool found=false;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
	}
	while(!File.eof()&&found==false)
	{
		File.read(reinterpret_cast<char*> (this), sizeof(student));
		if(GetStudentRollNo()==n)
		{
			showdata();
			cout<<"\n\nPlease Enter the New Details of student: "<<endl;
			getdata();
			if(flag==false)
			{
				int pos=(-1)*static_cast<int>(sizeof(*this));
				File.seekp(pos,ios::cur);
				File.write(reinterpret_cast<char *> (this), sizeof(student));
			}
			found=true;
		}
	}
	File.close();
	if(flag==true)
	{
		cout<<"could not update because this RollNo already exists";
	}
	if(found==false)
	{
		cout<<"\n\n Record Not Found";
	}
	cin.ignore();
	cin.get();
	
	if(flag==false&&found==true&&UsnToBeUpdated!=usn)
    {
    	Delete_From_Duplicate_File(n);
    }
    UsnToBeUpdated=0;
}


void student::Delete_Student_Record(int n)
{
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile could not be opened..Press any key";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
	{
		if(GetStudentRollNo()!=n)
		{
			outFile.write(reinterpret_cast<char *> (this), sizeof(student));
		}
	}
	
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\nRecord deleted..Press any key";
	cin.ignore();
	cin.get();
	Delete_From_Duplicate_File(n);
}


void student::Delete_From_Duplicate_File(int RollNoOfRecord)
{
	int Current_usn;
	ifstream InFile("DuplicateCheckingFile.txt");
	ofstream OutFile("TempFile.txt");
	InFile.seekg(0,ios::beg);
	while(!InFile.eof())
	{
		InFile>>Current_usn;
		if(Current_usn!=RollNoOfRecord)
		{
			OutFile<<"\n"<<Current_usn;
		}
	}
	
	InFile.close();
	OutFile.close();
	
	remove("DuplicateCheckingFile.txt");
	rename("TempFile.txt","DuplicateCheckingFile.txt");
	
	cin.ignore();
	cin.get();
}

double student::grade_calculator(double totalMark, int crts) { 

	
    
	if(totalMark>=9.0 && totalMark<=10.0)
    return totalMark*crts;
            
    else if(totalMark>=8.5 && totalMark<9.0)
    return totalMark*crts;
 
    else if(totalMark>=8.0 && totalMark<8.5)
    return totalMark*crts; 
 
    else if(totalMark>=7.5 && totalMark<8.0)
    return totalMark*crts;   
 
    else if(totalMark>=7.0 && totalMark<7.5)
    return totalMark*crts;
 
    else if(totalMark>=6.5 && totalMark<7.0)
    return totalMark*crts;
 
    else if(totalMark>=6.0 && totalMark<6.5)        
	return totalMark*crts;
 
    else if(totalMark>=5.0 && totalMark<6.0)        
	return totalMark*crts;
 
    else if(totalMark>=4.5 && totalMark<5.0)
    return totalMark*crts;
 
    else if(totalMark>=4.0 && totalMark<4.5)
    return totalMark*crts;
 
    else if(totalMark>=3.0 && totalMark<4.0)
    return totalMark*crts;
 
    else if(totalMark>=0 && totalMark<3.0)
    return totalMark*crts;
 
    else       
    return totalMark*crts;
}

void student::value_of_subj(){
//Grade multiply by it's crts for each subjects
s1.value=grade_calculator((s1.total_marks/10),s1.crts);
s2.value=grade_calculator((s2.total_marks/10),s2.crts);
s3.value=grade_calculator((s3.total_marks/10),s3.crts);
s4.value=grade_calculator((s4.total_marks/10),s4.crts);
s5.value=grade_calculator((s5.total_marks/10),s5.crts);
s6.value=grade_calculator((s6.total_marks/10),s6.crts);
s7.value=grade_calculator((s7.total_marks/10),s7.crts);
s8.value=grade_calculator((s8.total_marks/10),s8.crts);

	total_sub=s1.value+s2.value+s3.value+s4.value+s5.value+s6.value+s7.value+s8.value;
	total_crts=s1.crts+s2.crts+s3.crts+s4.crts+s5.crts+s6.crts+s7.crts+s8.crts;
	
	sgpa=total_sub/total_crts;
}



void student::CalculateGrade()
{
//	calculate_student_gpa();
	value_of_subj();
//	int total_percentage;
	total_percentage=(s1.total_marks+s2.total_marks+s3.total_marks+s4.total_marks+s5.total_marks+s6.total_marks+s7.total_marks+s8.total_marks)/8.0;
	if(sgpa>=9.0)
	Student_Grade='S';
	if(sgpa>=8.9&&sgpa<8.0)
    Student_Grade='A';
    if(sgpa>=7.9&&sgpa<7.0)
    Student_Grade='B';
    if(sgpa>=6.9&&sgpa<6.0)
    Student_Grade='C';
    if(sgpa>=5.9&&sgpa<5.0)
    Student_Grade='D';
    if(sgpa>=4.9&&sgpa<4.0)
    Student_Grade='E';
    if(sgpa<=4.0)
    Student_Grade='F';
}

void student::TabularDisplay()
{
	cout<<usn<<setw(7)<<" "<<Student_Name<<setw(20-strlen(Student_Name))<<int(s1.total_marks)<<setw(5)<<int(s2.total_marks)<<setw(5)<<int(s3.total_marks)<<setw(9)<<int(s4.total_marks)<<setw(12)<<int(s5.total_marks)<<setw(10)<<int(s6.total_marks)<<setw(8)<<int(s7.total_marks)<<setw(8)<<int(s8.total_marks)<<setw(8)<<total_percentage<<setw(9)<<Student_Grade<<endl;
}

int student::GetStudentRollNo()
{
	return usn;
}

void student::ShowStudentRecord(int n)
{
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not opened !! Press any key to continue";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	
	while(inFile.read(reinterpret_cast<char *> (this),sizeof(student)))
	{
		if(GetStudentRollNo()==n)
		{
			showdata();
            flag=true;
		}
	}
	inFile.close();
    if(flag==false)
    cout<<"\n\nrecord does not exist";
    cin.ignore();
    cin.get();
}


void student::Show_Result_Menu()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\n\t3. Back to Main Menu/Home Screen";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
		case '1':Display_Class_Result();
			break;
		case '2':cout<<"\n\n\tEnter the RollNo of Student = ";
				 cin>>rno;
				 ShowStudentRecord(rno);		
				 break;
		case '3':break;
		default: cout<<"\a";
	}
}


void student::Display_Class_Result()
{
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened.. Press any key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\t\tALL CLASS RESULT \n\n";
	cout<<"=================================================================================================================\n";
	cout<<"RNO       Name              fs   st   wt     dm/java     ncs/scm     FSL     MAD     STL     %age     Grade"<<endl;
	cout<<"=================================================================================================================\n";
	
	while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
	{
		TabularDisplay();	
	}
	
	inFile.close();
	cin.ignore();
	cin.get();
}


void intro();
void entry_menu();
void display_all();

int main()
{
	system("CLS");
	system("color B1");
	char ch;
	student std_obj;
  	cout.setf(ios::fixed|ios::showpoint);
  	cout<<setprecision(2);
	intro();
	do
	{
	system("cls");
	intro();
	cout<<"\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
	cout<<"\n\n\t1. Result Calculation System";
	cout<<"\n\n\t2. Student Database Management System";
	cout<<"\n\n\t3. Exit";
	cout<<"\n\n\n\n\n\tPlease Select Your Option (1-3)";
	cin>>ch;
	switch(ch)
	{
		case '1':
			std_obj.Show_Result_Menu();
			break;
		case '2':
			entry_menu();
			break;
		case '3':
			break;
		default: cout<<"\a";
	}
	}while(ch!=3);
	
		
	system("pause");
	return 0;
}

void intro()
{
	cout<<"\n\n\n**  WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM  **\n\n";
}

void entry_menu()
{
	char ch;
	int num;
	student std;
	system("CLS");
	cout<<"\n\n\n\t\t\tSTUDENT DATABASE MANAGEMENT SYSTEM MENU";
	cout<<"\n\n\t1. CREATE STUDENT RECORD";
	cout<<"\n\n\t2. SHOW RECORD OF ALL STUDENTS";
	cout<<"\n\n\t3. SEARCH STUDENTS RECORD";
	cout<<"\n\n\t4. UPDATE STUDENT RECORD";
	cout<<"\n\n\t5. DELETE STUDENT RECORD";
	cout<<"\n\n\t6. BACK TO HOME SCREEN";
	cout<<"\n\n\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
		case '1':
			std.Write_Student_Record_In_File();
			break;
		case '2':
			display_all();
			break;
		case '3':
			cout<<"\n\n\t Please Enter The RollNo: ";
			cin>>num;
			std.ShowStudentRecord(num);
			break;
		case '4':
			cout<<"\n\n\t Please Enter The RollNo: ";
			cin>>num;
			std.Update_Student_Record(num);
			break;
		case '5':
			cout<<"\n\n\t Please Enter The RollNo: ";
			cin>>num;
			std.Delete_Student_Record(num);
			break;
		case '6':
			break;
		default:cout<<"\a"; entry_menu();
		
	}
}

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n==============================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}