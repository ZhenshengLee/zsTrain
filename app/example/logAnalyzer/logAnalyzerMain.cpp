#include "public/common.h"

#include "logAnalyzer.h"

using namespace std;

int main()
{
    // 主调用程序代码
    FileExtMgr fileExtMgr;
    LogAnalyzer analyzer(&fileExtMgr);
    bool bStatus = analyzer.IsValidLogFileName("filewithbadextension.foo");
    printf("zs: the filename bStatus(%d)", bStatus);
    return 0;
}
