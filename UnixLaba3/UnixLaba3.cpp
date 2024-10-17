#include <iostream>
#include <regex>
#include <string>
#include <vector>

// ANSI codes for color
#define RESET   "\033[0m" 
#define RED     "\033[31m" //невідомі символи
#define GREEN   "\033[32m" //числа
#define YELLOW  "\033[33m" //стрінг
#define LIGHT_YELLOW "\033[93m" //функції
#define LIGHT_BLUE "\033[94m" //буліан
#define BLUE    "\033[34m" //зарезервовані слова
#define MAGENTA "\033[35m" //коментарі
#define CYAN    "\033[36m"// розділові знаки
#define DARK_CYAN "\033[96m" //препроцесор
#define LIGHT_GREEN "\033[92m" //бібліотеки
#define DARK_ORANGE "\033[38;5;208m" //чар
#define LAVA "\033[38;5;202m" //бібліотечні об'єкти
#define LIGHT_GRAY "\033[37m"// ідентифікатори
#define DARK_GRAY "\033[90m"//оператори


void analyzeCode(const std::string& code) {
    // Define regular expressions for different lexemes
    std::regex integer_pattern(R"(\b[-]?[0-9]+\b)");
    std::regex float_pattern(R"([-]?[0-9]+\.?[0-9]*)");
    std::regex hex_pattern(R"(0[xX][0-9a-fA-F]+)");
    std::regex string_pattern(R"("(\\"|[^"])*")");
    std::regex char_pattern(R"('(\\['"tvrnafb\\]|[^'\\])')");
    std::regex boolean_pattern(R"(true|false)");
    std::regex preprocessor_pattern(R"(#\s*(include|define|undef|ifdef|ifndef|if|elif|else|endif|error|warning|pragma))");
    std::regex library_pattern(R"(<(algorithm|any|array|atomic|barrier|bit|bitset|cassert|ccomplex|cctype|cerrno|cfenv|cfloat|charconv|chrono|cinttypes|ciso646|climits|clocale|cmath|codecvt|compare|complex|concepts|condition_variable|coroutine|csetjmp|csignal|cstdarg|cstdbool|cstddef|cstdint|cstdio|cstdlib|cstring|ctgmath|ctime|cuchar|cwchar|cwctype|deque|exception|execution|filesystem|format|forward_list|fstream|functional|future|initializer_list|iomanip|ios|iosfwd|iostream|istream|iterator|latch|limits|list|locale|map|memory|memory_resource|mutex|new|numbers|numeric|optional|ostream|queue|random|ranges|ratio|regex|scoped_allocator|semaphore|set|shared_mutex|source_location|span|sstream|stack|stdexcept|stop_token|string|string_view|strstream|syncstream|system_error|thread|tuple|type_traits|typeindex|typeinfo|unordered_map|unordered_set|utility|valarray|variant|vector)>)");
    std::regex c_library_pattern(R"(<(assert\.h|ctype\.h|errno\.h|fenv\.h|float\.h|inttypes\.h|limits\.h|locale\.h|math\.h|setjmp\.h|signal\.h|stdarg\.h|stddef\.h|stdint\.h|stdio\.h|stdlib\.h|string\.h|time\.h|uchar\.h|wchar\.h|wctype\.h|stdatomic\.h|complex\.h|tgmath\.h|iso646\.h|stdalign\.h|stdbool\.h)>)");
    std::regex single_line_comment_pattern(R"(//.*)");
    std::regex multi_line_comment_pattern(R"(/\*[^*]*\*+([^/*][^*]*\*+)*/)");
    std::regex keyword_pattern(R"(\b(asm|auto|break|case|catch|char|class|const|continue|default|delete|do|double|else|enum|extern|float|for|friend|goto|if|inline|int|long|new|operator|private|protected|public|register|return|short|signed|sizeof|static|struct|switch|template|this|throw|try|typedef|union|unsigned|virtual|void|volatile|while|bool|string)\b)");
    std::regex operator_pattern(R"(==|!=|<=|>=|<|>|\?:|\+=|-=|\*=|\/=|%=|\+\+|--|&&|\|\||[-+*\/%=!&|^])");
    std::regex delimiter_pattern(R"([.,;~:(){}[\]])");
    std::regex function_pattern(R"([_A-Za-z][0-9A-Za-z_]*(?=\((([A-Za-z_][A-Za-z_0-9]*[*&]*[\s]+[A-Za-z_]+[A-Za-z_0-9]*)+|\))))");
    std::regex identifier_pattern(R"(\b(bool|auto|char|class|double|struct|enum|typedef|template|int|union|wchar_t|long|unsigned|signed|void|string|float)\b\s+([a-zA-Z_][a-zA-Z0-9_]*)\b(?!\s*\())");
    std::regex library_object_pattern(R"(std|cout|cin|endl)");

    // Vectors to store found lexemes
    std::vector<std::string> numbers;
    std::vector<std::string> strings;
    std::vector<std::string> chars;
    std::vector<std::string> booleans;
    std::vector<std::string> preprocessor_directives;
    std::vector<std::string> libraries;
    std::vector<std::string> comments;
    std::vector<std::string> keywords;
    std::vector<std::string> operators;
    std::vector<std::string> delimiters;
    std::vector<std::string> functions;
    std::vector<std::string> identifiers;
    std::vector<std::string> library_objects;

    size_t pos = 0;
    std::smatch match;
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
        else if (std::regex_search(rest_code, match, hex_pattern) && match.position() == 0) {
            std::cout << GREEN << match.str() << RESET;
            numbers.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, string_pattern) && match.position() == 0) {
            std::cout << YELLOW << match.str() << RESET;
            strings.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, char_pattern) && match.position() == 0) {
            std::cout << DARK_ORANGE << match.str() << RESET;
            chars.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, boolean_pattern) && match.position() == 0) {
            std::cout << LIGHT_BLUE << match.str() << RESET;
            booleans.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, preprocessor_pattern) && match.position() == 0) {
            std::cout << DARK_CYAN << match.str() << RESET;
            preprocessor_directives.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, library_pattern) && match.position() == 0) {
            std::cout << LIGHT_GREEN << match.str() << RESET;
            libraries.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, c_library_pattern) && match.position() == 0) {
            std::cout << LIGHT_GREEN << match.str() << RESET;
            libraries.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, single_line_comment_pattern) && match.position() == 0) {
            std::cout << MAGENTA << match.str() << RESET;
            comments.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, multi_line_comment_pattern) && match.position() == 0) {
            std::cout << MAGENTA << match.str() << RESET;
            comments.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, identifier_pattern) && match.position() == 0) {
            std::string type = match[1]; 
            std::string identifier = match[2];
            keywords.push_back(match[1].str());
            identifiers.push_back(match[2].str());
            std::cout << BLUE << type << " " << LIGHT_GRAY << identifier << RESET;
        }
        else if (std::regex_search(rest_code, match, keyword_pattern) && match.position() == 0) {
            std::cout << BLUE << match.str() << RESET;
            keywords.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, operator_pattern) && match.position() == 0) {
            std::cout << DARK_GRAY << match.str() << RESET;
            operators.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, delimiter_pattern) && match.position() == 0) {
            std::cout << CYAN << match.str() << RESET;
            delimiters.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, function_pattern) && match.position() == 0) {
            std::cout << LIGHT_YELLOW << match.str() << RESET;
            functions.push_back(match.str());
        }
        else if (std::regex_search(rest_code, match, library_object_pattern) && match.position() == 0) {
			std::cout << LAVA << match.str() << RESET;
            library_objects.push_back(match.str());
		}
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
        pos += match.length();
    }
    
    auto removeDuplicates = [](std::vector<std::string>& vec) {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        };


    removeDuplicates(numbers);
    removeDuplicates(strings);
    removeDuplicates(chars);
    removeDuplicates(booleans);
    removeDuplicates(preprocessor_directives);
    removeDuplicates(libraries);
    removeDuplicates(comments);
    removeDuplicates(keywords);
    removeDuplicates(operators);
    removeDuplicates(delimiters);
    removeDuplicates(functions);
    removeDuplicates(identifiers);
    removeDuplicates(library_objects);

    // Output the collected lexemes
    std::cout << "\nFound numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }

    std::cout << "\nFound strings: ";
    for (const auto& str : strings) {
        std::cout << str << " ";
    }

    std::cout << "\nFound characters: ";
    for (const auto& ch : chars) {
        std::cout << ch << " ";
    }

    std::cout << "\nFound boolean values: ";
    for (const auto& b : booleans) {
        std::cout << b << " ";
    }

    std::cout << "\nFound preprocessor directives: ";
    for (const auto& pd : preprocessor_directives) {
        std::cout << pd << " ";
    }

    std::cout << "\nFound libraries: ";
    for (const auto& lib : libraries) {
        std::cout << lib << " ";
    }

    std::cout << "\nFound comments: ";
    for (const auto& com : comments) {
        std::cout << com << " ";
    }

    std::cout << "\nFound keywords: ";
    for (const auto& kw : keywords) {
        std::cout << kw << " ";
    }

    std::cout << "\nFound operators: ";
    for (const auto& op : operators) {
        std::cout << op << " ";
    }

    std::cout << "\nFound delimiters: ";
    for (const auto& del : delimiters) {
        std::cout << del << " ";
    }

    std::cout << "\nFound functions: ";
    for (const auto& func : functions) {
        std::cout << func << " ";
    }

    std::cout << "\nFound identifiers: ";
    for (const auto& id : identifiers) {
        std::cout << id << " ";
    }

    std::cout << "\nFound library objects: ";
    for (const auto& lo : library_objects) {
		std::cout << lo << " ";
	}
    
}

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

    std::string Info =
        "\033[31mRED\033[0m: unknown symbols\n"
        "\033[32mGREEN\033[0m: numbers\n"
        "\033[33mYELLOW\033[0m: strings\n"
        "\033[93mLIGHT_YELLOW\033[0m: functions\n"
        "\033[94mLIGHT_BLUE\033[0m: booleans\n"
        "\033[34mBLUE\033[0m: reserved words\n"
        "\033[35mMAGENTA\033[0m: comments\n"
        "\033[36mCYAN\033[0m: punctuation marks\n"
        "\033[96mDARK_CYAN\033[0m: preprocessor\n"
        "\033[92mLIGHT_GREEN\033[0m: libraries\n"
        "\033[38;5;208mDARK_ORANGE\033[0m: char type\n"
        "\033[38;5;202mLAVA\033[0m: library objects\n"
        "\033[37mLIGHT_GRAY\033[0m: identifiers\n"
        "\033[90mDARK_GRAY\033[0m: operators\n";

    std::cout << Info << std::endl;
    analyzeCode(code);
    return 0;
}
