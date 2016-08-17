//
// Created by ivan on 7/15/16.
//

#include "config.hpp"
#include "../exceptions/ConfigException.hpp"

Config::Config()
{
    ini.SetUnicode();
    SI_Error rc = ini.LoadFile(CONFIG_FILE);

    if (rc < 0)
        throw ConfigException("Config file could not be accessed.");
}

HOST Config::getHost(string section) {

    string ipAddress = string(ini.GetValue(section.c_str(),
                                         "HOST", "127.0.0.1"));
    int port = stoi(string(ini.GetValue(section.c_str(),
                                           "PORT", "17616")));
    return HOST(ipAddress, port);
}

string Config::getDetectorTypeAsString(DETECTOR_TYPE detector_type) {
    string result;

    switch (detector_type)
    {
        case WEAK:
            result = "WEAK";
            break;
        case STRONG:
            result = "STRONG";
            break;
        default:
            result = "DEFAULT";
            break;
    }

    return result;
}

string Config::getDetectorProcessorAsString(DETECTOR_PROCESSOR detector_processor) {
    string result;

    switch (detector_processor)
    {
        case CPU:
            result = "CPU";
            break;
        case GPU:
            result = "GPU";
            break;
        default:
            result = "CPU";
            break;
    }

    return result;
}

string Config::getFaceDetectorSectionName() {
    return ini.GetValue(DEFAULT_SUBSYSTEM_SECTION,
                        string(getDetectorProcessorAsString(getDetectorProcessor()) +
                                       "_" + getDetectorTypeAsString(detectorType) + "_FACE_DETECTOR").c_str(), "none");
}

string Config::getAgeEstimatorSectionName() {
    return ini.GetValue(DEFAULT_SUBSYSTEM_SECTION,
                        string(getDetectorProcessorAsString(getDetectorProcessor()) +
                               "_" + getDetectorTypeAsString(detectorType) + "_AGE_ESTIMATOR").c_str(), "none");
}

string Config::getGenderEstimatorSectionName() {
    return ini.GetValue(DEFAULT_SUBSYSTEM_SECTION,
                        string(getDetectorProcessorAsString(getDetectorProcessor()) +
                               "_" + getDetectorTypeAsString(detectorType) + "_GENDER_ESTIMATOR").c_str(), "none");
}

void Config::setDetectorType(DETECTOR_TYPE detectorType) {
    this->detectorType = detectorType;
}

void Config::setProcessor(DETECTOR_PROCESSOR processor) {
    this->detectorProcessor = processor;
}

DETECTOR_PROCESSOR Config::getDetectorProcessor() {

    if (this->detectorProcessor == UNKNOWN)
    {
        string defaultProcessor = ini.GetValue("Options", "DEFAULT_PROCESSOR", "CPU");

        if (defaultProcessor == "CPU")
            this->detectorProcessor = CPU;
        else
            this->detectorProcessor = GPU;

    }

    return this->detectorProcessor;
}
