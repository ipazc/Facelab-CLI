#include <iostream>
#include <boost/program_options.hpp>
#include "src/global/config.hpp"
#include "src/exceptions/ConfigException.hpp"
#include "src/service_client/FaceAgeGenderStackServiceClient.hpp"
#include "src/result_adapter/FaceResultAdapter.hpp"
#include "src/exceptions/AnalysisErrorException.hpp"
#include "src/input_adapter/InputAdapter.hpp"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char** argv) {

    try
    {
        bool estimateAge = false;
        bool estimateGender = false;
        int limitFaces = PARAMETER_UNSET;
        float bboxExpansion = PARAMETER_UNSET;

        po::options_description desc("Usage: facelab analyze URI [-a] [-g] [-x 0.8] [-l 3]\n\tExample: facelab analyze samples/image1.jpg -a\n\n Options", 1024, 512);
        desc.add_options()
                ("help,h",     "Show this help message and exit.")
                ("version,v",     "Show program's version number and exit.")
                ("estimate-age,a",   po::bool_switch(&estimateAge)->default_value(false),      "Estimate the age.")
                ("estimate-gender,g",   po::bool_switch(&estimateAge)->default_value(false),      "Estimate the gender.")
                ("limit-faces,l",   po::value<int>(&limitFaces)->default_value(PARAMETER_UNSET),             "Sets a limit in age/gender estimation. When this limit\n"
                        "is reached, no age/gender estimation algorithms are\n"
                        "applied. By default there is a limit of 3 faces.")
                ("bbox-expansion-proportion,x", po::value<float>(&bboxExpansion)->default_value(PARAMETER_UNSET), "Sets the proportion to expansion for bounding boxes.\n"
                        "The bounding box detected by the face detector may not\n"
                        "be big enough for age and gender estimation. By\n"
                        "default it is expanded in a 0.8 (80%).")
                ("input-file,i", po::value< vector<string> >(), "Input image to analyze.")
                ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                options(desc).positional(p).run(), vm);


        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return 0;
        }

        if (!vm.count("input-file"))
        {
            std::cout << desc << "\n";
            return 0;
        }
        // There must be an easy way to handle the relationship between the
        // option "help" and "host"-"port"-"config"
        // Yes, the magic is putting the po::notify after "help" option check
        po::notify(vm);


        HOST host = Config::getInstance().getHost(DEFAULT_STACK_SERVICE_SECTION);

        InputAdapter inputAdapter;

        vector<string> inputFiles = vm["input-file"].as< vector<string> >();

        FaceAgeGenderStackServiceClient faceAgeGenderStackServiceClient(host);


        faceAgeGenderStackServiceClient.setEstimateAge(estimateAge);
        faceAgeGenderStackServiceClient.setEstimateGender(estimateGender);
        faceAgeGenderStackServiceClient.setLimitFaces(limitFaces);
        faceAgeGenderStackServiceClient.setBoundingBoxExpansion(bboxExpansion);

        // Since multiple files may be the input, we are going to analyze them all.
        for (std::vector<string>::iterator it = inputFiles.begin() ; it != inputFiles.end(); ++it)
        {
            string adaptedURI = inputAdapter.adaptURI(*it);
            json result = faceAgeGenderStackServiceClient.analyzeUri(adaptedURI);
            FaceResultAdapter faceResultAdapter(result);
            cout << faceResultAdapter.toString() << endl;
        }
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