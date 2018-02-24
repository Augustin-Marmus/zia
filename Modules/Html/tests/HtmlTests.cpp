//
// Created by Elias Demnati on 10/02/2018.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE TestSerializer

#include <boost/test/unit_test.hpp>
#include "Html.hpp"

BOOST_AUTO_TEST_SUITE(html)

BOOST_AUTO_TEST_CASE(get_simple_file) {
  Html* html = new Html();
  zia::api::HttpDuplex http;
  zia::api::Conf conf;

  http.req.method = zia::api::http::Method::get;
  http.req.uri = "/index.html";
  html->config(conf);
  BOOST_CHECK(html->exec(http));
}

BOOST_AUTO_TEST_CASE(no_existing_file) {
  Html* html = new Html();
  zia::api::HttpDuplex http;
  zia::api::Conf conf;

  http.req.method = zia::api::http::Method::get;
  http.req.uri = "/titi.html";
  html->config(conf);
  BOOST_CHECK(!html->exec(http));
}


BOOST_AUTO_TEST_SUITE_END()
