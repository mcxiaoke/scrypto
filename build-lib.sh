#!/usr/bin/env bash
# @Author: mcxiaoke
# @Date:   2016-01-17 12:59:23
# @Last Modified by:   mcxiaoke
# @Last Modified time: 2016-01-17 13:00:48
ndk-build -C lib NDK_PROJECT_PATH=. NDK_APPLICATION_MK=Application.mk $@
