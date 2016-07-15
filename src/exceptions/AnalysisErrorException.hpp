//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_ANALYSISERROREXCEPTION_H
#define FACELAB_ANALYSISERROREXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>


using namespace std;

class AnalysisErrorException: public runtime_error  {
public:

    AnalysisErrorException(string error)
    : runtime_error( error )
            {}

private:

};


#endif //FACELAB_ANALYSISERROREXCEPTION_H
