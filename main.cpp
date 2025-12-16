#include "Lab3.h"
#include <iostream>


using namespace std;

void showMainMenu() {
    cout << endl;
    cout << "-- Главное меню -- " << endl;
    cout << "Выберите действие: " << endl;
    cout << "1 -- Работа с классом Person " << endl;
    cout << "2 -- Работа с классом Name " << endl;
    cout << "3 -- Работа Department и Employee" << endl;
    cout << "4 -- Работа с пистолетом " << endl;
    cout << "5 -- Работа с автоматом " << endl;
    cout << "6 -- Выход из проги " << endl;
    cout << endl;
}

void personMenu() {
    cout << "-- Person меню -- " << endl;
    cout << "\nСоздание нового человека:" << endl;
    Person customPerson;
    customPerson.input();
    cout << "Результат: ";
    customPerson.print();
}

void nameMenu() {
    cout << "-- Name меню -- " << endl;
    cout << "\nСоздание нового имени:" << endl;
    Name customName;
    customName.input();
    cout << "Результат: ";
    customName.print();   
}

void createNewPerson(Person& person) {
    cout << "Создание нового человека " << endl;
    person.input();
    cout << endl;
}

// Старье
void showCurrentPerson(const Person& customPerson){

    if (customPerson.getName().empty()) {
        cout << "Этот человек еще не 'создан' ! " << endl;
    } else {
        cout << "Текущий созданный человек: " << endl;
        customPerson.print();
        cout << endl;
    }
}

void empDepExample() {
    cout << "Пример работы сотрудников и отделов: " << endl;

    Department itDepartment("IT");

    Employee petrov("Петров", &itDepartment);
    Employee kozlov("Козлов", &itDepartment);
    Employee sidorov("Сидоров", &itDepartment);

    // cout << "Назначаем сотрудников в отдел: " << endl;

    // petrov.setDepartment(&itDepartment);
    // kozlov.setDepartment(&itDepartment);
    // sidorov.setDepartment(&itDepartment);

    kozlov.setAsBoss();

    cout << "Результат: " << endl;
    petrov.print();
    kozlov.print();
    sidorov.print();

    cout << "Инфа о отделе: " << endl;
    itDepartment.print();

    cout << "Коллеги Петрова:" << endl;
    vector<Employee*> petrovColleagues = petrov.getDepartmentColleagues();
    for (Employee* colleague : petrovColleagues) {
        cout << "   - " << colleague->getName() << endl;
    }

    cout << endl;

}

void demPistol(){
    cout << "-- Пистолет -- " << endl;

    cout << "1. Создаем пистолет с 3 патронами:" << endl;
    Pistol pistol(3);
    pistol.print();
    
    cout << "\n2. Стреляем 5 раз:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "Выстрел " << i << ": ";
        pistol.shoot();
    }

}

void automaticMenu() {
    Automatic* automatic = nullptr;
    int choice;
    
    do {
        cout << "Автомат" << endl;
        cout << "1 - Создать автомат по умолчанию (30/30)" << endl;
        cout << "2 - Создать автомат с указанными патронами" << endl;
        cout << "3 - Создать автомат с патронами и скорострельностью" << endl;
        cout << "4 - Стрелять очередью" << endl;
        cout << "5 - Стрелять N секунд" << endl;
        cout << "6 - Перезарядить" << endl;
        cout << "7 - Показать информацию" << endl;
        cout << "8 - Назад в главное меню" << endl;
        cout << "Выберите действие: ";
        
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                if (automatic != nullptr) delete automatic;
                automatic = new Automatic();
                break;
                
            case 2: {
                if (automatic != nullptr) delete automatic;
                int bullets;
                cout << "Введите количество патронов: ";
                cin >> bullets;
                cin.ignore();
                automatic = new Automatic(bullets);
                break;
            }
                
            case 3: {
                if (automatic != nullptr) delete automatic;
                int bullets, rate;
                cout << "Введите количество патронов: ";
                cin >> bullets;
                cout << "Введите скорострельность: ";
                cin >> rate;
                cin.ignore();
                automatic = new Automatic(bullets, rate);
                break;
            }
                
            case 4:
                if (automatic != nullptr) {
                    automatic->shoot();
                } else {
                    cout << "Сначала создайте автомат!" << endl;
                }
                break;
                
            case 5:
                if (automatic != nullptr) {
                    int seconds;
                    cout << "Введите количество секунд: ";
                    cin >> seconds;
                    cin.ignore();
                    automatic->shootSeconds(seconds);
                } else {
                    cout << "Сначала создайте автомат!" << endl;
                }
                break;
                
            case 6:
                if (automatic != nullptr) {
                    int newBullets;
                    cout << "Введите новое количество патронов: ";
                    cin >> newBullets;
                    cin.ignore();
                    automatic->reload(newBullets);
                } else {
                    cout << "Сначала создайте автомат!" << endl;
                }
                break;
                
            case 7:
                if (automatic != nullptr) {
                    automatic->print();
                } else {
                    cout << "Сначала создайте автомат!" << endl;
                }
                break;
                
            case 8:
                if (automatic != nullptr) {
                    delete automatic;
                    automatic = nullptr;
                }
                cout << "Возврат в главное меню..." << endl;
                break;
                
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 8);
}

int main() {
    Person customPerson;
    int choice;

    do {
        showMainMenu();
        cin >> choice;
        cout << endl;
        cin.ignore();


        switch(choice){
            case 1:
                personMenu();
                break;
            case 2:
                nameMenu();
                break;
            case 3:
                empDepExample();
                break;
            case 4:
                demPistol();
                break;
            case 5:
                automaticMenu();
                break;
            case 6:
                cout << "До свидания! " << endl;
                break;
            default: 
             cout << "Неверный выбор. Выбирайте от 1 до 5! " << endl;
        }
    } while (choice != 6);

    return 0;
}
