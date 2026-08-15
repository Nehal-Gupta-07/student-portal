#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include <string>

namespace console {

void discardRestOfLine();
std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt, bool& ok);

}  // namespace console

#endif
