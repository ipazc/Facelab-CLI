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
