#ifndef HASHING_H // Защита от повторного включения заголовка
#define HASHING_H
#include <iostream> // Для ввода-вывода
#include <iomanip> // Для форматирования ввода-вывода
#include <string> // Для работы со строками
#include <sstream> // Для работы с потоками строк
#include <openssl/rand.h> // Для генерации случайных чисел
#include <argon2.h> // Для работы с Argon2 (хеширование паролей)
#include <vector> // Для работы с векторами
using namespace std; // Использование пространства имен std

class MyHashing { // Определение класса MyHashing
private:
    // Генерация соли для хеширования пароля
    void generate_salt(vector<unsigned char>& salt) {
        // Генерация случайных байтов для соли
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            cerr << "Ошибка генерации соли" << endl; // Ошибка при генерации соли
            abort(); // Завершение программы в случае ошибки
        }
    }

public:
    // Хеширование пароля с использованием Argon2
    string hashing(const string &data) {
        vector<unsigned char> salt(16); // Создание вектора для соли размером 16 байт
        generate_salt(salt); // Генерация соли

        vector<unsigned char> hash(32); // Создание вектора для хеша размером 32 байта
        const int iterations = 12; // Количество итераций хеширования
        const size_t memory = 1 << 16; // Объем памяти для хеширования (64 КБ)
        const int parallelism = 1; // Параллелизм (количество потоков)

        // Хеширование пароля с использованием Argon2
        int result = argon2id_hash_raw(iterations, memory, parallelism,
                                       data.c_str(), data.length(),
                                       salt.data(), salt.size(),
                                       hash.data(), hash.size());

        // Проверка на ошибки хеширования
        if (result != ARGON2_OK) {
            cerr << "Ошибка хэширования: " << argon2_error_message(result) << endl; // Сообщение об ошибке
            return ""; // Возврат пустой строки в случае ошибки
        }

        // Преобразование хеша и соли в строку
        ostringstream oss_hash, oss_salt; // Создание потоков для хеша и соли
        for (auto byte : hash) { // Проход по каждому байту хеша
            oss_hash << hex << setw(2) << setfill('0') << static_cast<int>(byte); // Форматирование в шестнадцатеричную строку
        }
        for (auto byte : salt) { // Проход по каждому байту соли
            oss_salt << hex << setw(2) << setfill('0') << static_cast<int>(byte); // Форматирование в шестнадцатеричную строку
        }

        return oss_salt.str() + ":" + oss_hash.str(); // Возвращает соль и хеш, разделенные двоеточием
    }
};
#endif // HASHING_H // Конец защиты от повторного включения заголовка
