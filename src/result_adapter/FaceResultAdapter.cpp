//
// Created by ivan on 7/15/16.
//

#include "FaceResultAdapter.hpp"
#include "../exceptions/AnalysisErrorException.hpp"


FaceResultAdapter::FaceResultAdapter(json response) {

    if (response.count("error") > 0)
    {
        string error = response["error"];
        throw AnalysisErrorException(error);
    }
    json output = response["output"];

    int has_age = output.count("has_age") > 0;
    int has_gender = output.count("has_gender") > 0;

    if (has_age)
        output.erase("has_age");

    if (has_gender)
        output.erase("has_gender");
    json content = output["content"];

    Face* header = new Face("Face_ID", "Bounding_box", (has_age ? "Age_range" : ""), (has_gender ? "Gender" : ""));
    this->facesList.push_back(header);

    for (json::iterator it = content.begin(); it != content.end(); ++it) {
        json faceDescription = *it;

        string index = it.key();
        int coord0 = faceDescription[0][0];
        int coord1 = faceDescription[0][1];
        int coord2 = faceDescription[0][2];
        int coord3 = faceDescription[0][3];

        string bbox = "["+ to_string(coord0) + ", " + to_string(coord1) + ", " + to_string(coord2) + ", "
                      + to_string(coord3) + "]";
        string age = "";
        string gender = "";

        if (faceDescription.size() > 1 && has_age)
            age = faceDescription[1];
        else if (faceDescription.size() > 1 && has_gender)
            gender = faceDescription[1];

        if (faceDescription.size() > 2 && has_age && has_gender)
        {
            gender= faceDescription[2];
        }

        Face* face = new Face(index, bbox, age, gender);
        this->facesList.push_back(face);
    }
}

FaceResultAdapter::~FaceResultAdapter() {
    for (std::list<Face*>::const_iterator iterator = facesList.begin(), end = facesList.end(); iterator != end; ++iterator) {
        Face* face = *iterator;
        delete face;
    }
}

string FaceResultAdapter::toString() {
    string formattedResult = "";

    for (std::list<Face*>::const_iterator iterator = facesList.begin(), end = facesList.end(); iterator != end; ++iterator) {
        Face* face = *iterator;
        formattedResult += face->toString();
    }

    return formattedResult;
}
