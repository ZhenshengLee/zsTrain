#pragma once

using namespace std;

// 前向声明的类，不能使用其方法
// 由于LogAnalyzer中包含该成员，而非指针，所以必须将fileExtMgr声明在前面
// 如果用指针的话就可以任意顺序定义类
// class FileExtMgr;

// *****************************************************************************
// CCpp11 declaration
// *****************************************************************************
class CCpp11
{
public:
    // CCpp11(FileExtMgr* pFileExtMgr);
    CCpp11();
    ~CCpp11();
    // 成员函数
    // bool IsValidLogFileName(string filename);

private:
    // 私有成员
    // FileExtMgr* m_pFileExtMgr;
    // 私有方法
};