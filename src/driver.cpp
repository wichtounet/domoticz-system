//=======================================================================
// Copyright (c) 2015-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

#include <string>
#include <cstring>

#include <unistd.h>

namespace {

double read_system_temperature(){
    std::ifstream is("/sys/class/thermal/thermal_zone0/temp");
    std::string line;
    std::getline(is, line);
    int value = std::atoi(line.c_str());
    return value / (double)1000;
}

} //End of anonymous namespace

int main(){
    // Send data to the server continuously
    while(true){
        double value = read_system_temperature();

        std::string base_url = "http://192.168.20.140:8066/json.htm?";

        auto command = base_url + "type=command&param=udevice&idx=1&nvalue=0&svalue=" + std::to_string(value);

        system(("curl -s \"" + command + "\" > /dev/null").c_str());

        // Wait some time before messages
        usleep(5 * 1000 * 1000);
    }

    return 0;
}
