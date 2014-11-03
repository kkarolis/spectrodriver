# -*- coding: utf-8 -*-
from SCons.Script import Repository, Environment
# Mount code directories
Repository(['#./vendor/ceedling/vendor/unity/src'])

CCCOM = '$CC -c $_CCCOMCOM $SOURCE -o $TARGET '
CPPPATH = ['#./vendor/ceedling/vendor/unity/src', '#./include']
CPPFLAGS = ['-std=c99', '-pedantic', '-Wall', '-DTEST']
UNITYHELPDIR = '#./vendor/ceedling/vendor/unity/auto'

env_test = Environment()
env_test.Append(
    UNITYHELPDIR=UNITYHELPDIR,
)

env_test.Replace(
    CCCOM=CCCOM,
    CPPPATH=CPPPATH,
    CPPFLAGS=CPPFLAGS,
)
