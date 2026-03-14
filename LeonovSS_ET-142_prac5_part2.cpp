#include <iostream>
#include <string>

using std::string;

int is_digit(string str) {
    if (str.empty()) {
        return 0;
    }
    bool flag = 0;
    for (const char& ch : str) {
        short c = (short) ch;
        if (ch == '.' || ch == ',' || ch == '?' || ch == '!') {
            if (!flag) {
                flag = 1;
            } else {
                return 0;
            }
            continue;
        }
        if (!(c >= 48 && c <= 57)) {
            return 0;
        }
    }
    return 1;
}

/* 
    Функция проверяет, начинается ли переданная строка с заглавной кириллической буквы.
    В кодировке UTF-8 символы кодируются по-другому: два байта вместо одного (ascii)
    Поэтому str[i] выводит не символ, а только половину. Чтобы это исправить, требуется 
    специальная обработка.
    Функция берет первые два байта. Затем избавляется от заголовков:
    (в формате UTF-8 (кириллица) байты имееют структуру 110xxxxx10yyyyyy, то есть, из 16
    бит информативны лишь 11) первый байт избавляется от первых трех бит, второй - от двух.
    Далее байты склеиваются в одно число, значение которого проверяется по таблице UTF-8,
    где заглавные кириллические буквы находятся в диапазоне 0x410 - 0x42f или 1040 - 1071.
*/
int is_capitalized(string str) {
    
    if (str.empty()) {
        return 0;
    }
    unsigned char c1 = (unsigned  char) str[0];
    unsigned char c2 = (unsigned  char) str[1];
    int sym_code = ((c1 & 0x1f) << 6) + (c2 & 0x3f);
    return (sym_code >= 0x410 && sym_code <= 0x42f);
}

int ends_with_dot(string str) {
    if (str.empty()) {
        return 0;
    }
    return (str.back() == '.');
}

/*
    Будем считать так: 
    Название города - слово с заглавной буквы, не считая первых слов предложений. 
    Число магазинов в городе - число, идущее между названием города и концом предложения.
    Чек - число после слова "чек" (или любое другое число в предложении) кроме числа магазинов
*/
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    string s;
    getline(std::cin, s);
    //Текущий символ
    int current = 0;
    int next = s.find(' ', current);
    int n = s.size();
    string cur_s;
    // Помечает, что сейчас ищется: средний чек (-1), число магазинов (1) или ничего (0)
    short flag = 0; 
    bool skip = 1;
    while (next != -1) {
        cur_s = s.substr(current, next - current);
        if (is_capitalized(cur_s)) {
            if (skip) {
                skip = 0;
            } else {
                std::cout << cur_s << ": ";
                flag = 1;
            }
        } else if (cur_s.find("чек") != -1) {
            flag = -1; 
        } else if (is_digit(cur_s)) {
            if (flag == 1) {
                std::cout << cur_s << std::endl;
            }
            flag = 0;
        } else if (ends_with_dot(cur_s)) {
            if (cur_s != "р.") {
                 flag = 0;
                skip = 1;
            }
        }
        current = next + 1;
        next = s.find(' ', current + 1);
    }
    
    return 0;
}