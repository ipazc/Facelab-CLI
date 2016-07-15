//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_FACEAGEGENDERSTACKSERVICECLIENT_H
#define FACELAB_FACEAGEGENDERSTACKSERVICECLIENT_H

#include "ServiceClient.hpp"
#include "../../libs/json.hpp"
#include "../global/config.hpp"

#include <iostream>

using namespace std;
using namespace nlohmann;

enum PARAMETER_SPECIAL_VALUES {
    PARAMETER_UNSET = -99
};

class FaceAgeGenderStackServiceClient {
private:
    /**
     * Client for the service Face Age Gender stack.
     */
    ServiceClient *serviceClient;

    /**
     * Parameter expansion. Must be a float between 0 and 1.
     * The default expansion is 0.8, but take into mind that this parameter is handled by the daemon service
     * implementation and this default value may vary from version to version.
     */
    float bboxExpansion = PARAMETER_UNSET;

    /**
     * Limit faces ammount. This parameter is intended to establish a limit in the age and gender estimation (for
     * example when too much faces are detected and it is not wanted to waste time estimating age/gender on all of
     * the faces. When this limit is overpassed, the age and gender are disabled by the daemon.
     * The default limit is 3, but take into mind that this parameter is handled by the daemon service implementation
     * and this default value may vary from version to version.
     */
    int limitFaces = PARAMETER_UNSET;

    /**
     * Age estimation flag in order to make the daemon to perform age estimation too.
     */
    bool estimateAge = false;

    /**
     * Gender estimation flag in order to make the daemon to perform age estimation too.
     */
    bool estimateGender = false;

    /**
     * Builds the request for the daemon service.
     *
     * @param URI URI to send in order to analyze.
     * @return a JSON object with the request answered.
     */
    json buildRequest(string URI);

public:
    /**
     * Constructor of the stack service client.
     * It is established a connection to the service at the very beginning. The service daemon is prepared to work
     * with any amount of connections but a limited amount of requests. The excess of requests are going to be queued.
     */
    FaceAgeGenderStackServiceClient (string host, int port) { serviceClient = new ServiceClient(host, port); }
    FaceAgeGenderStackServiceClient (HOST wrappedHost) { serviceClient = new ServiceClient(wrappedHost.ip,
                                                                                           wrappedHost.port); }

    /**
     * Send the request to the daemon in order to Analyze the given URI to detect faces and estimate their age
     * and gender.
     */
    json analyzeUri(string URI);

    /**
     * Setter for limit_faces
     */
    void setLimitFaces(int limitFacesCount) { this->limitFaces = limitFacesCount; }
    void setBoundingBoxExpansion(float expansion) { this->bboxExpansion = expansion; }
    void setEstimateAge(bool enableEstimation) { this->estimateAge = enableEstimation; }
    void setEstimateGender(bool enableEstimation) { this->estimateGender = enableEstimation; }

    /**
     * Destructor of the stack service client.
     */
    ~FaceAgeGenderStackServiceClient() { delete serviceClient; }
};


#endif //FACELAB_FACEAGEGENDERSTACKSERVICECLIENT_H
