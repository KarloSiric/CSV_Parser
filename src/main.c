/*
* @Author: karlosiric
* @Date:   2025-06-26 13:46:03
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-26 14:09:59
*/

#include "../include/data.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("Fetching COVID-19 Data Test Starting ... \n");

    const char *api_url = "https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/03-22-2020.csv";
    char *csv_data = NULL;
    printf("Fetching data from the API URL ... \n");
    int fetch_result = fetch_api_data(api_url, &csv_data);

    if (fetch_result != 0) {
        fprintf(stderr, "Failed to fetch appropriate data from the API url\n");
        return 1;
    }

    if (!csv_data) {
        fprintf(stderr, "No data received from the API\n");
        return 1;
    }

    printf("Data successfully fetched from the API\n");
    printf("Successfully fetched: %zu bytes\n", strlen(csv_data));

    printf("Parsing the CSV data ... \n");
    s_CovidData *covid_data = parse_covid_csv(csv_data);
    if (!covid_data) {
        fprintf(stderr, "Failed to parse CSV data\n");
        free(csv_data);
        return 1;
    }

    printf("CSV parsing completed successfully!\n");
    printf("Total records parsed: %zu\n", covid_data->count);

    printf("\n--- Printing 50 Records ---\n");
    int records_to_show = (covid_data->count) < 50 ? covid_data->count : 50;
    for (int i = 0; i < records_to_show; i++) {
        s_CovidRecord *record = &covid_data->records[i];
        printf("Record %d\n", i + 1);
        printf("   Location: %s, %s, %s\n",
            record->admin2, record->province_state, record->country_region);
        printf("   Confirmed: %d, Deaths: %d, Recovered: %d\n",
            record->confirmed, record->deaths, record->recovered);
        printf("  Last Update: %s\n\n", record->last_update);
    }

    printf("Cleaning up ... \n");
    free_covid_data(covid_data);
    free(csv_data);

    printf("Test completed successfully!");
    return (0);
}
