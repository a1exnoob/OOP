#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <string>
#include <ctime>
#include <tuple>

/*
Методические указания.
1. В части № 1 тип контейнера и встроенный тип данных выбирается самостоятельно.
2. В части № 2 в качестве пользовательского типа данных использовать свой
пользовательский класс(придумать самостоятельно, например: студент, кот, сотрудник,
товар, автомобиль, книга, банковский счёт и т.д.).
3. При создании контейнеров в части № 2 объекты выгружать и загружать из потока
(файла).
4. Для вставки и удаления элементов контейнера в части № 2 использовать
соответствующие операции, определенные в классе контейнера.
5. Для создания второго контейнера в части № 3 можно использовать либо алгоритм
remove_copy_if, либо алгоритм copy_if.
6. Для поиска элемента в коллекции можно использовать алгоритм find_if, либо for_each,
либо binary_search, если контейнер отсортирован.
7. Для сравнения элементов при сортировке по возрастанию используется операция <<,
которая должна быть перегружена в пользовательском классе. Для сортировки по
убыванию следует написать функцию comp и использовать вторую версию алгоритма sort.
8. Условия поиска и замены элементов выбираются самостоятельно и для них пишется
функция-предикат.
9. Для ввода-вывода объектов пользовательского класса следует перегрузить операции
>> и <<.
10. Некоторые алгоритмы могут не поддерживать используемые в вашей программе
контейнеры. Например, алгоритм sort не поддерживает контейнеры, которые не имеют
итераторов произвольного доступа. В этом случае следует написать свой алгоритм.
Например, для стека алгоритм сортировки может выполняться следующим образом:
переписать стек в вектор, отсортировать вектор, переписать вектор в стек.
*/
using std::string;

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {}

    Date() {
        srand(time(0));
        day = rand() % 31 + 1;
        month = rand() % 12 + 1;
        year = rand() % 5 + 2024;
    }
    bool operator < (const Date& other) const { return (year == other.year && ((month == other.month && day < other.day) || month < other.month)) || (year < other.year); }
    bool operator > (const Date& other) const { return (year == other.year && ((month == other.month && day > other.day) || month > other.month)) || (year > other.year); }

    std::string get_date() const {
        return std::to_string(day) + '/' + std::to_string(month) + '/' + std::to_string(year);
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.day << '/' << date.month << '/' << date.year;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Date& date) {
        is >> date.day >> date.month >> date.year;
        return is;
    }
};

class BankCard
{
private:
    string ownersName;
    unsigned int number;
    Date date;
    unsigned int CVV;
    int balanceRub;

public:
    friend std::ostream& operator << (std::ostream&, const BankCard&);
    friend std::istream& operator >> (std::istream&, BankCard&);
    friend void read_list_of_cards_from_file(std::list<BankCard>&);

    explicit BankCard(string ownersName = "", Date date = Date(), unsigned int number = 0, unsigned int CVV = 0, int balanceRub = 0) : ownersName(ownersName), date(date), number(number), CVV(CVV), balanceRub(balanceRub) {}
    BankCard(const BankCard&) = default;
    BankCard(BankCard&&) = default;
    BankCard& operator = (const BankCard& other) {
        if (this == &other) { return *this; }
        ownersName = other.ownersName;
        date = other.date;
        number = other.number;
        CVV = other.CVV;
        balanceRub = other.balanceRub;
        return *this;
    }
    BankCard& operator = (BankCard&& other) {
        if (this == &other) { return *this; }
        ownersName = std::move(other.ownersName);
        date = std::move(other.date);
        number = std::move(other.number);
        CVV = std::move(other.CVV);
        balanceRub = std::move(other.balanceRub);
        return *this;
    }
    ~BankCard() = default;

    Date get_date() const { return date; }

    bool operator<(const BankCard& other) const {
        return date < other.date;
    }
};

std::ostream& operator << (std::ostream& stream, const BankCard& bankCard)
{
    stream << "ФИО:" << bankCard.ownersName << "\t Дата действия карты: " << bankCard.date << "\t номер карты" << bankCard.number << "\t CVV:" << bankCard.CVV << "\t баланс карты:" << bankCard.balanceRub << std::endl;
    return stream;
}

std::istream& operator >> (std::istream& stream, BankCard& bankCard)
{
    stream >> bankCard.ownersName >> bankCard.date >> bankCard.number >> bankCard.CVV >> bankCard.balanceRub;
    return stream;
}

void read_list_of_cards_from_file(std::list<BankCard>& list) {
    std::ifstream file("data.txt");
    if (file.is_open()) {
        BankCard temp;
        while (file >> temp) {
            list.push_back(temp);
        }
        file.close();
    }
}

int main() {
    setlocale(LC_ALL, "RUS");

    /*==================================================================
    ПЕРВАЯ ЧАСТЬ
    ==================================================================*/

    // 1) Создать объект-контейнер и заполнить его данными.
    std::vector<int> vector{ 1, 2, 3, 4, 5, 6, 7 };

    // 2) Просмотреть контейнер.
    std::cout << "Данные вектора:" << std::endl;
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << '\t';
    }
    std::cout << std::endl;

    // 3) Изменить контейнер, удалив из него одни элементы и заменив другие.
    vector.pop_back();
    vector[3] = vector[0];

    // 4) Просмотреть контейнер, используя для доступа к его элементам итераторы.
    std::cout << "Вывод данных вектора через итераторы: " << std::endl;
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << *it << '\t';
    }
    std::cout << std::endl;

    // 5) Создать второй контейнер этого же класса и заполнить его данными того же типа, что и
    // // первый контейнер.
    std::vector<int> second_vector = vector;
    std::cout << "Данные второго вектора: " << std::endl;
    for (const int item : second_vector)
    {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    // 6) Изменить первый контейнер, удалив из него n элементов после заданного и добавив
    // затем в него все элементы из второго контейнера.
    const std::size_t n = 3;
    vector.erase(vector.begin(), std::next(vector.begin(), 5));
    vector.insert(vector.end(), second_vector.begin(), second_vector.end());

    // 7) Просмотреть первый и второй контейнеры.
    std::cout << "Данные первого вектора: " << std::endl;
    for (const int item : vector)
    {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
    std::cout << "Данные второго вектора: " << std::endl;
    for (const int item : second_vector)
    {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    /*==================================================================
    ВТОРАЯ ЧАСТЬ
    ==================================================================*/

    // 1) Создать объект-контейнер и заполнить его данными.
    std::list<BankCard> list;
    read_list_of_cards_from_file(list);
    // 2) Просмотреть контейнер.
    std::cout << "Данные списка:" << std::endl;
    for (const BankCard& item : list) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    // 3) Изменить контейнер, удалив из него одни элементы и заменив другие.
    list.pop_back();
    *(++list.begin()) = *list.begin();

    // 4) Просмотреть контейнер, используя для доступа к его элементам итераторы.
    std::cout << "Вывод данных списка через итераторы: " << std::endl;
    for (std::list<BankCard>::iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << '\t';
    }
    std::cout << std::endl;

    // 5) Создать второй контейнер этого же класса и заполнить его данными того же типа, что и
    // первый контейнер.
    std::list<BankCard> second_list = list;
    std::cout << "Данные второго списка: " << std::endl;
    for (const BankCard& item : second_list)
    {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    // 6) Изменить первый контейнер, удалив из него n элементов после заданного и добавив
    // затем в него все элементы из второго контейнера.
    list.erase(list.begin(), std::next(list.begin(), 2));
    list.insert(list.end(), second_list.begin(), second_list.end());

    // 7) Просмотреть первый и второй контейнеры.
    std::cout << "Данные первого списка: " << std::endl;
    for (const BankCard& item : list)
    {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
    std::cout << "Данные второго списка: " << std::endl;
    for (const BankCard& item : second_list)
    {
        std::cout << item << '\t';
    }
    std::cout << std::endl;


    /*==================================================================
    ТРЕТЬЯ ЧАСТЬ
    ==================================================================*/

    // 1. Создать контейнер, содержащий объекты пользовательского типа.
    std::deque<BankCard> deque{ BankCard{"Иван Иванов", Date(20,10,2001), 34236, 349, 23000}, BankCard{"Даня Писечкин", Date(21,06,1999), 23534, 109, 15000}, BankCard{"Игорь Пупкин", Date(13,04,2008), 5490}, BankCard{("Василий Кошечкин"), Date(27,01,2004), 37566, 403, 45000} };

    // 2. Отсортировать его по убыванию элементов.
    std::sort(deque.begin(), deque.end(), [](const BankCard& firstBankCard, const BankCard& secondBankCard) { return firstBankCard.get_date() > secondBankCard.get_date(); });

    // 3. Просмотреть контейнер.
    std::cout << "Данные двухсторонней очереди: " << std::endl;
    for (const BankCard& item : deque) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
    // 4. Используя подходящий алгоритм, найти в контейнере элемент, удовлетворяющий
    // заданному условию.
    auto result = std::find_if(deque.begin(), deque.end(), [](const BankCard& bankCard) { return bankCard.get_date() < Date(01, 01, 1999) && bankCard.get_date() > Date(01, 01, 2010); });
    if (result != deque.end()) std::cout << *result << std::endl;
    else std::cout << "Элемент удовлетворяющий заданным условиям не найден!" << std::endl;
    std::cout << std::endl;
    // 5. Переместить элементы, удовлетворяющие заданному условию в другой
    // (предварительно пустой) контейнер.

    std::deque<BankCard> second_deque;
    second_deque.resize(std::count_if(deque.begin(), deque.end(), [](const BankCard& bankCard) { return bankCard.get_date() < Date(05, 05, 2003); }));
    std::remove_copy_if(deque.begin(), deque.end(), second_deque.begin(), [](const BankCard& bankCard) { return bankCard.get_date() < Date(05, 05, 2003); });

    // 6. Просмотреть второй контейнер.
    std::cout << "Данные второй двухсторонней очереди: " << std::endl;
    for (const BankCard& item : second_deque) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    // 7. Отсортировать первый и второй контейнеры по возрастанию элементов.
    std::sort(deque.begin(), deque.end());
    std::sort(second_deque.begin(), second_deque.end());

    // 8. Просмотреть их.
    std::cout << "После сортировки:\nДанные первой двухсторонней очереди: " << std::endl;
    for (const BankCard& item : deque) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
    std::cout << "Данные второй двухсторонней очереди: " << std::endl;
    for (const BankCard& item : second_deque) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    // 9. Получить третий контейнер путем слияния первых двух.
    std::deque<BankCard> third_deque;
    third_deque.resize(deque.size() + second_deque.size());
    std::merge(deque.begin(), deque.end(), second_deque.begin(), second_deque.end(), third_deque.begin());

    // 10. Просмотреть третий контейнер.
    std::cout << "Данные третьей двухсторонней очереди: " << std::endl;
    for (const BankCard& item : third_deque) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;

    // 11 Подсчитать, сколько элементов, удовлетворяющих заданному условию, содержит
    // третий контейнер.
    std::cout << std::count_if(third_deque.begin(), third_deque.end(), [](const BankCard& bankCard) { return bankCard.get_date() < Date(05, 05, 2003);
        });
    std::cout << std::endl;
    // 12. Определить, есть ли в третьем контейнере элемент, удовлетворяющий заданному
    // условию.
    std::cout << (std::find_if(third_deque.begin(), third_deque.end(), [](const BankCard& bankCard) { return bankCard.get_date() > Date(05, 06, 2004); }) == third_deque.end());
    std::cout << std::endl;
    return 0;
}