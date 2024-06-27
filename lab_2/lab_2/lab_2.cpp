#include <iostream>
#include <memory>
#include <vector>
#include <cmath>


// Абстрактный базовый класс Triangle (треугольник)
class Triangle {
protected:
    double side1;       // Сторона  треугольника a
    double side2;       // Сторона  треугольника b
    double angle;   // Угол между a и b (в радианах)
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void input() = 0;
    virtual void output() const = 0;

    Triangle(double side1, double side2, double angle) : side1(side1), side2(side2), angle(angle) {}

    virtual Triangle& operator = (const Triangle& other) = default;
    Triangle(const Triangle& other) = default;

    virtual Triangle& operator = (Triangle&& other) = default;
    Triangle(Triangle&& other) = default;

    virtual ~Triangle() = default;
};

// Производный класс для прямоугольного треугольника
class RightTriangle : public Triangle {

public:
    explicit RightTriangle(double side1 = 0.0, double angle = 0.0) : Triangle(side1, side1* cos(angle), angle) {};

    RightTriangle(const RightTriangle& other) = default;
    RightTriangle& operator = (const RightTriangle& other) = default;

    RightTriangle(RightTriangle&& other) = default;
    RightTriangle& operator = (RightTriangle&& other) = default;

    double getArea() const override {
        return 0.5 * side1 * side2 * sin(angle);
    }

    double getPerimeter() const override {
        return side1 + side2 + hypot(side1, side2);
    }

    void input() override {
        std::cout << "Enter the two sides and the angle (in radians) of the right triangle: ";
        std::cin >> side1 >> side2 >> angle;
        if (side1 <= 0 || side2 <= 0 || angle <= 0) {
            throw std::invalid_argument("Invalid input: sides and angle must be positive");
        }
    }

    void output() const override {
        std::cout << "Right Triangle - Side 1: " << side1 << ", Side 2: " << side2 << ", Angle: " << angle << " radians" << std::endl;
    }
};

// Производный класс для равнобедренного треугольника
class IsoscelesTriangle : public Triangle {

public:
    explicit IsoscelesTriangle(double side1 = 0.0, double angle = 0.0) : Triangle(side1, side2, angle) {};

    IsoscelesTriangle(const IsoscelesTriangle& other) = default;
    IsoscelesTriangle& operator = (const IsoscelesTriangle& other) = default;

    IsoscelesTriangle(IsoscelesTriangle&& other) = default;
    IsoscelesTriangle& operator = (IsoscelesTriangle&& other) = default;

    double getArea() const override {
        return 0.5 * side1 * side2 * sin(angle);
    }

    double getPerimeter() const override {
        return 2 * side1 + side2;
    }

    void input() override {
        std::cout << "Enter the base, one side, and the angle (in radians) of the isosceles triangle: ";
        std::cin >> side1 >> side2 >> angle;
    }

    void output() const override {
        std::cout << "Isosceles Triangle - Base: " << side1 << ", Side: " << side2 << ", Angle: " << angle << " radians" << std::endl;
    }
};

// Производный класс для равностороннего треугольника
class EquilateralTriangle : public Triangle {

public:
    explicit EquilateralTriangle(double side1 = 0.0) : Triangle(side1, side1, angle) {};


    EquilateralTriangle(const EquilateralTriangle& other) = default;
    EquilateralTriangle& operator = (const EquilateralTriangle& other) = default;

    EquilateralTriangle(EquilateralTriangle&& other) = default;
    EquilateralTriangle& operator = (EquilateralTriangle&& other) = default;

    double getArea() const override {
        return (sqrt(3) / 4) * side1 * side1;
    }

    double getPerimeter() const override {
        return 3 * side1;
    }

    void input() override {
        std::cout << "Enter the side and the angle (in radians) of the equilateral triangle: ";
        std::cin >> side1 >> angle;
    }

    void output() const override {
        std::cout << "Equilateral Triangle - Side: " << side1 << ", Angle: " << angle << " radians" << std::endl;
    }
};

int main() {
    std::vector<std::unique_ptr<Triangle>> triangles;

    triangles.push_back(std::make_unique<RightTriangle>());
    triangles.push_back(std::make_unique<IsoscelesTriangle>());
    triangles.push_back(std::make_unique<EquilateralTriangle>());

    for (const auto& triangle : triangles) {
        triangle->input();
        triangle->output();
        std::cout << "Area: " << triangle->getArea() << ", Perimeter: " << triangle->getPerimeter() << std::endl;
    }

    return 0;
}