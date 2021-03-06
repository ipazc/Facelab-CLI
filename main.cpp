#include <iostream>
#include <boost/program_options.hpp>
#include "src/global/config.hpp"
#include "src/exceptions/ConfigException.hpp"
#include "src/service_client/FaceAgeGenderStackServiceClient.hpp"
#include "src/result_adapter/FaceResultAdapter.hpp"
#include "src/exceptions/AnalysisErrorException.hpp"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char** argv) {

    try
    {
        bool estimateAge = false;
        bool estimateGender = false;
        bool weakDetector = false;
        bool strongDetector = false;
        bool gpuProcessor = false;
        bool cpuProcessor = false;
        int limitFaces = PARAMETER_UNSET;
        float bboxExpansion = PARAMETER_UNSET;

        po::options_description desc("Usage: facelab analyze URI [-a] [-g] [-x 0.8] [-l 3]\n\tExample: facelab analyze samples/image1.jpg -a\n\n Options", 1024, 512);
        desc.add_options()
                ("help,h",     "Show this help message and exit.")
                ("version,v",     "Show program's version number and exit.")
                ("estimate-age,a",   po::bool_switch(&estimateAge)->default_value(false),      "Estimate the age.")
                ("estimate-gender,g",   po::bool_switch(&estimateGender)->default_value(false),      "Estimate the gender.")
                ("weak,w",   po::bool_switch(&weakDetector)->default_value(false),      "Works with the weak version of the detectors if available.")
                ("strong,s",   po::bool_switch(&strongDetector)->default_value(false),      "Works with the strong version of the detectors if available.")
                ("cpu,c",   po::bool_switch(&cpuProcessor)->default_value(false),      "Works with the CPU version of the detectors if available. Can be combined with weak/strong flags.")
                ("gpu,p",   po::bool_switch(&gpuProcessor)->default_value(false),      "Works with the GPU version of the detectors if available. Can be combined with weak/strong flags.")
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
            std::cout << desc << endl;
            return 0;
        }

        if (vm.count("version"))
        {
            std::cout << VERSION << " " << BUILD_DATE << endl;
            return 0;
        }

        if (!vm.count("input-file"))
        {
            std::cout << "Error: no input file/s specified." << endl;
            return 0;
        }

        // There must be an easy way to handle the relationship between the
        // option "help" and "host"-"port"-"config"
        // Yes, the magic is putting the po::notify after "help" option check
        po::notify(vm);

        if (weakDetector)
            Config::getInstance().setDetectorType(WEAK);

        else if (strongDetector)
            Config::getInstance().setDetectorType(STRONG);

        else
            Config::getInstance().setDetectorType(DEFAULT);

        if (cpuProcessor)
            Config::getInstance().setProcessor(CPU);
        else if (gpuProcessor)
            Config::getInstance().setProcessor(GPU);

        HOST host = Config::getInstance().getHost(DEFAULT_STACK_SERVICE_SECTION);

        vector<string> inputFiles = vm["input-file"].as< vector<string> >();

        FaceAgeGenderStackServiceClient faceAgeGenderStackServiceClient(host);


        faceAgeGenderStackServiceClient.setEstimateAge(estimateAge);
        faceAgeGenderStackServiceClient.setEstimateGender(estimateGender);
        faceAgeGenderStackServiceClient.setLimitFaces(limitFaces);
        faceAgeGenderStackServiceClient.setBoundingBoxExpansion(bboxExpansion);


        // Since multiple files may be the input, we are going to analyze them all.
        for (std::vector<string>::iterator it = inputFiles.begin() ; it != inputFiles.end(); ++it)
        {
            json result = faceAgeGenderStackServiceClient.analyzeUri(*it);
            FaceResultAdapter faceResultAdapter(result);
            cout << faceResultAdapter.toString() << endl;
        }
    }
    catch (ConfigException configException)
    {
        cerr << "Error: " << configException.what() << endl;
    }
    catch (AnalysisErrorException analysisErrorException)
    {
        cerr << "Error: " << analysisErrorException.what() << endl;
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::program_options::invalid_command_line_syntax> > exception)
    {
        cerr << "Error: " << "Required argument is missing!" << endl;
    }

    return 0;
}