#ifndef Lab3_h
#define Lab3_h

#include <string>
#include <vector>
using namespace std;


class Department;
class Employee;


class Pistol {
    protected:
        int bullets;
        
    public:
        Pistol();
        Pistol(int initialBullets);

        virtual void shoot();
        void reload(int newBullets);
        int getBullets() const;
        virtual void print() const;

    protected:
        void decreaseBullets(int count = 1);
};

class Automatic : public Pistol {
private:
    int fireRate;  

public:
    Automatic();  
    Automatic(int maxBullets);  
    Automatic(int maxBullets, int fireRate);  
    
    void shoot() override;  
    void print() const override;  
    
    void shootSeconds(int seconds); 
    int getFireRate() const;
};



class Department {
    private:
        string name;
        Employee* boss;
        vector<Employee*> employees;
    
    public:
        Department(const string& name);
        Department(const string& name, Employee* boss);

        void setBoss(Employee* newBoss);
        void addEmployee(Employee* employee);
        string getName() const;
        Employee* getBoss() const;
        const vector<Employee*>& getEmployees() const;
        string toString() const;
        void print() const;   
        void printEmployees() const;   
};


class Employee {
    private:
        string name;
        Department* department;
    
    public:
        // Employee(const string& name);
        Employee(const string& name, Department* department);

        // void setDepartment(Department* newDepartment);
        void setAsBoss();

        string getName() const;
        Department* getDepartment() const;
        string toString() const;
        void print() const;

        bool isBoss() const;

        vector<Employee*> getDepartmentColleagues() const;

};


class Person {
    private:
        string name;
        int height;
    

    public:
        Person();
        Person(const string& name, int height);

        void input();
        void inputName();
        void inputHeight();

        void print() const;
        string toString() const;

        string getName() const;
        int getHeight() const;

        void setName(const string& newName);
        void setHeight(int newHeight);

};


class Name {
    private:
        string lastName;
        string firstName;
        string middleName; // 'отчество' 
    
    
    public:
        Name();
        Name(const string& first);
        Name(const string& first, const string& middle, bool hasNoLastName);
        Name(const string& last, const string& first);
        Name(const string& last, const string& first, const string& middle);
        

        void input();
        void inputLastName();
        void inputFirstName(); 
        void inputMiddleName();

        
        void print() const;
        string toString() const;

        string getLastName() const;
        string getFirstName() const;
        string getMiddleName() const;


        void setLastName(const string& last);
        void setFirstName(const string& first);
        void setMiddleName(const string& middle);


        bool hasLastName() const;
        bool hasFirstName() const; 
        bool hasMiddleName() const;
};


#endif