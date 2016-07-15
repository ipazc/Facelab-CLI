cmake_minimum_required(VERSION 2.8.12.2)
project(FaceLab)

find_package(libzmq REQUIRED)
IF (LIBZMQ_FOUND)
    include_directories(${LIBZMQ_INCLUDE_DIRS})
    list(APPEND MORE_LIBRARIES ${LIBZMQ_LIBRARIES})
ELSE (LIBZMQ_FOUND)
    message( FATAL_ERROR "libzmq not found." )
ENDIF (LIBZMQ_FOUND)

set(CMAKE_BUILD_TYPE CMAKE_CXX_FLAGS_RELEASE)
set(CMAKE_C_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-stack-protector")

set(SOURCE_FILES main.cpp src/service_client/ServiceClient.cpp src/service_client/ServiceClient.hpp src/service_client/FaceAgeGenderStackServiceClient.cpp src/service_client/FaceAgeGenderStackServiceClient.hpp src/global/config.hpp libs/simpleini.hpp src/global/config.cpp src/global/config.hpp src/global/host.hpp src/exceptions/ConfigException.hpp libs/ConvertUTF.hpp libs/ConvertUTF.cpp src/result_adapter/Face.cpp src/result_adapter/Face.hpp src/result_adapter/FaceResultAdapter.cpp src/result_adapter/FaceResultAdapter.hpp src/exceptions/AnalysisErrorException.hpp src/input_adapter/InputAdapter.cpp src/input_adapter/InputAdapter.h)
set_source_files_properties(main.cpp PROPERTIES LANGUAGE CXX )

add_executable(FaceLab ${SOURCE_FILES})

target_link_libraries( FaceLab
        ${LIBZMQ_LIBRARIES}
)