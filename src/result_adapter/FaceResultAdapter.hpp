//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_RESULTADAPTER_H
#define FACELAB_RESULTADAPTER_H

#include <iostream>
#include <list>
#include "../../libs/json.hpp"
#include "Face.hpp"

using namespace nlohmann;
using namespace std;

/**
 * Adapter for a Faceresult JSON
 */
class FaceResultAdapter {
private:
    // constructors used in the same order as described above:
    list<Face*> facesList;

public:
    FaceResultAdapter(json response);

    string toString();

    ~FaceResultAdapter();
};


#endif //FACELAB_RESULTADAPTER_H
