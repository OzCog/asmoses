#include "ListModulesRequest.h"

#include <opencog/atomspace/AtomSpace.h>
#include <opencog/atomspace/ClassServer.h>
#include <opencog/atomspace/types.h>
#include <opencog/server/CogServer.h>

using namespace opencog;

ListModulesRequest::ListModulesRequest()
{
}

ListModulesRequest::~ListModulesRequest()
{
    logger().debug("[ListModulesRequest] destructor");
}

bool ListModulesRequest::syntaxError()
{
    _error << "invalid syntax" << std::endl;
    sendError();
    return false;
}

bool ListModulesRequest::execute()
{
    CogServer& cogserver = static_cast<CogServer&>(server());

    std::string moduleList = cogserver.listModules();

    send(moduleList);

    return true;
}

void ListModulesRequest::sendError()
{
    if (_mimeType != "text/plain")
        throw RuntimeException(TRACE_INFO, "Unsupported mime-type: %s",
                _mimeType.c_str());
    send(_error.str());
}