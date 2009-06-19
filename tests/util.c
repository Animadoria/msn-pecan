/**
 * Copyright (C) 2007-2009 Felipe Contreras
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <check.h>

#include "pecan_util.h"

typedef struct {
    const char *in;
    const char *out;
} str_cmp_t;

START_TEST (test_url_decode)
{
    str_cmp_t a[] = {
        { "foobar", "foobar" },
        { "foo%24bar", "foo$bar" },
        { "%24%2b%3b%2f%3a%3d%3f%40", "$+;/:=?@" },
    };
    int i;
    for (i = 0; i < ARRAY_SIZE(a); i++) {
        char *r;
        r = pecan_url_decode (a[i].in);
        ck_assert_str_eq (r, a[i].out);
        g_free (r);
    }
}
END_TEST

START_TEST (test_html_unescape)
{
    str_cmp_t a[] = {
        { "foobar", "foobar" },
        { "foo&amp;bar", "foo&bar" },
        { "&amp;&lt;&gt;&nbsp;&copy;&reg;&quot;&apos;", "&<> ©®\"'" },
        { "WMP&#x5C;0Music&#x5C;01&#x5C;0&#x7B;0&#x7D; - &#x7B;1&#x7D;"
            "&#x5C;0#1 Zero&#x5C;0Audioslave&#x5C;0Out of Exile"
                "&#x5C;0&#x7B;1F475271-C147-4D64-975B-CFCAE886FDE5&#x7D;&#x5C;0",
            "WMP\\0Music\\01\\0{0} - {1}\\0#1 Zero\\0Audioslave\\0Out of Exile\\0{1F475271-C147-4D64-975B-CFCAE886FDE5}\\0" },
#if 0
        { "&#x04ZZ;", "&#x04ZZ;" },
        { "&foobar;", "&foobar;" },
#endif
    };
    int i;
    for (i = 0; i < ARRAY_SIZE(a); i++) {
        char *r;
        r = pecan_html_unescape (a[i].in);
        fail_if(!r, "malformed");
        ck_assert_str_eq (r, a[i].out);
        g_free (r);
    }
}
END_TEST

Suite *
util_suite (void)
{
    Suite *s = suite_create ("util");

    /* Core test case */
    TCase *tc_core = tcase_create ("Core");
    tcase_add_test (tc_core, test_url_decode);
    tcase_add_test (tc_core, test_html_unescape);
    suite_add_tcase (s, tc_core);

    return s;
}

int
main (void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = util_suite ();
    sr = srunner_create (s);
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);

    return (number_failed == 0) ? 0 : 1;
}