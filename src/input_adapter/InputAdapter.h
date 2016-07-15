//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_INPUTADAPTER_H
#define FACELAB_INPUTADAPTER_H

#include <iostream>
using namespace std;

class InputAdapter {
private:

public:
    InputAdapter() {};

    string adaptURI(string URI) {return URI_PREFIX + URI};
            
};


#endif //FACELAB_INPUTADAPTER_H
