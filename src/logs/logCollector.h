
#include "error.h"

#include <optional>
#include <string>
#include <vector>


class LogCollector
{
 public:

    static void putError(Error error)
    {
        logs.push_back(error);
    }

    static std::vector<Error>& getErrors()
    {
        return logs;
    }

    static std::optional<std::string> getLastMessage()
    {
        if (logs.empty()) {
            return std::nullopt;
        }
        return message.at(logs.back());
    }

    static void clear()
    {
        logs.clear();
    }

private:

    inline static std::vector<Error> logs = {};

    inline static const std::map<Error, std::string> message =
    {
        { Error::NODE_NOT_EXISTS,  "Node does not exist" },
        { Error::ROUTE_NOT_EXISTS, "Route does not exists" }
    };
};

