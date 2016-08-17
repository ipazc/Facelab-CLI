//
// Created by ivan on 7/15/16.
//

#ifndef FACELAB_CONFIG_H
#define FACELAB_CONFIG_H

#include <iostream>
#include <list>
#include "../../libs/simpleini.hpp"
#include "host.hpp"

#define VERSION "1.1.0"
#define BUILD_DATE "17 Aug 2016"
#define CONFIG_FILE "/etc/varpcore/facelab.conf"

#define DEFAULT_STACK_SERVICE_SECTION "FullStackService"
#define DEFAULT_SUBSYSTEM_SECTION "SubsystemServices"


using namespace std;

enum DETECTOR_TYPE
{
    DEFAULT = 0,
    WEAK = 1,
    STRONG = 2,
};

enum DETECTOR_PROCESSOR
{
    UNKNOWN = 0,
    CPU = 1,
    GPU = 2,
};

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

    DETECTOR_TYPE detectorType = DEFAULT;
    DETECTOR_PROCESSOR detectorProcessor = UNKNOWN;

    /**
     * Returns the detector type as a string.
     */
    string getDetectorTypeAsString(DETECTOR_TYPE detector_type);

    /**
     * Returns the detector processor as a string.
     */
    string getDetectorProcessorAsString(DETECTOR_PROCESSOR detector_processor);
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

    /**
     * Gets the face detector section name for the desired detector type.
     */
    string getFaceDetectorSectionName();

    /**
     * Gets the age estimator section name for the desired detector type.
     */
    string getAgeEstimatorSectionName();

    /**
     * Gets the gender estimator section name for the desired detector type.
     */
    string getGenderEstimatorSectionName();

    /**
     * Sets the detector type in order to get the appropriate section when requested.
     */
    void setDetectorType(DETECTOR_TYPE detectorType);

    /**
     * Sets the processor for the detectors (CPU or GPU)
     */
    void setProcessor(DETECTOR_PROCESSOR processor);

    /**
     * Returns the processor that must be used for the service.
     */
    DETECTOR_PROCESSOR getDetectorProcessor();
};

#endif //FACELAB_CONFIG_H
