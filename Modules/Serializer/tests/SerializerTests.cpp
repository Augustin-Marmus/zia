//
// Created by Elias Demnati on 10/02/2018.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE TestSerializer

#include <boost/test/unit_test.hpp>
#include "Serializer.hpp"
BOOST_AUTO_TEST_SUITE( requests )

BOOST_AUTO_TEST_CASE(get_request_no_body) {
        Serializer* srlz = new Serializer();
        std::string raw_resq = "GET / HTTP/1.1\nHost: 127.0.0.1:1337\nConnection: keep-alive\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\nUpgrade-Insecure-Requests: 1\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\nAccept-Encoding: gzip, deflate, br\nAccept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7";
        zia::api::HttpDuplex duplex;
        for (auto it: raw_resq) {
          duplex.raw_req.push_back(static_cast<std::byte>(it));
        }
        BOOST_CHECK(srlz->exec(duplex));
}

BOOST_AUTO_TEST_CASE(post_request_with_body) {
        Serializer* srlz = new Serializer();
        std::string raw_resq = "POST / HTTP/1.1\nHost: localhost:1337\nConnection: keep-alive\nContent-Length: 29\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\nCache-Control: no-cache\nOrigin: chrome-extension://fhbjgbiflinjbdggehcddcbncdddomop\nContent-Type: text/plain;charset=UTF-8\nAuthorization: Bearer 8f6108c77fbb469c55f1c2c5c3e688f175146612\nPostman-Token: a5e48fc9-1d41-6fa2-74eb-321d8816eeec\nAccept: */*\nAccept-Encoding: gzip, deflate, br\,Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7\n\nThis is the body of a request";
        zia::api::HttpDuplex duplex;
        for (auto it: raw_resq) {
          duplex.raw_req.push_back(static_cast<std::byte>(it));
        }
        BOOST_CHECK(srlz->exec(duplex));
}

BOOST_AUTO_TEST_CASE(request_with_no_mvu) {
        Serializer* srlz = new Serializer();
        std::string raw_resq = "Host: 127.0.0.1:1337\nConnection: keep-alive\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\nUpgrade-Insecure-Requests: 1\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\nAccept-Encoding: gzip, deflate, br\nAccept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7";
        zia::api::HttpDuplex duplex;
        for (auto it: raw_resq) {
          duplex.raw_req.push_back(static_cast<std::byte>(it));
        }
        BOOST_CHECK(!srlz->exec(duplex));
}

BOOST_AUTO_TEST_CASE(get_requestion_with_cgi_bin) {
      Serializer* srlz = new Serializer();
      std::string raw_resq = "GET /cgi-bin HTTP/1.1\nHost: localhost:1338\nConnection: keep-alive\nCache-Control: max-age=0\nUpgrade-Insecure-Requests: 1\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\nAccept-Encoding: gzip, deflate, br\nAccept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7\nCookie: csrftoken=5hmQlNwEcvMBa7i85RbpirK9RBjo4tXW";
      zia::api::HttpDuplex duplex;
      for (auto it: raw_resq) {
        duplex.raw_req.push_back(static_cast<std::byte>(it));
      }
      BOOST_CHECK(srlz->exec(duplex));
}

BOOST_AUTO_TEST_SUITE_END()
