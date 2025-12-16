#include "StudentDictionary.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    StudentDictionary dict;
    string filename;
    
    cout << "Введите имя файла с данными: ";
    cin >> filename;
    
    if (!dict.loadFromFile(filename)) {
        cout << "Ошибка загрузки данных. Проверьте файл." << endl;
        return 1;
    }
    
    vector<string> failed = dict.getFailedStudents();
    
    cout << endl;
    if (failed.empty()) {
        cout << "Нет абитуриентов, потерпевших неудачу." << endl;
    } else {
        cout << "Абитуриенты, потерпевшие неудачу:" << endl;
        for (const auto& student : failed) {
            cout << student << endl;
        }
    }
    
    return 0;
}