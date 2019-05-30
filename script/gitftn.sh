#!/bin/sh

DIRQUEUE+="build_make_tool& "
DIRQUEUE+="code/rosng&code "
DIRQUEUE+="code/pm_platform&code/pm "
DIRQUEUE+="code/tulip&code/tulip "
DIRQUEUE+="code/xtn/public&code/xtn "
DIRQUEUE+="code/xtn/bsp&code/xtn/bsp "
DIRQUEUE+="code/xtn/switchcard&code/xtn/switchcard "
DIRQUEUE+="code/xtn/cgel_kernel&code/xtn/bsp/kernel "
DIRQUEUE+="sdk3.0&code/xtn/switchcard/switchdrv/xgs/drv/bcmsdk/BcmSdkCode "
DIRQUEUE+="sdk4.0&code/xtn/switchcard/switchdrv/dune/drv/bcmsdk/BcmSdkCode "
DIRQUEUE+="code/xtn/firmware&code/firmware "
DIRQUEUE+="code/xtn/linecard&code/linecard "
DIRQUEUE+="code/xtn/pm_project&code/pm_project "
URLPATH="gerritro.zte.com.cn:29418"

help()
{
echo =========================================================================
echo gitftn.sh usage:
echo "    参数说明："
echo "    ./gitftn.sh 命令      路径              指定参数"
echo "         命令1:clone      \$Path             \$UserName"
echo "         命令2:reset      \$Path             \$Branch  "
echo "         命令3:setbranch  \$Path             \$Branch  "
echo "         命令4:getbranch  \$Path                       "
echo "         命令5:ln         \$Path                       "
echo "         命令6:\$Cmd       \$Path                      "
echo "  可选值：\$Branch:master,040,cmcc "
echo "          \$Cmd:   pull,status,..."
echo "  默认值：\$Path:  code  \$UserName:10172331  \$Branch:master"
echo "for example:"
echo "    gitftn.sh clone      code 10172331        #从gerrit下载代码"
echo "    gitftn.sh reset      code 040/master/cmcc #更新覆盖代码"
echo "    gitftn.sh setbranch  code 040/master/cmcc #切换分支"
echo "    gitftn.sh getbranch  code                 #获取分支号"
echo "    gitftn.sh ln         code                 #软连接"
echo "    gitftn.sh status     code                 #当前状态"
echo =========================================================================
exit

}

gitclone()
{
    for tmpdir in $DIRQUEUE
	do
		git clone ssh://"$PARAM_USER"@"$URLPATH"/FTN/${tmpdir%%&*} "$PARAM_PATH"/"${tmpdir#*&}"
		sleep 1
	done
	wait
    echo "UserName:${PARAM_USER}"
}

gitsetbranch()
{
    for tmpdir in $DIRQUEUE
	do
        echo "${PARAM_PATH}/${tmpdir#*&}"
        cd "$PARAM_PATH"/"${tmpdir#*&}"
        git checkout -f ${PARAM_BRANCH}
        cd "${CURRENT_PATH}"
		sleep 1
	done
	wait
    echo "Branch:${PARAM_BRANCH}"
}

gitgetbranch()
{
    for tmpdir in $DIRQUEUE
	do
        echo "${PARAM_PATH}/${tmpdir#*&}"
        cd "$PARAM_PATH"/"${tmpdir#*&}"
        git branch -a
        cd "${CURRENT_PATH}"
	done
	wait
}

gitreset()
{
    for tmpdir in $DIRQUEUE
	do
        echo "${PARAM_PATH}/${tmpdir#*&}"
        cd "$PARAM_PATH"/"${tmpdir#*&}"
        git checkout -f ${PARAM_BRANCH}
        git fetch --all
		git reset --hard origin/${PARAM_BRANCH}
        cd "${CURRENT_PATH}"
		sleep 1
	done
	wait
    echo "Branch:${PARAM_BRANCH}"
}

gitcmd()
{
    for tmpdir in $DIRQUEUE
	do
        echo "${PARAM_PATH}/${tmpdir#*&}"
        cd "$PARAM_PATH"/"${tmpdir#*&}"
        git ${PARAM_CMD}
        cd "${CURRENT_PATH}"
		sleep 1
	done
	wait
    echo "Cmd:${PARAM_CMD}"
}

: '
#整块注释
'
#软连接必须绝对路径
gitln()
{
    CODEPATH="$CURRENT_PATH/$PARAM_PATH"/code
    XTNPATH="$CODEPATH"/xtn
    rm -f "$XTNPATH"/boot
    rm -f "$XTNPATH"/epld
    rm -f "$XTNPATH"/fpga
    rm -f "$CODEPATH"/linecard/pm
    rm -f "$CODEPATH"/linecard/switchcard
    rm -f "$CODEPATH"/linecard/bsp
    rm -f "$XTNPATH"/linecard
    rm -f "$XTNPATH"/sc
    rm -f "$XTNPATH"/pm
    rm -f "$XTNPATH"/pmncp
    rm -f "$XTNPATH"/shmc

    ln -s "$CODEPATH"/firmware/boot 		"$XTNPATH"/boot
    ln -s "$CODEPATH"/firmware/epld 		"$XTNPATH"/epld
    ln -s "$CODEPATH"/firmware/fpga 		"$XTNPATH"/fpga
    ln -s "$CODEPATH"/pm_project/pm 		"$XTNPATH"/pm
    ln -s "$CODEPATH"/pm_project/pmncp 		"$XTNPATH"/pmncp
    ln -s "$CODEPATH"/pm_project/shmc 		"$XTNPATH"/shmc
    ln -s "$CODEPATH"/linecard/sc 			"$XTNPATH"/sc
    ln -s "$CODEPATH"/linecard/linecard 	"$XTNPATH"/linecard
    ln -s "$XTNPATH"/switchcard 			"$CODEPATH"/linecard/switchcard
    ln -s "$XTNPATH"/bsp 					"$CODEPATH"/linecard/bsp
    ln -s "$XTNPATH"/pm 					"$CODEPATH"/linecard/pm

}

gitchmod()
{
    chmod -R 751 "$PARAM_PATH"/build
    chmod -R 751 "$PARAM_PATH"/make
    chmod -R 751 "$PARAM_PATH"/tool
}

gitlog()
{
    for tmpdir in $DIRQUEUE
	do
        echo "${PARAM_PATH}/${tmpdir#*&}"
        cd "$PARAM_PATH"/"${tmpdir#*&}"
        git log --author="邓文博10090301" --since=2017-08-22 --pretty=tformat: --numstat >> ./gitlog.txt
        cd "${CURRENT_PATH}"
		sleep 1
	done
	wait
    echo "Cmd:${PARAM_CMD}"
}

PARAM_NUM=$#
PARAM_CMD="$1"
#PARAM_PATH="$2"
#PARAM_THIRD="$3"

#默认参数
PARAM_PATH="code"
PARAM_USER="10172331"
PARAM_BRANCH="master"
CURRENT_PATH=`pwd`

#参数赋值
if [ "$PARAM_NUM" == 0 ]
then
	help
elif [ "$PARAM_NUM" == 2 ]
then
    PARAM_PATH="$2"
elif [ "$PARAM_NUM" == 3 ]
then
    PARAM_PATH="$2"
    if [ "$PARAM_CMD" = "clone" ]
    then
        PARAM_USER="$3"
    elif [ "$PARAM_CMD" = "reset" ] || [ "$PARAM_CMD" = "setbranch" ]
    then
        PARAM_BRANCH="$3"
    else
        help
    fi
fi

#对参数进行修补完整
if [[ "$PARAM_BRANCH" =~ "040" ]]
then
    PARAM_BRANCH="ftn_v1.00_040chip"
elif [[ "$PARAM_BRANCH" =~ "cmcc" ]]
then
    PARAM_BRANCH="ftn_v1.00_cmccTest"
fi


#处理命令
if [ "$PARAM_CMD" = "clone" ]
then
    gitclone
    gitln
    gitchmod
elif [ "$PARAM_CMD" = "reset" ]
then
    gitreset
    gitln
    gitchmod
elif [ "$PARAM_CMD" = "setbranch" ]
then
    gitsetbranch
elif [ "$PARAM_CMD" = "getbranch" ]
then
    gitgetbranch
elif [ "$PARAM_CMD" = "ln" ]
then
    gitln
    gitchmod
elif [ "$PARAM_CMD" = "log" ]
then
    gitlog
else
    gitcmd
fi













