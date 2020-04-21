# CMake generated Testfile for 
# Source directory: /p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests
# Build directory: /p/project/cjzam11/kitayama1/projects/nest-simulator/src/testsuite/selftests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(selftests/test_pass.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_pass.sli")
set_tests_properties(selftests/test_pass.sli PROPERTIES  _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;25;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_goodhandler.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_goodhandler.sli")
set_tests_properties(selftests/test_goodhandler.sli PROPERTIES  _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;25;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_lazyhandler.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_lazyhandler.sli")
set_tests_properties(selftests/test_lazyhandler.sli PROPERTIES  _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;25;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_fail.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_fail.sli")
set_tests_properties(selftests/test_fail.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;32;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_stop.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_stop.sli")
set_tests_properties(selftests/test_stop.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;32;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_badhandler.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_badhandler.sli")
set_tests_properties(selftests/test_badhandler.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;32;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_pass_or_die.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_pass_or_die.sli")
set_tests_properties(selftests/test_pass_or_die.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_assert_or_die_b.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_assert_or_die_b.sli")
set_tests_properties(selftests/test_assert_or_die_b.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_assert_or_die_p.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_assert_or_die_p.sli")
set_tests_properties(selftests/test_assert_or_die_p.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_fail_or_die.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_fail_or_die.sli")
set_tests_properties(selftests/test_fail_or_die.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_crash_or_die.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_crash_or_die.sli")
set_tests_properties(selftests/test_crash_or_die.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_failbutnocrash_or_die_crash.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_failbutnocrash_or_die_crash.sli")
set_tests_properties(selftests/test_failbutnocrash_or_die_crash.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_failbutnocrash_or_die_pass.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_failbutnocrash_or_die_pass.sli")
set_tests_properties(selftests/test_failbutnocrash_or_die_pass.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
add_test(selftests/test_passorfailbutnocrash_or_die.sli "/tmp/tmp1/bin/nest" "/tmp/tmp1/share/doc/nest/selftests/test_passorfailbutnocrash_or_die.sli")
set_tests_properties(selftests/test_passorfailbutnocrash_or_die.sli PROPERTIES  WILL_FAIL "TRUE" _BACKTRACE_TRIPLES "/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;41;add_test;/p/project/cjzam11/kitayama1/projects/nest-simulator/testsuite/selftests/CMakeLists.txt;0;")
