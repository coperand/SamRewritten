#include "Downloader.h"
#include "functions.h"
#include <curl/curl.h>
#include <thread>
#include <iostream>

Downloader*
Downloader::get_instance() {
    static Downloader me;
    return &me;
}

void 
Downloader::download_file(const std::string& file_url, const std::string& local_path) {
    //If the file exists, there's no need to download it again.
    //We assume the banners don't change

    if(!file_exists(local_path)) {
        CURL *curl;
        FILE *fp;
        CURLcode res;

        curl = curl_easy_init();
        if (curl) {
            fp = fopen(local_path.c_str(),"wb");

            if (fp == NULL)
            {
                std::cerr << "An error occurred downloading " << file_url  << " and saving it to ";
                std::cerr << local_path << std::endl;
                zenity("An error occurred downloading a file. Please report it to the developers!");
                exit(EXIT_FAILURE);
            }
            
            curl_easy_setopt(curl, CURLOPT_URL, file_url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            /* always cleanup */
            curl_easy_cleanup(curl);
            fclose(fp);

            //Erasing file if code is not 200
            long http_code = 0;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            if(http_code != 200)
                unlink(local_path.c_str());
        }
        else {
            std::cerr << "An error occurred creating curl. Please report it to the developers!" << std::endl;
            zenity("An error occurred creating curl. Please report it to the developers!");
            exit(EXIT_FAILURE);
        }

        if(res != 0) {
            std::cerr << "Curl errored with status " << res << ". (file: " <<  file_url << ")" << std::endl;
            zenity("An error occurred while fetching an icon, are you connected to the internet?");
            exit(EXIT_FAILURE);
        }
    }
}
