#include <iostream>  
#include <fstream>   
#include <limits>    // Для получения минимального значения int

using namespace std;  // Используем пространство имен std

// Структура для представления узла бинарного дерева
struct Node {
    int status;       // Значение узла (в вашем случае - "status")
    Node* right;      // Указатель на правого потомка
    Node* left;       // Указатель на левого потомка

    // Конструктор для инициализации узла
    Node(int stat) : status(stat), right(nullptr), left(nullptr) {}
};

// Структура для представления бинарного дерева
struct List { 
    Node* head;       // Указатель на корень дерева

    // Конструктор для инициализации дерева (пустое дерево)
    List() : head(nullptr) {}

    // Функция для создания корня дерева
    Node* createHead(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        head = newNode;                   // Устанавливаем его как корень
        return head;                      // Возвращаем указатель на новый корень
    }

    // Функция для добавления левого потомка к узлу с заданным "status"
    void push_back_left(int value, int parent) {
        Node* newNode = new Node(value); // Создаем новый узел

        if (head == nullptr) {            // Если дерево пустое
            head = newNode;               // Новый узел становится корнем
            return;                       // Завершаем функцию
        }

        Node* parentNode = findNode(head, parent); // Ищем узел, к которому нужно добавить потомка

        if (parentNode != nullptr && parentNode->left == nullptr) { // Если узел-родитель найден и у него нет левого потомка
            parentNode->left = newNode;                             // Добавляем новый узел как левого потомка
        }
    }

    // Функция для добавления правого потомка к узлу с заданным "status"
    void push_back_right(int value, int parent) {
        Node* newNode = new Node(value); // Создаем новый узел

        if (head == nullptr) {            // Если дерево пустое
            head = newNode;               // Новый узел становится корнем
            return;                       // Завершаем функцию
        }

        Node* parentNode = findNode(head, parent); // Ищем узел, к которому нужно добавить потомка

        if (parentNode != nullptr && parentNode->right == nullptr) { // Если узел-родитель найден и у него нет правого потомка
            parentNode->right = newNode;                // Добавляем новый узел как правого потомка
        }
    }

    // Функция для поиска узла в дереве с заданным "status"
    Node* findNode(Node* head, int parent) {
        if (head == nullptr) {       // Если дерево пустое или дошли до конца ветки
            return nullptr;           // Узел не найден, возвращаем nullptr
        }

        if (head->status == parent) { // Если нашли узел с нужным "status"
            return head;            // Возвращаем указатель на этот узел
        }

        Node* foundNode = nullptr; // Инициализируем foundNode
        if (head->left != nullptr) {  // Добавляем проверку на nullptr // Если есть левый потомок
            foundNode = findNode(head->left, parent); // Ищем рекурсивно в левом поддереве
            if (foundNode != nullptr) {               // Если нашли в левом поддереве
                return foundNode;                    // Возвращаем найденный узел
            }
        }

        if (head->right != nullptr) { // Добавляем проверку на nullptr // Если есть правый потомок
            return findNode(head->right, parent); // Ищем рекурсивно в правом поддереве
        }
        return nullptr;
    }

    // Функция для поиска максимального значения во внутренних вершинах дерева
    int findMax(Node* head) {
        if (head == nullptr) {
            return numeric_limits<int>::min(); // Если дерево пустое, возвращаем минимальное значение
        }

        if (head->left == nullptr && head->right == nullptr) {
            return numeric_limits<int>::min(); //Если это лист, то возвращаем минимальное значение
        }

        int maxValue = head->status; // Значение текущего узла

        int leftMax = numeric_limits<int>::min(); // Максимальное значение в левом поддереве
        if (head->left != nullptr) {             // Если есть левый потомок
            leftMax = findMax(head->left);       // Рекурсивно ищем максимум в левом поддереве
        }

        int rightMax = numeric_limits<int>::min(); // Максимальное значение в правом поддереве
        if (head->right != nullptr) {              // Если есть правый потомок
            rightMax = findMax(head->right);        // Рекурсивно ищем максимум в правом поддереве
        }

        return max({ maxValue,leftMax, rightMax }); // Возвращаем максимум из текущего узла и поддеревьев
    }
};

int main() {
    List Tree;        // Создаем экземпляр класса List (бинарное дерево)
    int a, b, c, d;   // Переменные для хранения значений, считанных из файла или введенных пользователем
    int flag = 0;     // Флаг, указывающий, был ли создан корень дерева (0 - нет, 1 - да)
    int count = 0;    // Счетчик элементов, считанных из файла

    // Бесконечный цикл для выбора способа ввода информации
    while (1) {
        cout << "How would you like to enter information?" << endl; // Предлагаем пользователю выбор
        cout << "1-by yourself" << endl;  // Ввести данные вручную
        cout << "2-from file" << endl;     // Считать данные из файла

        // Считываем выбор пользователя
        cin >> d;  // Считываем выбор в переменную d

        // Проверка на ошибку ввода
        if (std::cin.fail()) {                                                  // Если cin находится в состоянии ошибки (например, введен текст вместо числа)
            std::cout << "Input error\n";                                       // Выводим сообщение об ошибке
            std::cin.clear();                                                   // Сбрасываем флаги ошибок cin (переводим cin в нормальное состояние)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода, игнорируя все символы до символа новой строки
            continue;                                                           // Переходим к следующей итерации цикла (запрашиваем ввод заново)
        }

        // Проверка корректности выбора (должен быть 1 или 2)
        if (d < 1 || d > 2) {  // Если введенное число меньше 1 или больше 2
            cout << "Input error" << endl;  // Сообщаем об ошибке
        }
        else {  // Если ввод корректен
            break;        // Выход из цикла, если ввод корректен
        }
    }

    if (d == 2) {  // Если пользователь выбрал ввод из файла (d == 2)
            /*10
             / \
            5   15
           / \  / \
          2  7 12 18
         /    /
        1    6*/

        ifstream in("text.txt");   // Открываем файл "text.txt" для чтения

        // Подсчитываем количество элементов в файле
        while (in >> a) {           // Читаем элементы из файла, пока не достигнем конца файла
            count++;                // Увеличиваем счетчик
        }
        in.close();                 // Закрываем файл

        // Проверяем, что количество элементов в файле соответствует ожидаемому формату (каждый узел требует 3 элемента, кроме корня)
        if (((count - 1) / 3) * 3 != (count - 1)) {  // Если (количество элементов - 1) не кратно 3
            cout << "Input error" << endl;      // Выводим сообщение об ошибке
            return 0;                          // Завершаем программу
        }

        ifstream fin("text.txt");   // Открываем файл "text.txt" для чтения

        // Считываем данные из файла и строим дерево
        for (int i = 0; i < count; i++) {  // Цикл по всем элементам в файле
            fin >> a;                  // Считываем текущий элемент
            if (flag == 0) {         // Если это первый элемент (корень дерева)
                Tree.createHead(a);    // Создаем корень дерева
                flag = 1;             // Устанавливаем флаг, что корень создан
            }
            else if (a == 0) {        // Если a равно 0 (добавить левого потомка)
                fin >> b;              // Считываем значение потомка
                i++;                  // Увеличиваем счетчик цикла
                fin >> c;              // Считываем значение родителя
                i++;                  // Увеличиваем счетчик цикла
                Tree.push_back_left(b, c); // Добавляем левого потомка
            }
            else if (a == 1) {        // Если a равно 1 (добавить правого потомка)
                fin >> b;              // Считываем значение потомка
                i++;                  // Увеличиваем счетчик цикла
                fin >> c;              // Считываем значение родителя
                i++;                  // Увеличиваем счетчик цикла
                Tree.push_back_right(b, c); // Добавляем правого потомка
            }
            else {                  // Если a не равно ни 0, ни 1
                cout << "Input error" << endl;  // Выводим сообщение об ошибке
            }
        }
        fin.close();                 // Закрываем файл
    }
    if(d == 1) {  // Если пользователь выбрал ввод данных вручную (d == 1)
        // Ввод корня дерева
            while (1) {  // Цикл для ввода значения корня (с обработкой ошибок)
                cout << "Enter root of the tree:" << endl;  // Запрос ввода корня
                cin >> a;                                   // Считываем значение корня
                if (std::cin.fail()) {                    // Если произошла ошибка ввода (например, ввели не число)
                    std::cout << "Input error\n";        // Сообщение об ошибке
                    std::cin.clear();                     // Сбрасываем флаги ошибок cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
                    continue;                             // Переходим к следующей итерации цикла (запрашиваем ввод заново)
                }
               else break;                                 // Если ввод успешен, выходим из цикла
            }
            Tree.createHead(a);           // Создаем корень дерева с введенным значением
            cout << "Instruction:" << endl;
            cout << "   Data should be entered like this:" << endl;
            cout << "   Should element be left or right?" << endl;
            cout << "   Enter 0 if left and 1 if right" << endl;
            cout << "   For example I'll enter 1, so program will create right element." << endl;
            cout << "   What data should that element consist of:" << endl;
            cout << "   For example I'll enter 5, so programm will create right 5 element." << endl;
            cout << "   Enter parent element:" << endl;
            cout << "   For example I'll enter 4, so programm create right 5 branch to element 4" << endl;
            cout << "   Or something like this:" << endl;
            cout << "   4" << endl;
            cout << "    \\" << endl;
            cout << "     5" << endl;
            while (1) {  // Цикл для ввода дочерних узлов (левых и правых)
                cout << "Should element be left or right?(Enter something other if you want to stop)" << endl; // Запрос ввода направления добавления
                cin >> a;                   // Считываем направление (0 - влево, 1 - вправо)

                if (std::cin.fail()) {                                                   // Если произошла ошибка ввода
                    std::cout << "Input error\n";                                        // Сообщение об ошибке
                    std::cin.clear();                                                    // Сбрасываем флаги ошибок cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очищаем буфер ввода
                    continue;                                                            // Переходим к следующей итерации цикла
                }

                if (a != 0 && a != 1) {  // Если ввод не 0 и не 1 (прекращаем ввод)
                    break;               // Выходим из цикла
                }

                cout << "What data should that element consist of:" << endl; // Запрос ввода значения дочернего узла
                cin >> b;                    // Считываем значение дочернего узла
                if (std::cin.fail()) {                                                   // Если произошла ошибка ввода
                    std::cout << "Input error\n";                                        // Сообщение об ошибке
                    std::cin.clear();                                                    // Сбрасываем флаги ошибок cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очищаем буфер ввода
                    continue;                                                            // Переходим к следующей итерации цикла
                }

                cout << "Enter parent element : " << endl; // Запрос ввода значения родительского узла
                cin >> c;                    // Считываем значение родительского узла
                if (std::cin.fail()) {                                                   // Если произошла ошибка ввода
                    std::cout << "Input error\n";                                        // Сообщение об ошибке
                    std::cin.clear();                                                    // Сбрасываем флаги ошибок cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очищаем буфер ввода
                    continue;                                                            // Переходим к следующей итерации цикла
                }

                if (a == 0) {                  // Если a равно 0 (добавить левого потомка)
                    Tree.push_back_left(b, c);  // Добавляем левого потомка
                }
                else if (a == 1) {             // Если a равно 1 (добавить правого потомка)
                    Tree.push_back_right(b, c); // Добавляем правого потомка
                }
                else {
                    break; //Не должно быть, так как это проверено выше
                }
            }
    }
    int g = Tree.findMax(Tree.head); // Вызываем findMax, передавая head.
    if (g == numeric_limits<int>::min()) {
        cout << "No iteranl nodes." << endl;
    }
    else {
        cout << "Max iternal node: " << g << endl;
    }
    return 0;
}