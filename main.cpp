#include <iostream>
#include <string>
#include <vector>
#include <bitset>

int bit(int num) {
    int runner = 0;
    while (num) {
        num /= 2;
        runner++;
    }
    return runner;
}





bool is_correct_control_bit(std::string& code, int step) {
    int runner = step;
    int count = 0;
    while (runner <= code.size()) {
        for (int i = 0; i < step && runner + i <= code.size(); i++) {
            if (code[runner + i - 1] == '1') {
                count++;
            }
        }
        runner += step * 2;
    }
    if (count % 2 == 0)
        return true;
    return false;
}


std::string encode(std::string& origin) {
    std::string decode = "";
    int count_control_bits = 0;
    for (int i = 1; i <= origin.size() + count_control_bits; i++) {
        if (i & (i - 1))
            decode += origin[i - 1 - count_control_bits];
        else {
            decode += "x";
            count_control_bits++;
        }
    }
    for (int i = 1; i <= decode.size(); i *= 2) {
        if ((i & (i - 1)) == 0) {
            if (is_correct_control_bit(decode, i))
                decode[i - 1] = '0';
            else
                decode[i - 1] = '1';
        }
    }
    return decode;
}

std::string decode(std::string& code) {
    std::string origin = "";
    std::vector<int> control_bits;
    int incorrect_bit = NULL;
    for (int i = 1; i <= code.size(); i++) {
        if (i & (i - 1)) {
            origin += code[i - 1];
        }
        else {
            if (!is_correct_control_bit(code, i)) {
                if (incorrect_bit == NULL)
                    incorrect_bit = 0;
                incorrect_bit += i;
            }
        }
    }
    if (incorrect_bit != NULL && (incorrect_bit & (incorrect_bit - 1)) != 0) {
        int pre_bits = bit(incorrect_bit);
        if (origin[incorrect_bit - pre_bits - 1] == '0')
            origin[incorrect_bit - pre_bits - 1] = '1';
        else
            origin[incorrect_bit - pre_bits - 1] = '0';
    }
    return origin;
}

int main() {
    setlocale(LC_ALL, "RUS");
    std::string code, result;
    int mode;
    std::cout << "Введите что вы хотите сделать: закодировать(1) или декодировать(2) кодом Хеминга:    ";
    std::cin >> mode;
    switch (mode) {
        case 1:
            std::cout << "Введите исходное сообщение:    ";
            std::cin >> code;
            result = encode(code);
            std::cout << "Ваше закодированное сообщение:    " << result << "\n";
            break;
        case 2:
            std::cout << "Введите исходное сообщение:    ";
            std::cin >> code;
            result = decode(code);
            std::cout << "Ваше раскодированное сообщение:    " << result << "\n";
            break;
        default:
            std::cout << "Вы ввели что-то не то. Пока";
            break;
    }
}
