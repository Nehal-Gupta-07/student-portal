#ifndef HELP_H
#define HELP_H

#include <string>

class HelpService {
public:
    std::string formatAbout() const;
    std::string formatCommandList() const;
};

#endif
