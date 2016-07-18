//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_CONFIG_H
#define FACELAB_CONFIG_H

#include <iostream>
#include <list>
#include "../../libs/simpleini.hpp"
#include "host.hpp"

#define CONFIG_FILE "/etc/varpcore/facelab.conf"

#define DEFAULT_STACK_SERVICE_SECTION "FullStackService"
#define DEFAULT_FACE_DETECTION_SERVICE_SECTION "FaceDetector"
#define DEFAULT_AGE_ESTIMATION_SERVICE_SECTION "AgeEstimator"
#define DEFAULT_GENDER_ESTIMATION_SERVICE_SECTION "GenderEstimator"

#define DEFAULT_BINDED_DIR "/media"

using namespace std;

class Config
{
public:
    static Config& getInstance()
    {
        static Config    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
private:
    CSimpleIniA ini;

    Config();                   // Private constructor

    // C++ 03
    // ========
    // Dont forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    //Config(Config const&);         // Don't Implement
    //void operator=(Config const&); // Don't implement

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
public:
    Config(Config const&)               = delete;
    void operator=(Config const&)       = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status

    /**
     * Retrieves a host from the config file.
     * It must be a valid section. For example, the 'FaceDetection' section is intended to point in the config file
     * to the FaceDetection service daemon.
     *
     * Config file should be located under /etc/varpcore/
     */
    HOST getHost(string section);
};

#endif //FACELAB_CONFIG_H
