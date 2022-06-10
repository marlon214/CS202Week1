/*
Name: Marlon Alejandro, 5002573038, 1001, ASSIGNMENT_1
Description: Store information from database file, as an array of Users.
Sort the Array and print it out
Input: database.txt
Output: Output to terminal
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_USERS = 100; //Max number of users 

//User class where every user has a username and password
class User
{
	string username, password, firstName, lastName;
	static int count; //Count of total users. This is static so it is shared between all users

	const int printWidth = 40; //Used for printing formatting
	const int cellWidth = (printWidth / 2) - 2; //Also for formatting

	public: //Public modifier means these can be accessed anywhere
		User() { username = password = firstName = lastName = ""; } //Default constructor
		User(string, string, string, string);

		string getName() { return firstName + " " + lastName; }
		void printUser();

		static int getCount() { return count; } //Accessor that returns the count
		static void sortUsers(User userArr[MAX_USERS], int length);

		void operator = (const User& other);
};

int User::count = 0; //Static variables should be initialized at global scope in C++
User readUserFromFile(ifstream& file); //Function prototype for global function

int main(int argc, char** argv)
{
	User users[MAX_USERS]; //Static array to store users into
	ifstream infile;
	//TODO: Finish main

	//Error check that the number of command line arguments was correct 
	/* YOUR CODE HERE */
	    if(argc != 2)
    {
        //argc must contain 2 commands
        //commands are stored in argv

        cout << "ERROR: Incorrect usage." << endl;
		cout << "./a.out <filename>" << endl;
		return 1;
        //1 is an exit code that we returned an error
    }


	
	//Open the file and check if it was successful. The first argument in argv should be the filename
	/* YOUR CODE HERE */
    infile.open(argv[1]);
    if (!infile.good()){
        cout << "ERROR: Could not open file: " << argv[1] << endl;
        return 1;
    }

	//Read from the file until we're at the end, storing each read User into the array, then close the file
	int count = 0; //Separate count variable for reading (to make debugging easier)
	
	/* YOUR CODE HERE: Do the reading here*/
    int i=0;

	while (!infile.eof() && i < MAX_USERS){
		users[i]= readUserFromFile(infile);
        count++;
		i++;
    }

	cout << "Read a total of " << count << " Users from file " << endl;

	//Sort the array of users and print
	int userCount = User::getCount(); //Just grab it once so we don't keep calling the function
	cout << "User count is " << userCount << endl;
	User::sortUsers(users, userCount); //Static functions should be call using className::function(...)
	for (int j = 1; j <= userCount; j++){
				users[j].printUser();
	}
	return 0;
}

//------------------------------ Function definitions ---------------------------------
//TODO: YOUR CODE HERE 
//Finish the functions and give descriptions for each

/*
*/
User::User(string f, string l, string u, string p)
{
	//A contructor is called when an object is created
	//Use the constructor to initialize all of the User members to the given params
	//Then increment the User count to represent that we made one object
	firstName = f;
	lastName = l;
	username = u;
	password = p;
	count++;
}

/*
*/
User readUserFromFile(ifstream& file)
{
	//Read a User from the given file stream and return it
	string first, last, user, pass;

	//Read the first, last, user name, and password of the user from the file
	file >> first >> last >> user >> pass;

	//Then construct a new user using all of these strings and return that

	return User(first,last,user,pass); //Change this line to return your result user
}

/*
* 
*/
void User::sortUsers(User userArr[MAX_USERS], int length)
{
	//Sort the array of users, preferrably using Bubble Sort
	//Sort using the first name as the member to search by
	bool isSorted = false;
    for (int i =0 ; i < count && !isSorted; i++){
        isSorted = true;

        //if out of order, swap
        //bubble sort
        // bubbles the max to the end
        for (int j=0; j <count-i; j++){
            if(userArr[j].firstName > userArr[j+1].firstName){
                User temp = userArr[j];
                userArr[j] = userArr[j+1];
                userArr[j+1] = temp;
                isSorted = false;
            }
        }
    }
}

/* Prints this user to the standard out, cout. This function is done for you
*/
void User::printUser()
{
	cout << setfill('-') << setw(printWidth + 1) << "" << endl; //Print the top line
	cout << setfill(' ') << left << "| " << setw(cellWidth) << getName() << "| " << setw(cellWidth)
		<< username << "|" << endl;
	cout << setfill('-') << setw(printWidth + 1) << "" << endl << endl; //Print the bottom line
}

/* This is an operator overload for setting to Users = to each other when using references.
* We'll cover operator overloads later.
* This exists to make your code a bit easier when doing the swap in the sort function
*/
void User::operator = (const User& other)
{
	//Just copy all the members
	this->firstName = other.firstName;
	this->lastName = other.lastName;
	this->username = other.username;
	this->password = other.password;
}
