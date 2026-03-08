#include "appRunner.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stdexcept>

#include <cstdio>

AppRunner::AppRunner(const std::string& file): dbFile(file){}

void AppRunner::addApp(const std::string& appName, const std::string& alias)
{
    std::ofstream file(dbFile, std::ios::app);

    file << "#" << appName << "\n";
    file << "+" << alias << "\n";

    file.close();
}

void AppRunner::parseLine(const std::string& line, App*& currentApp)
{
    if(line.empty()) return;

    if(line[0] == '#'){
        std::string name = line.substr(1);

        App app;
        app.name = name;

        apps[name] = app;
        currentApp = &apps[name];

        //aliasLookup[name] = name;
    }
    else if(line[0] == '+'){
        if(!currentApp) return;

        std::string alias = line.substr(1);

        currentApp->aliases.push_back(alias);
        //aliasLookup[alias] = currentApp->name;
    }
    else if(line[0] == '<'){
        if(!currentApp) return;

        size_t comma = line.find(',');
        size_t end = line.find('>');

        if(comma == std::string::npos || end == std::string::npos)
            return;

        std::string param = line.substr(1, comma - 1);
        std::string type = line.substr(comma + 1, end - comma - 1);

        currentApp->parameters.push_back({param, type});
    }
}

void AppRunner::loadApps()
{
    std::ifstream file(dbFile);
    if(!file) return; // add throw here

    apps.clear();

    App* currentApp = nullptr;
    std::string line;
    while(std::getline(file, line))
        parseLine(line, currentApp);
}

bool AppRunner::knownApp (std::string appName) {
    /*if(aliasLookup.count(appName)) {
        appName = aliasLookup[appName];
    }*/
    return apps.count(appName) != 0;
}

std::string AppRunner::runApp(
    const std::string& appName,
    const std::vector<std::string>& params
)
{
    std::string paramString = appName + " ";
    for(std::string n : params)
            paramString += " " + n;

    

    std::string cliout;


    cliout = runPlainString(paramString); // use code below later to make the interface for known apps.

    /*App& app = apps[appName];
    //std::cout << "Running app: " << app.name << "\n";
    if (knownApp(appName)) 
        cliout = "knownAppRunGoesHere.";
    else {
        cliout = runPlainString(paramString);
        // add app to discoveredApps.txt and history.txt.
    }*/

    return cliout;
}

std::string AppRunner::runPlainString(const std::string& runString) {

    std::array<char, 128> buffer;
    std::string result;

    #ifdef _WIN32
        FILE* pipe = _popen(runString.c_str(), "r");
    #else
        FILE* pipe = popen(runString.c_str(), "r");
    #endif
        if (!pipe) throw std::runtime_error("popen() failed to open pipe for command: " + runString);

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr){
            std::cout << buffer.data();
            result += buffer.data();
        }
        
        if (result.empty()){
            std::cerr << "Command produced no output: " << runString << "\n";
        }

    #ifdef _WIN32
        int exitCode = _pclose(pipe);
    #else
        int exitCode = pclose(pipe);
    #endif
        if (exitCode != 0){
            std::cerr << "Command exited with non-zero status " << exitCode << "\n";
        }

        return result;
}

