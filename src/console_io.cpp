#include "console_io.h"

#include <iostream>
#include <limits>
#include <string>

namespace console {

void discardRestOfLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int readInt(const std::string& prompt, bool& ok) {
    std::cout << prompt;
    int value = 0;
    if (!(std::cin >> value)) {
        std::cin.clear();
        discardRestOfLine();
        ok = false;
        return 0;
    }
    discardRestOfLine();
    ok = true;
    return value;
}

}  // namespace console
