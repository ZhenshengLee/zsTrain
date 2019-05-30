#include <iomanip>

#include "public/common.h"

#include "helloWorld.h"

#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/sleep.h"
#include "log4cplus/layout.h"
#include "log4cplus/logger.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/loglevel.h"
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

int main()
{
    log4cplus::initialize();
    /* step 1: Instantiate an appender object */
    SharedAppenderPtr _append(new ConsoleAppender(false, true));
    _append->setName(LOG4CPLUS_TEXT("First"));

    /* step 2: Instantiate a layout object */
    // log4cplus::tstring pattern = LOG4CPLUS_TEXT("%d{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p %c{2} %%%x%% - %X{key} -
    // %m[%l]%n");
    log4cplus::tstring _pattern = LOG4CPLUS_TEXT("[%t_%p] - %m %n");
    std::auto_ptr<Layout> _layout(new PatternLayout(_pattern));

    /* step 3: Attach the layout object to the appender */
    // _append->setLayout(std::auto_ptr<Layout>(Layout *_layout = new log4cplus::SimpleLayout));
    _append->setLayout(_layout);

    /* step 4: Instantiate a logger object */
    Logger _root = Logger::getRoot();
    Logger _test = Logger::getInstance(LOG4CPLUS_TEXT("test"));

    // /* step 5: Attach the appender object to the logger */
    _root.addAppender(_append);

    // /* step 6: Set a priority for the logger */
    _root.setLogLevel(ALL_LOG_LEVEL);

    /* log activity */
    LOG4CPLUS_WARN(_root, "This is the FIRST log message...");
    sleep(1, 0);
    LOG4CPLUS_WARN(_root, "This is the SECOND log message...");
    LOG4CPLUS_WARN(_root, "This is a float: " << 1.2345f);
    // 初始化业务
    int radius;
    cout << "Please input the radius of the circle" << endl;
    cin >> radius;
    radius = 3;
    if (0 > radius)
    {
        LOG4CPLUS_FATAL(_root, "This is a fatal double: the radius is invalid" << radius);
        return -1;
    }
    zs zs_circle(radius);
    LOG4CPLUS_WARN(_root, "Hello, world");
    LOG4CPLUS_DEBUG(_root, "The radius is: " << radius);

    return 0;
}
