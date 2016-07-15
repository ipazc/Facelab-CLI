//
// Created by ivan on 7/14/16.
//

#ifndef FACELAB_SERVICECLIENT_H
#define FACELAB_SERVICECLIENT_H

#include "../../libs/json.hpp"
#include "../../libs/zhelpers.hpp"

using namespace std;
using namespace nlohmann;

/**
 * Allows to perform a connection against a service and request an operation
 */
class ServiceClient {
private:
    /**
     * Holds the full URI of the server, including the protocol.
     */
    string address;

public:
    ServiceClient(string host, int port) : address("tcp://" + host + ":" + to_string(port)) {}

    /**
     * Sends the specified request to the service and returns a response.
     * If something went wrong, an exception is raised.
     *
     * @param   json_request    request to send to the service.
     * @return  json object with the response.
     */
    json send_request(json &json_request);

    ~ServiceClient() {}
};


#endif //FACELAB_SERVICECLIENT_H
