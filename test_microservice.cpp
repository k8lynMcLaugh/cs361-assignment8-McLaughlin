#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::string data(ptr, size * nmemb);
    std::cout << data << std::endl;
    return size * nmemb;
}

void send_post_form(const std::string& url, const std::string& form_data, const std::string& token = "") {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        if (!token.empty()) {
            headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, form_data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize curl." << std::endl;
    }
}

int main() {
    std::cout << "Registering user..." << std::endl;
    send_post_form("http://localhost:3000/hello", "name=User&email=user@example.com");

    std::cout << "Logging in..." << std::endl;
    send_post_form("http://localhost:3000/hello", "name=User&email=user@example.com");

    std::cout << "Assigning role..." << std::endl;
    // Your backend probably doesn't handle roles on /hello, but you can try:
    send_post_form("http://localhost:3000/hello", "userId=12345&role=Coach", "<AUTH_TOKEN>");

    return 0;
}


