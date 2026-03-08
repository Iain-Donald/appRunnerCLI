#ifndef APP_RUNNER_HPP
#define APP_RUNNER_HPP

#include <string>
#include <vector>
#include <utility>
#include <map>
//#include <stdexcept>

class AppRunner
{
public:
    using Param = std::pair<std::string, std::string>;

    AppRunner(const std::string& file);

    void addApp(
        const std::string& appName, 
        const std::string& alias
    );
    void loadApps();

    std::string runApp(
        const std::string& application, 
        const std::vector<std::string>& params
    );

    bool knownApp (std::string appName);

private:

    struct App{
        std::string name;
        std::vector<std::string> aliases;
        std::vector<Param> parameters;
    };

    std::string dbFile;

    std::map<std::string, App> apps;
    //std::map<std::string, std::string> aliasLookup;

    void parseLine(const std::string& line, App*& currentApp);
    std::string runPlainString(const std::string& runString);
};

#endif