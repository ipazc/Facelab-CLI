//
// Created by ivan on 7/15/16.
//

#include <string.h>
#include <stdlib.h>
#include "InputAdapter.hpp"

string InputAdapter::adaptURI(string URI) {
    char *realPath = realpath(URI.c_str(), NULL);
    string strRealPath = string(realPath, strlen(realPath));
    free(realPath);

    return this->appendPaths(DEFAULT_BINDED_DIR, strRealPath);
}

string InputAdapter::appendPaths(string path1, string path2) {
    char separator = '/';
    string result = path1;

#ifdef _WIN32
    separator = '\\';
#endif

    cout << result << endl;
    if (path1[path1.length()-1] != separator
        && path2[0] != separator)
        result += separator;

    result += path2;

    return result;
}
