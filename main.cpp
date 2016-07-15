#include <iostream>
#include <getopt.h>
#include "src/global/config.hpp"
#include "src/exceptions/ConfigException.hpp"
#include "src/service_client/FaceAgeGenderStackServiceClient.hpp"
#include "src/result_adapter/Face.hpp"
#include "src/result_adapter/FaceResultAdapter.hpp"
#include "src/exceptions/AnalysisErrorException.hpp"

using namespace std;

int main() {
    try
    {
        HOST host = Config::getInstance().getHost(DEFAULT_STACK_SERVICE_SECTION);

        cout << "Host= " << host.ip << ":" << host.port << endl;
        cout << "Connecting to the service..." << endl;

        FaceAgeGenderStackServiceClient faceAgeGenderStackServiceClient(host);
        json result = faceAgeGenderStackServiceClient.analyzeUri("/home/ivan/init.jpg");
        cout << result << endl;
        FaceResultAdapter faceResultAdapter(result);
        cout << faceResultAdapter.toString() << endl;

        faceAgeGenderStackServiceClient.setEstimateAge(true);
        faceAgeGenderStackServiceClient.setEstimateGender(true);
        result = faceAgeGenderStackServiceClient.analyzeUri("/home/ivan/CvMlModule/samples/our-familly_original.jpg");
        cout << result << endl;
        FaceResultAdapter faceResultAdapter2(result);
        cout << faceResultAdapter2.toString() << endl;

        faceAgeGenderStackServiceClient.setEstimateAge(false);
        faceAgeGenderStackServiceClient.setEstimateGender(true);
        result = faceAgeGenderStackServiceClient.analyzeUri("/home/ivan/init.jpg");
        cout << result << endl;
        FaceResultAdapter faceResultAdapter3(result);
        cout << faceResultAdapter3.toString() << endl;

        result = faceAgeGenderStackServiceClient.analyzeUri("/home/ivan/inita.jpg");

        FaceResultAdapter faceResultAdapter4(result);
    }
    catch (ConfigException* configException)
    {
        cerr << "Error: " << configException->what() << endl;
    }
    catch (AnalysisErrorException* analysisErrorException)
    {
        cerr << "Error: " << analysisErrorException->what() << endl;
    }
    return 0;
}