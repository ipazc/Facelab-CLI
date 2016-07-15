//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_HOST_H
#define FACELAB_HOST_H

#include <iostream>

using namespace std;

struct HOST {
    HOST(string ip, int port) : ip(ip), port(port) {}
    string ip;
    int port;
};

#endif //FACELAB_HOST_H
