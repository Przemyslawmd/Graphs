
#include "error.h"

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

    static void clear()
    {
        logs.clear();
    }

private:

    inline static std::vector<Error> logs = {};
};

