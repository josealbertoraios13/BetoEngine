//
// Created by jose_alberto on 02/10/2025.
//

#ifndef BETOENGINE_LOGGER_H
#define BETOENGINE_LOGGER_H

#pragma once

#include <sstream>
#include <vector>

class Logger {
    public:
        template <typename... Args>
        static void PrintMessage(Args&&... args) {
            std::ostringstream oss;
            (oss << ... << args);
            logs.push_back(oss.str());
        }

        static std::vector<std::string> logs;
};

#endif //BETOENGINE_LOGGER_H