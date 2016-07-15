//
// Created by ivan on 7/14/16.
//

#include "ServiceClient.hpp"

json ServiceClient::send_request(json &json_request)
{
    json response;

    // Create a new socket for each request
    zmq::context_t context(1);
    zmq::socket_t worker(context, ZMQ_DEALER);

    s_set_id(worker);

    worker.connect(this->address.c_str());

    // ==> Send the request
    s_send(worker, json_request.dump());

    // <== Get the response
    response = json::parse(s_recv(worker));

    worker.disconnect(this->address.c_str());

    return response;
}