//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_INPUTADAPTER_H
#define FACELAB_INPUTADAPTER_H

#include <iostream>
#include <errno.h>
#include "../global/config.hpp"

using namespace std;

/**
 * Adapts the input to the understandable format for the Face + Age + Gender stack service daemon.
 */
class InputAdapter {
private:
    string appendPaths(string path1, string path2);
public:
    InputAdapter() {};

    string adaptURI(string URI);
};


#endif //FACELAB_INPUTADAPTER_H
