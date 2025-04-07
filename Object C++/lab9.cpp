#include<iostream>
#include<string>

using namespace std;

class Person {
private:
    string firstName;
    string lastName;
    int birthYear;

public:
    Person(string f, string l, int b) : firstName(f), lastName(l), birthYear(b) {}

    virtual void displayData() {
        cout << "Personal data:" << endl;
        cout << "First name: " << firstName << endl;
        cout << "Last name: " << lastName << endl;
        cout << "Year of birth: " << birthYear << endl;
    }

    void setFirstName(string f) { this->firstName = f; }
    void setBirthYear(int year) { this->birthYear = year; }
    void setLastName(string l) { this->lastName = l; }

    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    int getBirthYear() const { return birthYear; }
};

class Student : public Person {
private:
    string fieldOfStudy;
    int yearOfStudy;
public:
    Student(string f, string l, int b, string field, int year) : Person(f, l, b), fieldOfStudy(field), yearOfStudy(year) {}

    void displayData() {
        Person::displayData();
        cout << "Field of study: " << fieldOfStudy << endl;
        cout << "Year of study: " << yearOfStudy << endl;
    }
};

class Employee : public Person {
private:
    string workplace;
    string jobTitle;
public:
    Employee(string f, string l, int b, string wp, string job) : Person(f, l, b), workplace(wp), jobTitle(job) {}

    // Copy constructor with changes
    Employee(const Employee& other) : Person(other.getFirstName(), "NewLastName", 2000), workplace(other.workplace), jobTitle(other.jobTitle) {}

    void displayData() {
        Person::displayData();
        cout << "Workplace: " << workplace << endl;
        cout << "Job title: " << jobTitle << endl;
    }
};

// Display array of persons:
void displayArrayOfPersons(Person** array, int size) {
    for (int i = 0; i < size; i++) {
        array[i]->displayData();
        cout << endl;
    }
}

Person** addPeopleUnder30(Person** array, int size, int& newSize) {

    // Loop counting people under 30 years of age
    for (int i = 0; i < size; i++) {
        if (array[i]->getBirthYear() > 1993) {
            newSize++;
        }
    }

    // New array of people under 30
    Person** newArray = new Person * [newSize];

    // Storing data into the new array
    for (int i = 0, temp = 0; i < size; i++) {
        if (array[i]->getBirthYear() > 1993) {
            newArray[temp] = array[i];
            temp++;
        }
    }

    return newArray;
}


int main() {
    // Part A)
    cout << "Part A)" << endl;

    Person* person = new Person("John", "Doe", 2001);
    person->displayData();
    cout << endl;

    // Part B)
    cout << "Part B)" << endl;

    Student student1("Adam", "Nowak", 2003, "Computer Science", 2);
    student1.displayData();
    cout << endl;

    // Part C)
    cout << "Part C)" << endl;

    Employee employee1("Anna", "Nowak", 1980, "Magic Company", "Job Title");
    Employee employee2 = employee1;

    cout << "Employee data for employee nr. 1" << endl;
    employee1.displayData();
    cout << endl;

    cout << "Employee data for employee nr. 2" << endl;
    employee2.displayData();
    cout << endl;

    // Part D)
    cout << "Part D)" << endl;
    Person** personArray = new Person * [4];

    // Assign previously created people:
    personArray[0] = person;
    personArray[1] = &employee2;
    personArray[2] = &student1;
    personArray[3] = &employee1;

    cout << "Array of people:" << endl;
    displayArrayOfPersons(personArray, 4);

    // Part E)
    int newSize = 0;  // Since we don't know how many such people exist
    Person** newPersonArray = addPeopleUnder30(personArray, 4, newSize);

    cout << "New array of people under 30 years old:" << endl;
    displayArrayOfPersons(newPersonArray, newSize);

    // Free memory
    delete person;
    delete[] personArray;
    delete[] newPersonArray;

    system("PAUSE");
    return 0;
}
