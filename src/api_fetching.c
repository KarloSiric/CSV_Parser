/*
* @Author: karlosiric
* @Date:   2025-06-26 11:14:23
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-26 11:30:17
*/


#include "../include/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>

static int write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;

    s_API_Data *api_data = (s_API_Data *)userp;

    char *growing_data = realloc(api_data->fetched_data, api_data->size + total_size + 1);

    if (!growing_data) {
        perror("Memory reallocation failure!");
        return 0;
    }

    memcpy(growing_data + api_data->size, buffer, total_size);
    api_data->fetched_data = growing_data;
    api_data->size += total_size;
    api_data->fetched_data[api_data->size] = '\0';

    return total_size;
}

int fetch_api_data(const char *url, char **csv_response) {
    if (!csv_response) {
        fprintf(stderr, "Invalid API reponse pointer data: %s\n", strerror(errno));
        return -1;
    }

    s_API_Data *api_data = malloc(sizeof(s_API_Data));
    CURL *handle = curl_easy_init();
    if (!handle) {
        fprintf(stderr, "Failed to initialize CURL handle: %s\n", strerror(errno));
        free(api_data);
        return -1;
    }

    api_data->fetched_data = malloc(1);
    api_data->size = 0;

    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &api_data);

    CURLcode request = curl_easy_perform(handle);
    if (request != CURLE_OK) {
        fprintf(stderr, "CURL request failed: %s\n", curl_easy_strerror(request));
        curl_easy_cleanup(handle);
        free(api_data->fetched_data);
        free(api_data);
        return -1;
    }

    curl_easy_cleanup(handle);
    *csv_response = api_data->fetched_data;

    return 0;
}


