#ifndef SIMPLEDICT_H
#define SIMPLEDICT_H

#include <string>
#include <vector>

/**
 * Простейший словарь для хранения результатов тестирования
 * Ключ: фамилия (string)
 * Значение: баллы по двум предметам (int, int)
 */
class SimpleDict {
private:
    // Векторы для хранения данных (индексы соответствуют друг другу)
    std::vector<std::string> lastNames;     // Ключи - фамилии
    std::vector<std::string> firstNames;    // Имена
    std::vector<int> scores1;               // Баллы по предмету 1
    std::vector<int> scores2;               // Баллы по предмету 2
    
    /**
     * Находит индекс фамилии в словаре
     * @param lastName фамилия для поиска
     * @return индекс или -1 если не найдено
     */
    int findIndex(const std::string& lastName) const;
    
public:
    /**
     * Конструктор по умолчанию
     */
    SimpleDict();
    
    /**
     * Добавляет абитуриента в словарь
     * @param lastName фамилия (ключ)
     * @param firstName имя
     * @param score1 балл по первому предмету
     * @param score2 балл по второму предмету
     * @return true если добавлено успешно
     */
    bool addStudent(const std::string& lastName, const std::string& firstName,
                    int score1, int score2);
    
    /**
     * Удаляет абитуриента по фамилии
     * @param lastName фамилия для удаления
     * @return true если удалено успешно
     */
    bool removeStudent(const std::string& lastName);
    
    /**
     * Проверяет наличие фамилии в словаре
     * @param lastName фамилия для проверки
     * @return true если найдено
     */
    bool hasStudent(const std::string& lastName) const;
    
    /**
     * Возвращает количество абитуриентов
     * @return размер словаря
     */
    int getCount() const;
    
    /**
     * Проверяет пустоту словаря
     * @return true если пусто
     */
    bool isEmpty() const;
    
    /**
     * Очищает словарь
     */
    void clear();
    
    /**
     * Загружает данные из файла
     * @param filename имя файла
     * @return true если успешно
     */
    bool loadFromFile(const std::string& filename);
    
    /**
     * Получает список неудачников (балл < 30)
     * @return отсортированный список "Фамилия Имя"
     */
    std::vector<std::string> getFailed() const;
    
    /**
     * Выводит всех абитуриентов
     */
    void printAll() const;
};

#endif