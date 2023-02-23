#pragma once
#include <array>
#include <assert.h>
#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <string>

#include <EMath.h>
#include <raylib.h>

#define AIAssert(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)