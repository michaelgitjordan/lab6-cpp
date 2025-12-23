#include "SimpleDict.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    SimpleDict dict;
    string filename;
    
    cout << "Тестирование: \n" << endl;
    
    cout << "Введите имя файла : ";
    getline(cin, filename);
    
    if (filename.empty()) {
        filename = "students.txt";
    }
    
    cout << "\nЗагрузка данных из файла: " << filename << endl;
    if (!dict.loadFromFile(filename)) {
        cout << "ОШИБКА: Не удалось загрузить данные!" << endl;
        return 1;
    }
    
    
    vector<string> failed = dict.getFailed();
    
    cout << "\nРезультаты: " << endl;
    
    if (failed.empty()) {
        cout << "Все абитуриенты допущены к экзаменам!" << endl;
    } else {
        cout << "Не допущены к экзаменам (" << failed.size() << " человек.):" << endl;
        cout << "--------------------------------" << endl;
        
        for (size_t i = 0; i < failed.size(); i++) {
            cout << i + 1 << ". " << failed[i] << endl;
        }
        
        cout << "--------------------------------" << endl;
    }
     
    cout << "\nПрограмма завершена " << endl;
    return 0;
}