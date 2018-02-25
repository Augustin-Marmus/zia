//
// Created by Pierre-Alexandre Monneau on 17/02/2018.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE testLogger

#include <boost/test/unit_test.hpp>
#include "Logger.hpp"


BOOST_AUTO_TEST_CASE(test) {
        Logger* logger = new Logger();
        BOOST_CHECK(true);
}