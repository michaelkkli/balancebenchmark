TESTS = src/test/success.test src/test/xfail.test \
	src/test/popcountll.test \
	src/test/bal_mrg8-1.test \
	src/test/bal_mrg8-2.test 


XFAIL_TESTS = src/test/xfail.test

check_PROGRAMS = $(TESTS)

src_test_success_test_SOURCES = src/test/success.c
src_test_xfail_test_SOURCES = src/test/xfail.c

src_test_popcountll_test_SOURCES = src/test/popcountll.c

src_test_bal_mrg8_1_test_SOURCES = src/test/bal_mrg8-1.c src/bal_mrg8.c
src_test_bal_mrg8_1_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_mrg8_2_test_SOURCES = src/test/bal_mrg8-2.c src/bal_mrg8.c
src_test_bal_mrg8_2_test_CPPFLAGS = -I"$(srcdir)/src/include"
