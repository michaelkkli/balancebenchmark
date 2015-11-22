TESTS = src/test/success.test \
	src/test/popcountll.test \
	src/test/bal_heston_characteristic_lord2006-2.test \
	src/test/bal_heston_characteristic_lord2006-1.test \
	src/test/bal_mrg8-1.test \
	src/test/bal_mrg8-2.test \
	src/test/bal_mrg8-3.test \
	src/test/bal_pja_invnorm-1.test \
	src/test/bal_adaptive_lobatto_integrate-2.test \
	src/test/bal_adaptive_lobatto_integrate-1.test \
	src/test/bal_andersen_qe_minstore-1.test \
	src/test/bal_andersen_qe_minstore-2.test \
	src/test/xfail.test

XFAIL_TESTS = src/test/xfail.test

check_PROGRAMS = $(TESTS)

src_test_success_test_SOURCES = src/test/success.c
src_test_xfail_test_SOURCES = src/test/xfail.c

src_test_popcountll_test_SOURCES = src/test/popcountll.c

src_test_bal_mrg8_1_test_SOURCES = src/test/bal_mrg8-1.c src/bal_mrg8.c
src_test_bal_mrg8_1_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_mrg8_2_test_SOURCES = src/test/bal_mrg8-2.c src/bal_mrg8.c
src_test_bal_mrg8_2_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_mrg8_3_test_SOURCES = src/test/bal_mrg8-3.c src/bal_mrg8.c
src_test_bal_mrg8_3_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_pja_invnorm_1_test_SOURCES = src/test/bal_pja_invnorm-1.c src/bal_pja_invnorm.c src/bal_mrg8.c
src_test_bal_pja_invnorm_1_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_andersen_qe_minstore_1_test_SOURCES = src/test/bal_andersen_qe_minstore-1.c src/bal_andersen_qe_random_variates_init.c src/bal_andersen_qe_param_init.c src/bal_mrg8.c src/bal_andersen_qe_minstore.c src/bal_pja_invnorm.c
src_test_bal_andersen_qe_minstore_1_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_andersen_qe_minstore_2_test_SOURCES = src/test/bal_andersen_qe_minstore-2.c src/bal_andersen_qe_random_variates_init.c src/bal_andersen_qe_param_init.c src/bal_mrg8.c src/bal_andersen_qe_minstore.c src/bal_pja_invnorm.c
src_test_bal_andersen_qe_minstore_2_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_adaptive_lobatto_integrate_1_test_SOURCES = src/test/bal_adaptive_lobatto_integrate-1.c src/bal_adaptive_lobatto_init.c src/bal_adaptive_lobatto_integrate.c src/bal_adaptive_lobatto_resize.c
src_test_bal_adaptive_lobatto_integrate_1_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_adaptive_lobatto_integrate_2_test_SOURCES = src/test/bal_adaptive_lobatto_integrate-2.c src/bal_adaptive_lobatto_init.c src/bal_adaptive_lobatto_integrate.c src/bal_adaptive_lobatto_resize.c
src_test_bal_adaptive_lobatto_integrate_2_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_heston_characteristic_lord2006_1_test_SOURCES = src/test/bal_heston_characteristic_lord2006-1.c src/bal_heston_characteristic_lord2006.c src/bal_adaptive_lobatto_init.c src/bal_adaptive_lobatto_integrate.c src/bal_adaptive_lobatto_resize.c
src_test_bal_heston_characteristic_lord2006_1_test_CPPFLAGS = -I"$(srcdir)/src/include"

src_test_bal_heston_characteristic_lord2006_2_test_SOURCES = src/test/bal_heston_characteristic_lord2006-2.c src/bal_heston_characteristic_lord2006.c src/bal_adaptive_lobatto_init.c src/bal_adaptive_lobatto_integrate.c src/bal_adaptive_lobatto_resize.c
src_test_bal_heston_characteristic_lord2006_2_test_CPPFLAGS = -I"$(srcdir)/src/include"
