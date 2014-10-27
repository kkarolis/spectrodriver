# -*- coding: utf-8 -*-
# vim: set filetype=python : #
import os
from SCons.Script import SConscript
from env_target import env_target
from env_test import env_test
from config import TEST_SRC_BUILD_DIR, TEST_BUILD_DIR, SRC_BUILD_DIR

# Python modules
from subprocess import call


# Run all tests
def run_tests(target, source, env):
    for src_f in source:
        call(src_f.abspath)
    return None


# Build source files
core_variant_syscalls = SConscript('lib/SConscript', duplicate=0,
                                   exports='env_target')
bin_main = SConscript('src/SConscriptTARGET', duplicate=0,
                      variant_dir=SRC_BUILD_DIR, exports=[
                          'env_target', 'core_variant_syscalls'])
env_target.AlwaysBuild(env_target.Alias('compile', bin_main))

# Upload to board
stty_refresh = env_target.AlwaysBuild(env_target.Alias(
    'stty_refresh', [], env_target['STTY_RULE']))
env_target.AlwaysBuild(env_target.Alias('upload', [bin_main, stty_refresh],
                                        env_target['BOSSAC_RULE']))

# Test sources
obj_unity = env_test.Object(os.path.join(TEST_BUILD_DIR, 'unity.o'), 'unity.c')
obj_src = SConscript('src/SConscriptHOST', variant_dir=TEST_SRC_BUILD_DIR,
                     duplicate=0, exports='env_test')
test_runners = SConscript('test/SConscript', variant_dir=TEST_BUILD_DIR,
                          duplicate=0,
                          exports=['env_test', 'obj_src', 'obj_unity'])
env_test.AlwaysBuild(env_test.Alias('test', test_runners, run_tests))
