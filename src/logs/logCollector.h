
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
        { Error::NO_CONNECTION, "Connection does not exist" },
        { Error::NO_GRAPH,      "Graph does not exist" },
        { Error::NO_NODE,       "Node does not exist" },
        { Error::NO_ROUTE,      "Route does not exists" }
    };
};

