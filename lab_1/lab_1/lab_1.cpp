/* Создать класс для описания треугольника.Поля данных должны включать угля и стороны.
Реализовать операции получения и изменения данных, вычисления площади, вычисления
периметра, высот а также определения вида(равнобедренный, равносторонний,
    прямоугольный).*/

#include <iostream>
#include <cmath>
#include <string>

    class Triangle {
    private:
        double sideA;
        double sideB;
        double sideC;
        double angleA;
        double angleB;
        double angleC;

    public:
        // Конструктор по умолчанию
        Triangle() noexcept : sideA(0), sideB(0), sideC(0), angleA(0), angleB(0), angleC(0) {}

        // Конструктор с параметрами и проверкой
        Triangle(double a, double b, double c) noexcept : sideA(a), sideB(b), sideC(c) {
            angleA = acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / M_PI;
            angleB = acos((a * a + c * c - b * b) / (2 * a * c)) * 180 / M_PI;
            angleC = 180 - angleA - angleB;
            if (!isValidTriangle()) {
                std::cerr << "Ошибка: Неверные стороны и углы треугольника!" << std::endl;
                sideA = sideB = sideC = angleA = angleB = angleC = 0;
            }
        }
        // Конструктор копирования
        Triangle(const Triangle& other) noexcept : sideA(other.sideA), sideB(other.sideB), sideC(other.sideC), angleA(other.angleA), angleB(other.angleB), angleC(other.angleC) {}
        //Перегрузка оператора присваивания
        Triangle& operator=(const Triangle& other) noexcept {
            if (this == &other) {
                return *this;
            }
            sideA = other.sideA;
            sideB = other.sideB;
            sideC = other.sideC;
            angleA = other.angleA;
            angleB = other.angleB;
            angleC = other.angleC;
            return *this;
        }


        // Конструктор перемещения
        Triangle(Triangle&& other) noexcept : sideA(other.sideA), sideB(other.sideB), sideC(other.sideC),
            angleA(other.angleA), angleB(other.angleB), angleC(other.angleC) {
            other.sideA = other.sideB = other.sideC = 0.0;
            other.angleA = other.angleB = other.angleC = 0.0;
        }
        //Перегрузка оператора перемещающего присваивания
        Triangle& operator=(Triangle&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            sideA = other.sideA;
            other.sideA = 0.0;
            sideB = other.sideB;
            other.sideB = 0.0;
            sideC = other.sideC;
            other.sideC = 0.0;
            angleA = other.angleA;
            other.angleA = 0.0;
            angleB = other.angleB;
            other.angleB = 0.0;
            angleC = other.angleC;
            other.angleC = 0.0;
            return *this;
        }

        // Деструктор
        ~Triangle() {
            std::cout << "Объект треугольник удален" << std::endl;
        }
        //метод инициализации, т.е. как конструктор
        void Init(double a, double b, double c, double angleA, double angleB, double angleC) {
            sideA = a;
            sideB = b;
            sideC = c;
            this->angleA = angleA;
            this->angleB = angleB;
            this->angleC = angleC;
        }

        void Init(double a, double b, double c) {
            sideA = a;
            sideB = b;
            sideC = c;
            angleA = acos((sideB * sideB + sideC * sideC - sideA * sideA) / (2 * sideB * sideC)) * 180 / M_PI;
            angleB = acos((sideA * sideA + sideC * sideC - sideB * sideB) / (2 * sideA * sideC)) * 180 / M_PI;
            angleC = 180 - angleA - angleB;
        }

        // Проверка на правильно введенные данные
        bool isValidTriangle() const {
            std::cout << this->toString() << std::endl;
            return sideA * sideB * sideC * angleA * angleB * angleC > 1e-14 //Если сторона или угол равны нулю, то это не треугольник
                && std::abs(sin(angleA * M_PI / 180.0) * sideB - sin(angleB * M_PI / 180.0) * sideA) < 1e-14 //Теорема синусов
                && std::abs(sin(angleC * M_PI / 180.0) * sideB - sin(angleB * M_PI / 180.0) * sideC) < 1e-14;
        }
        //Определение вида треугольника
        std::string getType() const {
            if (
                std::abs(sideA - sideB) < 1e-14
                &&
                std::abs(sideB - sideC) < 1e-14)
            {
                return "Равносторонний";
            }
            if (
                std::abs(sideA - sideB) < 1e-14
                ||
                std::abs(sideA - sideC) < 1e-14
                ||
                std::abs(sideB - sideC) < 1e-14)
            {
                return "Равнобедренный ";
            }
            if (
                std::abs(angleA - 90) < 1e-14
                ||
                std::abs(angleB - 90) < 1e-14
                ||
                std::abs(angleC - 90) < 1e-14
                ) {
                return "Прямоугольный ";
            }
            return "Обычный ";
        }

        // Вычисление площади треуголньика
        double getArea() const {
            double s = (sideA + sideB + sideC) / 2;
            return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
        }
        // Вычисление периметр треугольника
        double getPerimeter() const {
            return sideA + sideB + sideC;
        }
        // Вывод строкой сторон и углов треугольника
        std::string toString() const {
            return "Треугольник со сторонами " + std::to_string(sideA) + ", " + std::to_string(sideB) + ", " + std::to_string(sideC) + " и углами " + std::to_string(angleA) + ", " + std::to_string(angleB) + ", " + std::to_string(angleC);
        }
        // Вычисление высоты треугольника через полупериметр
        double getHeight() const {
            const double s = (sideA + sideB + sideC) / 2;
            const double height = 2 * sqrt(s * (s - sideA) * (s - sideB) * (s - sideC)) / sideA;
            return height;
        }
        // Геттеры
        double getSideA() const { return sideA; }
        double getSideB() const { return sideB; }
        double getSideC() const { return sideC; }
        double getAngleA() const { return angleA; }
        double getAngleB() const { return angleB; }
        double getAngleC() const { return angleC; }

        // Сеттеры
        void setSideA(double a) { sideA = a; }
        void setSideB(double b) { sideB = b; }
        void setSideC(double c) { sideC = c; }
        void setAngleA(double a) { angleA = a; }
        void setAngleB(double b) { angleB = b; }
        void setAngleC(double c) { angleC = c; }

        // Метод считывания сторон треугольника от пользователя
        void read() {
            std::cout << "Введите стороны треугольника:" << std::endl;
            std::cout << "Сторона A: ";
            std::cin >> sideA;
            std::cout << "Сторона B: ";
            std::cin >> sideB;
            std::cout << "Сторона C: ";
            std::cin >> sideC;
            angleA = acos((sideB * sideB + sideC * sideC - sideA * sideA) / (2 * sideB * sideC)) * 180 / M_PI;
            angleB = acos((sideA * sideA + sideC * sideC - sideB * sideB) / (2 * sideA * sideC)) * 180 / M_PI;
            angleC = 180 - angleA - angleB;
            if (!isValidTriangle()) {
                std::cerr << "Ошибка: Неверные стороны треугольника!" << std::endl;
                sideA = sideB = sideC = angleA = angleB = angleC = 0;
            }
        }
};
int main() {
    setlocale(LC_ALL, "RUS");
    // Создание обычного треугольника
    Triangle defaultTriangle;
    std::cout << defaultTriangle.toString() << std::endl;
    std::cout << "Тип треугольника: " << defaultTriangle.getType() << std::endl;

    // Создание треугольника со сторонами 3,4,5, вычисление площади, периметра и высоты. определение типа треугольника
    Triangle customTriangle(3, 4, 5);
    std::cout << "Площадь: " << customTriangle.getArea() << std::endl;
    std::cout << "Периметр: " << customTriangle.getPerimeter() << std::endl;
    std::cout << "Высота: " << customTriangle.getHeight() << std::endl;
    std::cout << "Тип треугольника: " << customTriangle.getType() << std::endl;

    // Создание нового скопированного треугольника
    Triangle copiedTriangle(customTriangle);
    std::cout << "Скопированный треугольник: " << std::endl << copiedTriangle.toString() << std::endl;
    std::cout << "Тип треугольника: " << copiedTriangle.getType() << std::endl;

    // Создание нового треугольника, переместив пользовательский треугольник
    Triangle movedTriangle = std::move(customTriangle);
    std::cout << "Перемещенный треугольник: " << std::endl << movedTriangle.toString() << std::endl;
    std::cout << "Тип треугольника: " << movedTriangle.getType() << std::endl;

    // Создание треугольника со сторонами, забитыми пользователем
    Triangle userInputTriangle;
    userInputTriangle.read();
    std::cout << "Треугольник пользователя: " << userInputTriangle.toString() << std::endl;
    std::cout << "Площадь: " << userInputTriangle.getArea() << std::endl;
    std::cout << "Периметр: " << userInputTriangle.getPerimeter() << std::endl;
    std::cout << "Высота: " << userInputTriangle.getHeight() << std::endl;
    std::cout << "Тип треугольника: " << userInputTriangle.getType() << std::endl;

    defaultTriangle = customTriangle;
    std::cout << "оператор копирующего присваивания работает: " << defaultTriangle.toString() << std::endl;
    defaultTriangle = std::move(userInputTriangle);
    std::cout << "оператор перемещающего присваивания работает: " << defaultTriangle.toString() << std::endl;
    return 0;
}