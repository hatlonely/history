#include <event.h>
#include <evhttp.h>
#include <iostream>
#include "hellowords.h"

HelloWords helloWords;

static void root_handler(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf;
    buf = evbuffer_new();
    const std::string& word = helloWords.helloWords();
    evbuffer_add(buf, word.c_str(), word.length());
    evhttp_add_header(req->output_headers, "Content-Type", "text/html; charset=UTF-8");
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

int main() {
    helloWords.addWords("../../data/one.txt", "one");
    struct evhttp *httpd;
    event_init();
    httpd = evhttp_start("0.0.0.0", 8080);
    evhttp_set_cb(httpd, "/", root_handler, NULL);
    event_dispatch();
    evhttp_free(httpd);
    return 0;
}
