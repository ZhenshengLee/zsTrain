# 输出代码覆盖率

## 只使用gcov

```shell
# 使能lib.cmake中的 set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
# 使用vscode底部工具栏运行cmake test
cmake
make test
# gcov相关文件在 build\lib\CMakeFiles\logAnalyzer.dir\logAnalyzer.gcda
gcov ./lib/logAnalyzer.cpp --object-directory ./build/lib/CMakeFiles/logAnalyzer.dir
# 打开输出文件查看代码行的覆盖情况
```

## 使用lcov

上述方法麻烦，而且不直观，此处使用lcov生成代码覆盖率报表

```shell
./tools/lcov-1.13/bin/lcov --capture --directory ./build --output-file coverage.info
./tools/lcov-1.13/bin/genhtml  coverage.info --output-directory out
```

## 使用gcovr

lcov前端工具，将lcov和genhtml连起来用确实生成的HTML报告读起来很棒，行覆盖率、分支什么的都有，而且又能收集多个目标执行后的代码覆盖率，但是lcov生成的报告不能被Jenkins追踪，也没有覆盖率趋势。

```
pip install gcovr
gcovr --source-encoding utf-8 --root ./lib/ --object-directory D:/E_DISK/zsGit/zsCMake/build  -j6 --xml --output ./out/coverage.xml
gcovr --source-encoding utf-8 --root ./lib/ --object-directory D:/E_DISK/zsGit/zsCMake/build  -j6 --html --output ./out/coverage.html
gcovr --source-encoding utf-8 --root ./lib/ --object-directory D:/E_DISK/zsGit/zsCMake/build  -j6 --html-details --output ./out/coverage.html
```

