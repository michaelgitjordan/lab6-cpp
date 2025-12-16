#include "Lab3.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;


Person::Person(): name(""), height(0) {}
Person::Person(const string& name, int height) : name(name), height(height) {}

void Person::inputName(){
    cout << "Введите имя: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    while (name.empty()){
        cout << "Имя не может быть пустым, введите!";
        getline(cin, name);
    }
}

void Person::inputHeight() {
    while (true) {
        cout << "Введите рост(см): ";
        if (cin >> height && height > 0 && height <= 272){
            break;
        } else {
            cout << "Некорректный рост! (введите от 1 до 272 см)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Person::input() {
    cout << "Введите данные о человеке: (Имя, рост) " << endl;
    inputName();
    inputHeight();
}

string Person::toString() const {
    return name + ", рост: " + to_string(height);
}

void Person::print() const {
    cout << toString() << endl;
}

string Person::getName() const{
    return name;
}

int Person::getHeight() const {
    return height;
}

void Person::setName(const string& newName) {
    name = newName;
}

void Person::setHeight(int newHeight){
    if (newHeight > 0 && newHeight <= 272){
        height = newHeight;
    } else {
        cout << "Введите корректное значение роста! (1 - 272 см)";
    }
}


Name::Name() : lastName(""), firstName(""), middleName("") {}

Name::Name(const string& first) : lastName(""), firstName(first), middleName("") {}

Name::Name(const string& first, const string& middle, bool hasNoLastName) : lastName(""), firstName(first), middleName(middle) {}

Name::Name(const string& last, const string& first) : lastName(last), firstName(first), middleName("") {}

Name::Name(const string& last, const string& first, const string& middle) : lastName(last), firstName(first), middleName(middle) {}

void Name::inputLastName() {
    cout << "Введите фамилию (или Enter чтобы пропустить): ";
    string input;
    getline(cin, input);
    
    // Удаляем пробелы в начале и конце
    size_t start = input.find_first_not_of(" \t");
    size_t end = input.find_last_not_of(" \t");
    
    if (start != string::npos && end != string::npos) {
        lastName = input.substr(start, end - start + 1);
        if (!lastName.empty()) {
            cout << "Фамилия \"" << lastName << "\" сохранена" << endl;
        } else {
            cout << "Фамилия не указана" << endl;
        }
    } else {
        lastName = "";
        cout << "Фамилия не указана" << endl;
    }
}

void Name::inputFirstName() {
    cout << "Введите личное имя (или Enter чтобы пропустить): ";
    string input;
    getline(cin, input);
    
    size_t start = input.find_first_not_of(" \t");
    size_t end = input.find_last_not_of(" \t");
    
    if (start != string::npos && end != string::npos) {
        firstName = input.substr(start, end - start + 1);
        if (!firstName.empty()) {
            cout << "Имя \"" << firstName << "\" сохранено" << endl;
        } else {
            cout << "Имя не указано" << endl;
        }
    } else {
        firstName = "";
        cout << "Имя не указано" << endl;
    }
}

void Name::inputMiddleName() {
    cout << "Введите отчество (или Enter чтобы пропустить): ";
    string input;
    getline(cin, input);
    
    size_t start = input.find_first_not_of(" \t");
    size_t end = input.find_last_not_of(" \t");
    
    if (start != string::npos && end != string::npos) {
        middleName = input.substr(start, end - start + 1);
        if (!middleName.empty()) {
            cout << "Отчество \"" << middleName << "\" сохранено" << endl;
        } else {
            cout << "Отчество не указано" << endl;
        }
    } else {
        middleName = "";
        cout << "Отчество не указано" << endl;
    }
}

void Name::input() {
    cout << "-- Ввод имени " << endl;
    inputLastName();
    inputFirstName();
    inputMiddleName();
    cout << "-- Имя успешно введено: " << toString() << endl;
}

void Name::print() const {
    cout << toString() << endl;
}

string Name:: toString() const {
    string result;
        if (hasLastName()) {
        result += lastName;
    }
    
    if (hasFirstName()) {
        if (!result.empty()) result += " ";
        result += firstName;
    }
    
    if (hasMiddleName()) {
        if (!result.empty()) result += " ";
        result += middleName;
    }
    
    // Если все компоненты пустые
    if (result.empty()) {
        result = "[Имя не задано]";
    }
    
    return result;
}

string Name::getLastName() const {
    return lastName;
}

string Name::getFirstName() const {
    return firstName;
}

string Name::getMiddleName() const {
    return middleName;
}

void Name::setLastName(const string& last) {
    lastName = last;
}

void Name::setFirstName(const string& first) {
    firstName = first;
}

void Name::setMiddleName(const string& middle) {
    middleName = middle;
}

bool Name::hasLastName() const {
    return !lastName.empty();
}

bool Name::hasFirstName() const {
    return !firstName.empty();
}

bool Name::hasMiddleName() const {
    return !middleName.empty();
}


Department::Department(const string& name) : name(name), boss(nullptr) {}

Department::Department(const string& name, Employee* boss) : name(name), boss(boss) {}

void Department:: setBoss(Employee* newBoss) {
    boss = newBoss;
    cout << newBoss ->getName() << " назначен начальником отдела " << name << endl;
}

void Department::addEmployee(Employee* employee) {
    employees.push_back(employee);
}

string Department::getName() const{
    return name;
}

Employee* Department::getBoss() const{
    return boss;
}

string Department::toString() const {
    if (boss != nullptr){
        return "Отдел " + name + ", начальник: " + boss->getName();
    } else {
        return "Отдел" + name + ", начальник не назначен.";
    }
}

const vector<Employee*>& Department::getEmployees() const {
    return employees;
}


void Department::print() const{
    cout << toString() << endl;
}


// Employee::Employee(const string& name) : name(name), department(nullptr) {}

Employee::Employee(const string& name, Department* department) : name(name), department(department) {
    if (department != nullptr) {
        department->addEmployee(this);
    }
}

// void Employee::setDepartment(Department* newDepartment) {
//     department = newDepartment;
//     cout << name << " переведен в отдел " << newDepartment->getName() << endl;
// }

void Employee::setAsBoss() {
    if (department != nullptr) {
        department->setBoss(this);
    } else {
        cout << name << " не привязан к отедлу, его нельзя сделать боссом! " << endl;
    }
}

string Employee::getName() const {
    return name;
}

Department* Employee::getDepartment() const{
    return department;
}

string Employee::toString() const{
    if (department == nullptr){
        return name + " не привязан к отделу.";
    }
    if (isBoss()) {
        return name + " начальник отдела " + department->getName();
    } else {
        if (department->getBoss() != nullptr) {
            return name + " работает в отделе " + department->getName() + ", начальник которого " + department->getBoss()->getName();
        } else {
            return name + " работает в отделе " + department->getName() + " начальник не найден";
        }
    }
}

void Employee::print() const{
    cout << toString() << endl;
}

bool Employee::isBoss() const{
    return(department != nullptr && department->getBoss() == this);
}

vector<Employee*> Employee::getDepartmentColleagues() const {
    vector<Employee*> colleagues;
    
    if (department != nullptr) {
        const vector<Employee*>& allEmployees = department->getEmployees();
        for (Employee* emp : allEmployees) {
            if (emp != this) {  // Исключаем самого себя
                colleagues.push_back(emp);
            }
        }
    }
    
    return colleagues;
}


// Добавляем метод уменьшения патронов
void Pistol::decreaseBullets(int count) {
    if (bullets >= count) {
        bullets -= count;
    } else {
        bullets = 0;
    }
}

Pistol::Pistol() : bullets(5) {
    cout << "Создан пистолет с " << bullets << " патронами" << endl;
}

Pistol::Pistol(int initialBullets) : bullets(initialBullets) {
    cout << "Создан пистолет с " << bullets << " патронами" << endl;
}

void Pistol::shoot() {
    if (bullets > 0) {
        cout << "Бах!" << endl;
        decreaseBullets(1);
        cout << "Осталось патронов: " << bullets << endl;
    } else {
        cout << "Клац!" << endl;
        cout << "Пистолет пуст!" << endl;
    }
}

void Pistol::reload(int newBullets) {
    bullets = newBullets;
    cout << "Перезарядка! Теперь " << bullets << " патронов" << endl;
}

int Pistol::getBullets() const {
    return bullets;
}

void Pistol::print() const {
    cout << "Пистолет: " << bullets << " патронов" << endl;
}


Automatic::Automatic() : Pistol(30), fireRate(30) {
    cout << "Создан автомат: " << bullets << " патронов, скорострельность " << fireRate << " выстр/сек" << endl;
}

Automatic::Automatic(int maxBullets) : Pistol(maxBullets), fireRate(maxBullets / 2) {
    if (fireRate < 1) fireRate = 1;
    cout << "Создан автомат: " << bullets << " патронов, скорострельность " << fireRate << " выстр/сек" << endl;
}

Automatic::Automatic(int maxBullets, int fireRate) : Pistol(maxBullets), fireRate(fireRate) {
    if (this->fireRate < 1) this->fireRate = 1;
    cout << "Создан автомат: " << bullets << " патронов, скорострельность " << this->fireRate << " выстр/сек" << endl;
}

void Automatic::shoot() {
    if (bullets > 0) {
        int shotsToFire = min(fireRate, bullets);
        
        cout << "Автомат стреляет " << shotsToFire << " раз:" << endl;
        
        for (int i = 0; i < shotsToFire; i++) {
            cout << "Ба-бах!" << endl;
        }
        
        decreaseBullets(shotsToFire);
        cout << "Осталось патронов: " << bullets << endl;
    } else {
        cout << "Клац-клац!" << endl;
        cout << "Автомат пуст!" << endl;
    }
}

void Automatic::shootSeconds(int seconds) {
    int totalShots = seconds * fireRate;
    int actualShots = min(totalShots, bullets);
    
    if (actualShots > 0) {
        cout << "Автомат стреляет " << seconds << " секунд (" << actualShots << " выстрелов):" << endl;
        
        for (int i = 0; i < actualShots; i++) {
            cout << "Тра-та-та!" << endl;
        }
        
        decreaseBullets(actualShots);
        cout << "Осталось патронов: " << bullets << endl;
    } else {
        cout << "Клац-клац!" << endl;
        cout << "Автомат пуст!" << endl;
    }
}

void Automatic::print() const {
    cout << "Автомат: " << bullets << " патронов, скорострельность " << fireRate << " выстр/сек" << endl;
}

int Automatic::getFireRate() const {
    return fireRate;
}