#include "SimpleDict.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

SimpleDict::SimpleDict() {

}

int SimpleDict::findIndex(const std::string& lastName) const {

    for (size_t i = 0; i < lastNames.size(); i++) {
        if (lastNames[i] == lastName) {
            return i;
        }
    }
    return -1; 
}

bool SimpleDict::addStudent(const std::string& lastName, const std::string& firstName,
                           int score1, int score2) {

    if (findIndex(lastName) != -1) {
        return false; 
    }
    

    if (score1 < 0 || score1 > 100 || score2 < 0 || score2 > 100) {
        return false; 
    }
    

    lastNames.push_back(lastName);
    firstNames.push_back(firstName);
    scores1.push_back(score1);
    scores2.push_back(score2);
    
    return true;
}

bool SimpleDict::removeStudent(const std::string& lastName) {
    int index = findIndex(lastName);
    if (index == -1) {
        return false; 
    }
    

    lastNames.erase(lastNames.begin() + index);
    firstNames.erase(firstNames.begin() + index);
    scores1.erase(scores1.begin() + index);
    scores2.erase(scores2.begin() + index);
    
    return true;
}

bool SimpleDict::hasStudent(const std::string& lastName) const {
    return findIndex(lastName) != -1;
}

int SimpleDict::getCount() const {
    return lastNames.size(); 
}

bool SimpleDict::isEmpty() const {
    return lastNames.empty();
}

void SimpleDict::clear() {
    lastNames.clear();
    firstNames.clear();
    scores1.clear();
    scores2.clear();
}

bool SimpleDict::loadFromFile(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return false;
    }
    
    clear(); 
    
    int N;
    file >> N;
    
  
    if (N > 500) {
        cerr << "Слишком много абитуриентов (максимум 500)" << endl;
        file.close();
        return false;
    }
    

    for (int i = 0; i < N; i++) {
        string lastName, firstName;
        int score1, score2;
        
        if (file >> lastName >> firstName >> score1 >> score2) {
            if (!addStudent(lastName, firstName, score1, score2)) {
                cerr << "Ошибка добавления: " << lastName << " " << firstName << endl;
            }
        } else {
            cerr << "Ошибка чтения строки " << i + 1 << endl;
            break;
        }
    }
    
    file.close();
    return getCount() > 0; 
}

vector<string> SimpleDict::getFailed() const {
    vector<string> failed;
    
    for (size_t i = 0; i < lastNames.size(); i++) {
        if (scores1[i] < 30 || scores2[i] < 30) {
            failed.push_back(lastNames[i] + " " + firstNames[i]);
        }
    }
    
    sort(failed.begin(), failed.end());
    
    return failed;
}

void SimpleDict::printAll() const {
    cout << "Всего абитуриентов: " << getCount() << endl;
    for (size_t i = 0; i < lastNames.size(); i++) {
        cout << lastNames[i] << " " << firstNames[i] 
             << " " << scores1[i] << " " << scores2[i] << endl;
    }
}