//
// Created by ivan on 7/15/16.
//

#include "Face.hpp"

string Face::toString()
{
    std::ostringstream oss;

    oss << left << setw(12) << this->index <<
           setw(32) << this->boundingBox;

    if (!this->age.empty())
        oss << setw(12) << this->age;

    if (!this->gender.empty())
        oss << setw(10) << this->gender;

    oss << endl;

    return oss.str();
}
