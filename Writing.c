#include <stdio.h>
#include <stdlib.h>
#include "cJSON.c"

int main() {
    // Create a cJSON object
    cJSON *json = cJSON_CreateObject();
    if (!json) {
        fprintf(stderr, "Failed to create JSON object\n");
        return 1;
    }

    // Add a "name" field to the JSON object
    cJSON_AddStringToObject(json, "name", "Aditya");

    // Convert the cJSON object to a JSON string
    char *json_str = cJSON_Print(json);
    if (!json_str) {
        cJSON_Delete(json);
        fprintf(stderr, "Failed to convert JSON to string\n");
        return 1;
    }

    // Open a JSON file for writing
    FILE *file = fopen("output1.json", "w");
    if (!file) {
        cJSON_Delete(json);
        free(json_str);
        perror("Failed to create JSON file");
        return 1;
    }

    // Write the JSON string to the file
    fprintf(file, "%s\n", json_str);

    // Clean up and close the file
    fclose(file);
    cJSON_Delete(json);
    free(json_str);

    printf("JSON file created successfully.\n");

    return 0;
}

