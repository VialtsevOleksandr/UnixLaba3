# Аналізатор коду на C++

Цей проєкт являє собою простий аналізатор коду на мові програмування C++, який використовує регулярні вирази для виявлення та підсвічування різних лексем у коді.

## Можливості
- Підсвічування чисел, рядків, символів, булевих значень, препроцесорних директив, бібліотек, коментарів, ключових слів, операторів, розділових знаків, функцій, ідентифікаторів і бібліотечних об'єктів.
- Збір та виведення інформації про знайдені лексеми (наприклад, кількість чисел, рядків, коментарів тощо).
- Підтримка кольорового виведення через ANSI коди.

## Лексеми та кольори
- **Числа**: Звичайні числа, числа з плаваючою точкою та шістнадцяткові числа — **зелений колір**.
```
 std::regex integer_pattern(R"(\b[-]?[0-9]+\b)")
 std::regex float_pattern(R"([-]?[0-9]+\.?[0-9]*)")
 std::regex hex_pattern(R"(0[xX][0-9a-fA-F]+)")
```
- **Рядки**: Рядкові значення в лапках — **жовтий колір**.
```
std::regex string_pattern(R"("(\\"|[^"])*")")
```
- **Символи**: Символьні літерали (наприклад, 'A') — **темно-оранжевий колір**.
```
std::regex char_pattern(R"('(\\['"tvrnafb\\]|[^'\\])')")
```
- **Булеві значення**: Літерали true і false — **світло-блакитний колір**.
```
std::regex boolean_pattern(R"(true|false)")
```
- **Препроцесорні директиви**: Команди препроцесора (наприклад, #include, #define) — **темно-бірюзовий колір**.
```
std::regex preprocessor_pattern(R"(#\s*(include|define|undef|ifdef|ifndef|if|elif|else|endif|error|warning|pragma))")
```
- **Бібліотеки**: Стандартні бібліотеки C++ та C — **світло-зелений колір**.
```
std::regex library_pattern(R"(<(algorithm|any|array|atomic|barrier|bit|bitset|cassert|ccomplex|cctype|cerrno|cfenv|cfloat|charconv|chrono|cinttypes|ciso646|climits|clocale|cmath|codecvt|compare|complex|concepts|condition_variable|coroutine|csetjmp|csignal|cstdarg|cstdbool|cstddef|cstdint|cstdio|cstdlib|cstring|ctgmath|ctime|cuchar|cwchar|cwctype|deque|exception|execution|filesystem|format|forward_list|fstream|functional|future|initializer_list|iomanip|ios|iosfwd|iostream|istream|iterator|latch|limits|list|locale|map|memory|memory_resource|mutex|new|numbers|numeric|optional|ostream|queue|random|ranges|ratio|regex|scoped_allocator|semaphore|set|shared_mutex|source_location|span|sstream|stack|stdexcept|stop_token|string|string_view|strstream|syncstream|system_error|thread|tuple|type_traits|typeindex|typeinfo|unordered_map|unordered_set|utility|valarray|variant|vector)>)")
std::regex c_library_pattern(R"(<(assert\.h|ctype\.h|errno\.h|fenv\.h|float\.h|inttypes\.h|limits\.h|locale\.h|math\.h|setjmp\.h|signal\.h|stdarg\.h|stddef\.h|stdint\.h|stdio\.h|stdlib\.h|string\.h|time\.h|uchar\.h|wchar\.h|wctype\.h|stdatomic\.h|complex\.h|tgmath\.h|iso646\.h|stdalign\.h|stdbool\.h)>)")
```
- **Коментарі**: Однорядкові та багаторядкові коментарі — **пурпуровий колір**.
```
std::regex single_line_comment_pattern(R"(//.*)")
std::regex multi_line_comment_pattern(R"(/\*[^*]*\*+([^/*][^*]*\*+)*/)")
```
- **Ключові слова**: Зарезервовані слова C++ — **синій колір**.
```
std::regex keyword_pattern(R"(\b(asm|auto|break|case|catch|char|class|const|continue|default|delete|do|double|else|enum|extern|float|for|friend|goto|if|inline|int|long|new|operator|private|protected|public|register|return|short|signed|sizeof|static|struct|switch|template|this|throw|try|typedef|union|unsigned|virtual|void|volatile|while|bool|string)\b)")
```
- **Оператори**: Логічні, арифметичні та інші оператори — **темно-сірий колір**.
```
std::regex operator_pattern(R"(==|!=|<=|>=|<|>|\?:|\+=|-=|\*=|\/=|%=|\+\+|--|&&|\|\||[-+*\/%=!&|^])")
```
- **Розділові знаки**: Розділові символи, такі як коми, дужки та крапки з комою — **блакитний колір**.
```
std::regex delimiter_pattern(R"([.,;~:(){}[\]])")
```
- **Функції**: Імена функцій — **світло-жовтий колір**.
```
std::regex function_pattern(R"([_A-Za-z][0-9A-Za-z_]*(?=\((([A-Za-z_][A-Za-z_0-9]*[*&]*[\s]+[A-Za-z_]+[A-Za-z_0-9]*)+|\))))")
```
- **Ідентифікатори**: Імена змінних і типів — **світло-сірий колір**.
```
std::regex identifier_pattern(R"(\b(bool|auto|char|class|double|struct|enum|typedef|template|int|union|wchar_t|long|unsigned|signed|void|string|float)\b\s+([a-zA-Z_][a-zA-Z0-9_]*)\b(?!\s*\())")
```
- **Бібліотечні об'єкти**: Стандартні об'єкти C++ (std, cout, endl) — **лавовий колір**.
```
std::regex library_object_pattern(R"(std|cout|cin|endl)")
```

## Як це працює

Функція analyzeCode отримує рядок з кодом на C++, розбиває його на лексеми за допомогою регулярних виразів і виводить код з підсвіченими лексемами. Кольори виводяться за допомогою ANSI кодів.
Програма також збирає статистику по знайденим лексемам і виводить їх після аналізу.

**Детальніше про основні етапи програми**
1. *Оголошення кольорів*
2. *Визначення регулярних виразів для аналізу коду*
3. *Оголошення векторів для зберігання знайдених лексем*
4. *Виконання алгоритму аналізу коду*: 
 Програма бере кожен фрагмент коду по черзі і перевіряє його на відповідність до одного з регулярних виразів. Якщо знаходиться відповідність, лексема виводиться з відповідним кольором, а також додається до відповідного вектора.
```
while (pos < code.size()) {
    std::string rest_code = code.substr(pos);

    if (std::regex_search(rest_code, match, float_pattern) && match.position() == 0) {
        std::cout << GREEN << match.str() << RESET;
        numbers.push_back(match.str());
    }
    else if (std::regex_search(rest_code, match, integer_pattern) && match.position() == 0) {
        std::cout << GREEN << match.str() << RESET;
        numbers.push_back(match.str());
    }
```
І так по всіх лексемах, якщо ж вираз не підпадає під жодну лексему виконується ось цей блок коду, який перевіряє, чи не являється знайдений об'єкт змінною, яку ми знайшли раніше. Якщо так, то фарбує як змінну, якщо ж ні, то фарбує в червоний колір як помилку.
```
else {
    bool is_identifier = false;
    for (const auto& id : identifiers) {
        std::regex id_usage_pattern("\\b" + id + "\\b");
        if (std::regex_search(rest_code, match, id_usage_pattern) && match.position() == 0) {
            std::cout << LIGHT_GRAY << match.str() << RESET;
            is_identifier = true;
            break;
        }
    }
    if (!is_identifier) {
        std::cout << RED << rest_code[0] << RESET;
        pos++;
        continue;
    }
}
```
5. *Видалення дублікатів з векторів лексем*
6. *Виведення векторів з знайденими лексемами*

## Приклад використання

```
int main() {
    std::string code = R"(
    #include <iostream>
    #include <string>
    #include <assert.h>
	class A {
	public:
		A() {
			std::cout << "Constructor" << std::endl;
		}
		~A() {
			std::cout << "Destructor" << std::endl;
		}
	};
    int main() {
        float x = 3.14;
        Simple(void a);
        std::string text = "Hello";
        std::string str = "Hello, world!";
        std::string strO = "String with a quote: \"inside\"";
        bool b = true;
        std::string str = "";
        char c = 'A';
        // This is a comment
        /* Multi-line comment */
        if (x > 0) {
            std::cout << text << std::endl;
        }
        return 0;
        ABDS
    }
    )";

    analyzeCode(code);
    return 0;
}
 ```

![image](https://github.com/user-attachments/assets/0ef21b6d-b2fd-4a50-b67c-7b563954daec)
