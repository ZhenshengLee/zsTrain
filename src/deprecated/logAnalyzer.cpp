#include "public/common.h"

#include "example/logAnalyzer.h"

// *****************************************************************************
// LogAnalyzer Implementation
// *****************************************************************************
using namespace std;

LogAnalyzer::LogAnalyzer(FileExtMgr* pFileExtMgr)
{
    m_pFileExtMgr = pFileExtMgr;
}

LogAnalyzer::~LogAnalyzer()
{
    m_pFileExtMgr = NULL;
}

bool LogAnalyzer::IsValidLogFileName(string filename)
{
    return m_pFileExtMgr->IsValid(filename);
}

// *****************************************************************************
// FileExtMgr Implementation
// *****************************************************************************
FileExtMgr::FileExtMgr()
{
}

FileExtMgr::~FileExtMgr()
{
}

bool FileExtMgr::IsValid(string filename)
{
    if (EndWith(filename, ".SLF") || EndWith(filename, ".slf"))
    {
        return true;
    }
    return false;
}

bool FileExtMgr::EndWith(string filename, string ext)
{
    // cout << "compare" << filename.length()-ext.length() << "and" << ext.length() "and" << ext;
    // todo: 使用日志系统管理输出
    if (0 == filename.compare(filename.length() - ext.length(), ext.length(), ext))
    {
        return true;
    }
    return false;
}
