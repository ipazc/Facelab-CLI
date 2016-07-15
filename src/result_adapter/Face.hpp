//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_FACE_H
#define FACELAB_FACE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

/**
 * Represents a face result.
 */
class Face {
private:
public:
    Face(string index, string boundingBox, string age, string gender)
            : index(index), boundingBox(boundingBox), age(age), gender(gender) { }

private:
    string index = "-1";
    string boundingBox = "";
    string age = "";
    string gender = "";

public:
    string toString();
};


#endif //FACELAB_FACE_H
