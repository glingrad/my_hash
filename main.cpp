#include <iostream>
#include "hashing.h" // Предполагается, что hashing.h содержит определение MyHashing

int main() {
    MyHashing hasher; // Создание объекта класса MyHashing

    std::string password; // Переменная для хранения пароля
    std::cout << "Введите пароль для хеширования: ";
    std::getline(std::cin, password); // Чтение пароля с ввода

    // Хеширование пароля
    std::string hashedPassword = hasher.hashing(password);

    if (!hashedPassword.empty()) {
        std::cout << "Хешированный пароль: " << hashedPassword << std::endl; // Вывод хеша
    } else {
        std::cerr << "Произошла ошибка при хешировании пароля." << std::endl;
    }

    return 0;
}
