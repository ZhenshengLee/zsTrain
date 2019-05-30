#include "gmock/gmock.h"

class MockFileExtMgr : public FileExtMgr
{
public:
    MOCK_METHOD1(IsValid, bool(string filename));
};