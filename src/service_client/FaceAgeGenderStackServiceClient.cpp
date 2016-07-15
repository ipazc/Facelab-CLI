//
// Created by ivan on 7/15/16.
//

#include "FaceAgeGenderStackServiceClient.hpp"

json FaceAgeGenderStackServiceClient::analyzeUri(string URI) {
    json request = this->buildRequest(URI);

    json returnedResponse = this->serviceClient->send_request(request);

    return returnedResponse;
}

json FaceAgeGenderStackServiceClient::buildRequest(string URI) {
    json request = {};

    request["uri"] = URI;

    if (this->limitFaces != PARAMETER_UNSET)
        request["limit_faces"] = this->limitFaces;

    if (this->bboxExpansion != PARAMETER_UNSET)
        request["bbox_expansion"] = this->bboxExpansion;

    if (this->estimateAge)
        request["estimate_age"] = this->estimateAge;

    if (this->estimateGender)
        request["estimate_gender"] = this->estimateGender;

    HOST faceHost = Config::getInstance().getHost(DEFAULT_FACE_DETECTION_SERVICE_SECTION);
    HOST ageHost = Config::getInstance().getHost(DEFAULT_AGE_ESTIMATION_SERVICE_SECTION);
    HOST genderHost = Config::getInstance().getHost(DEFAULT_GENDER_ESTIMATION_SERVICE_SECTION);

    request["face_detector"] = {{"host", faceHost.ip}, {"port", faceHost.port}};
    request["age_estimator"] = {{"host", ageHost.ip}, {"port", ageHost.port}};
    request["gender_estimator"] = {{"host", genderHost.ip}, {"port", genderHost.port}};

    // This is a pending feature that is working in the face detector service daemon and may be useful in the future.
    //if (this->drawAtUri)
    //    request["destUri"] = draw_at_uri

    return request;
}
