//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_CONFIGEXCEPTION_H
#define FACELAB_CONFIGEXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

using namespace std;


class ConfigException: public runtime_error {
public:

    ConfigException(string error)
            : runtime_error( error )
    {}

private:

};


#endif //FACELAB_CONFIGEXCEPTION_H
