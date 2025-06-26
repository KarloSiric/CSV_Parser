#ifndef DATA_H
#define DATA_H 

#define INITIAL_RECORDS_SIZE            1000

#include <stddef.h>
typedef struct {
    char fips[10];                      // FIPS code (usually empty)
    char admin2[100];                   // county/admin level 2
    char province_state[100];           // state/province
    char country_region[100];           // country/region
    char last_update[30];               // last update timestamp
    double lat;                         // Latitude
    double longitude;                   // Longitude
    int confirmed;                      // confirmed cases
    int deaths;                         // deaths
    int recovered;                      // recovered cases    
    int active;                         // active cases still or not
    char combined_key[200];             // combined key for location
    double incident_rate;               // incident rate
    double case_fatality_ratio;         // case fatality ratio
} s_CovidRecord;

typedef struct {
    s_CovidRecord *records;
    size_t count;
    size_t size;
} s_CovidData;

typedef struct {
    char *fetched_data;
    size_t size;
} s_API_Data;

s_CovidData *create_covid_data(size_t initial_size);
void free_covid_data(s_CovidData *data);

static int write_data(void *buffer, size_t size, size_t nmemb, void *userp);
int fetch_api_data(const char *url, char **csv_response);
s_CovidData *parse_covid_csv(const char *csv_format);


#endif
