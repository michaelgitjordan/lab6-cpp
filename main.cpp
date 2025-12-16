#include "TouristSet.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const vector<string> POPULAR_COUNTRIES = {
    "Франция", "Италия", "Испания", "Германия", "Великобритания",
    "Греция", "Турция", "США", "Япония", "Таиланд",
    "Мексика", "Португалия", "Нидерланды", "Швейцария", "Австрия"
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isCountryValid(const string& country) {
    return find(POPULAR_COUNTRIES.begin(), POPULAR_COUNTRIES.end(), country) 
           != POPULAR_COUNTRIES.end();
}

void showCountries() {
    cout << "\nСписок доступных стран: \n";
    cout << "(нужно вводить точно как указано)\n\n";
    
    for (size_t i = 0; i < POPULAR_COUNTRIES.size(); i++) {
        cout << POPULAR_COUNTRIES[i];
        if (i != POPULAR_COUNTRIES.size() - 1) {
            cout << ", ";
        }
        if ((i + 1) % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void inputForTourist(TouristSet& tourist, int touristNum) {
    tourist.clear();
    
    cout << "\n Ввод для туриста " << touristNum << " \n";
    showCountries();
    
    cout << "\nИнструкция:\n";
    cout << "1. Вводите страны ТОЧНО как в списке выше\n";
    cout << "2. Для завершения введите: stop\n";
    cout << "3. Для просмотра списка введите: list\n\n";
    
    int count = 1;
    while (true) {
        cout << "Страна " << count << " (или 'stop'): ";
        string input;
        cin >> input;
        
        if (input == "stop") {
            break;
        }
        
        if (input == "list") {
            showCountries();
            continue;
        }
        
        if (isCountryValid(input)) {
            if (tourist.contains(input)) {
                cout << "Страна '" << input << "' уже добавлена! Пропускаем.\n";
            } else {
                tourist.add(input);
                cout << "Добавлено: " << input << "\n";
                count++;
            }
        } else {
            cout << "Ошибка: '" << input << "' нет в списке!\n";
            cout << "Вводите страны точно как показано выше.\n";
        }
    }
    
    cout << "\nТурист " << touristNum << " посетил " 
         << tourist.size() << " стран.\n";
    cout << "================================\n";
}

int main() {
    vector<TouristSet> tourists;
    TouristSet allCountries(POPULAR_COUNTRIES);
    
    cout << "Посещение стран туристами: " << endl;
    
    while (true) {
        cout << "\n Меню \n";
        cout << "1. Ввести данные о туристах\n";
        cout << "2. Посмотреть введенные данные\n";
        cout << "3. Выполнить анализ\n";
        cout << "4. Выйти\n";
        cout << "Выберите: ";
        
        int choice;
        cin >> choice;
        clearInput();
        
        if (choice == 1) {
            cout << "\nСколько туристов? ";
            int n;
            cin >> n;
            clearInput();
            
            if (n <= 0) {
                cout << "Неверное количество!\n";
                continue;
            }
            
            tourists.clear();
            tourists.resize(n);
            
            for (int i = 0; i < n; i++) {
                inputForTourist(tourists[i], i + 1);
            }
            
            cout << "\nДанные сохранены!\n";
            
        } else if (choice == 2) {
            if (tourists.empty()) {
                cout << "\nНет данных! Сначала введите данные.\n";
            } else {
                cout << "\nВведенные данные: \n";
                for (size_t i = 0; i < tourists.size(); i++) {
                    cout << "Турист " << (i + 1) << ": ";
                    if (tourists[i].isEmpty()) {
                        cout << "нет стран";
                    } else {
                        auto countries = tourists[i].getElements();
                        for (size_t j = 0; j < countries.size(); j++) {
                            cout << countries[j];
                            if (j != countries.size() - 1) {
                                cout << ", ";
                            }
                        }
                    }
                    cout << endl;
                }
            }
            
        } else if (choice == 3) {
            if (tourists.empty()) {
                cout << "\nНет данных! Сначала введите данные.\n";
                continue;
            }
            
            cout << "Всего туристов: " << tourists.size() << endl;
            cout << "Всего стран в перечне: " << allCountries.size() << endl;
            
            TouristSet visitedByAll = tourists[0];
            for (size_t i = 1; i < tourists.size(); i++) {
                visitedByAll = visitedByAll.Intersect(tourists[i]);
            }
            
            cout << "\n1. Страны, которые посетили ВСЕ туристы:\n";
            if (visitedByAll.isEmpty()) {
                cout << "   (нет таких стран)\n";
            } else {
                auto countries = visitedByAll.getElements();
                for (const auto& country : countries) {
                    cout << "   - " << country << endl;
                }
            }
            
            TouristSet visitedBySome;
            for (const auto& tourist : tourists) {
                visitedBySome = visitedBySome.Union(tourist);
            }
            
            cout << "\n2. Страны, которые посетили НЕКОТОРЫЕ туристы:\n";
            auto someCountries = visitedBySome.getElements();
            for (const auto& country : someCountries) {
                cout << "   - " << country << endl;
            }
            
            TouristSet visitedByNone = allCountries.Except(visitedBySome);
            
            cout << "\n3. Страны, которые НЕ посетил НИКТО из туристов:\n";
            if (visitedByNone.isEmpty()) {
                cout << "   (все страны кто-то посетил)\n";
            } else {
                auto noneCountries = visitedByNone.getElements();
                for (const auto& country : noneCountries) {
                    cout << "   - " << country << endl;
                }
            }
                    
        } else if (choice == 4) {
            cout << "\nВыход из программы...\n";
            break;
            
        } else {
            cout << "\nНеверный выбор! Выберите 1-4.\n";
        }
    }
    
    return 0;
}