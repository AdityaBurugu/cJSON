#include <stdio.h>
#include <stdlib.h>
#include "cJSON.c"

int main() {
    // Open the JSON file for reading
    FILE *file = fopen("data.json", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Read the contents of the file into a string
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *json_str = (char *)malloc(file_size + 1);
    if (!json_str) {
        perror("Failed to allocate memory");
        fclose(file);
        return 1;
    }
    fread(json_str, 1, file_size, file);
    fclose(file);
    json_str[file_size] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse(json_str);
    if (!json) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        } else {
            fprintf(stderr, "Failed to parse JSON\n");
        }
        return 1;
    }

    // Access and manipulate JSON data as needed
    cJSON *name = cJSON_GetObjectItem(json, "Name");
    cJSON *date = cJSON_GetObjectItem(json, "Date");

    if (cJSON_IsString(name)) {
        printf("Name: %s\n", name->valuestring);
    }

    if (cJSON_IsNumber(date)) {
        printf("Date: %d\n", date->valueint);
    }

    // Don't forget to free allocated memory and clean up
    cJSON_Delete(json);

    return 0;
}
