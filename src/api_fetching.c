/*
* @Author: karlosiric
* @Date:   2025-06-26 11:14:23
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-26 13:18:06
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
    free(api_data);

    return 0;
}

s_CovidData *parse_covid_csv(const char *csv_format) {
    s_CovidData *cd = malloc(sizeof(s_CovidData));
    if (!cd) {
        fprintf(stderr, "Failed to allocate enough space for the Covid Data container: %s\n", strerror(errno));
        return NULL;
    }

    cd->records = malloc(INITIAL_RECORDS_SIZE * sizeof(s_CovidRecord));
    if (!cd->records) {
        fprintf(stderr, "Failed to allocate enough space for memory for covid records: %s\n", strerror(errno));
        free(cd);
        return NULL;
    }

    cd->size = INITIAL_RECORDS_SIZE;
    cd->count = 0;

    if (cd->count >= cd->size) {
        size_t new_size = cd->size * 2;

        s_CovidRecord *new_records = realloc(cd->records, new_size * sizeof(s_CovidRecord));
        if (!new_records) {
            fprintf(stderr, "Reallocation of memory failed: %s\n", strerror(errno));
        }

        cd->records = new_records;
        cd->size = new_size;
    }












    // TODO: Not done yet now we need to parse that and store it into the records
    // cd->records[cd->count] =
    cd->count++;

}


s_CovidRecord parse_csv_line(const char *line) {
    s_CovidRecord record = {0};

    char *line_copy = strdup(line);
    char *field = strtok(line_copy, ",");
    int field_index = 0;

    while(field != NULL) {
        switch (field_index) {
            case 0: strncpy(record.fips, field, sizeof(record.fips) - 1); break;
            case 1: strncpy(record.admin2, field, sizeof(record.admin2) - 1); break;
            case 2: strncpy(record.province_state, field, sizeof(record.province_state) - 1); break;
            case 3: strncpy(record.country_region, field, sizeof(record.country_region) - 1); break;
            case 4: strncpy(record.last_update, field, sizeof(record.last_update) - 1); break;
            case 5: record.lat = atof(field); break;
            case 6: record.longitude = atof(field); break;
            case 7: record.confirmed = atoi(field); break;
            case 8: record.deaths = atoi(field); break;
            case 9: record.recovered = atoi(field); break;
            case 10: record.active = atoi(field); break;
            case 11: strncpy(record.combined_key, field, sizeof(record.combined_key) - 1); break;
            case 12: record.incident_rate = atof(field); break;
            case 13: record.case_fatality_ratio = atof(field); break;
        }   
        field = strtok(NULL, ",");
        field_index++;
    }

    free(line_copy);
    return record;
}

s_CovidData *create_covid_data(size_t initial_size) {
    s_CovidData *data = malloc(sizeof(s_CovidData));

    if (!data) {
        fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
        return NULL;
    }

    data->records = malloc(initial_size * sizeof(s_CovidRecord));

    if (!data->records) {
        fprintf(stderr, "Memory allocation failed for records: %s\n", strerror(errno));
        free_covid_data(data);
        return NULL;
    }

    data->size = initial_size;
    data->count = 0;
    return data;
}

void free_covid_data(s_CovidData *data) {
    if (data) {
        free(data->records);
        free(data);
        return ;
    }

    return ;
}
