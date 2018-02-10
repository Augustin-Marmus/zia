//
// Created by louis on 07/02/18.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE TestBoost

#include <boost/test/unit_test.hpp>
#include "Cgi.hpp"



BOOST_AUTO_TEST_CASE(TestingBoostCompilationCgi) {

    Cgi *cgi = new Cgi();
    zia::api::HttpDuplex httpDuplex;
    //cgi->exec(httpDuplex);
    BOOST_CHECK(cgi->exec(httpDuplex));
 }

