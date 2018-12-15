
/*******************************
 * 
 * @author Mr Dk.
 * @version 2018.12.15, Nanjing
 * 
 * *****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dkjson.h"

Status dkjson_init(dkJSON *json)
{
    if (json == NULL)
    {
        return STATUS_ERR;
    }
    dkjson_destroy(json);

    json->_dkjson_str = (char *) calloc(STR_INIT_SIZE, sizeof(char));

    if (json->_dkjson_str == NULL)
    {
        return STATUS_ERR;
    }

    json->_dkjson_capacity = STR_INIT_SIZE;
    strcat(json->_dkjson_str, "{");
    return STATUS_OK;
}

void dkjson_destroy(dkJSON *json)
{
    if (json->_dkjson_capacity > 0)
    {
        free(json->_dkjson_str);
        json->_dkjson_str = NULL;
        json->_dkjson_capacity = 0;
    }
    json->_dkjson_count = 0;

}

void dkjson_generate(dkJSON *json, char res[])
{
    strcpy(res, json->_dkjson_str);
    strcat(res, "}");
}

Status dkjson_put_string(dkJSON *json, char key[], char value[])
{
    if (json == NULL)
    {
        return STATUS_ERR;
    }

    // ...,"key":"value" -- strlen(former) + 6 bytes + strlen(key) + strlen(value)
    while ((long long unsigned int) (json->_dkjson_capacity - 1) <
            strlen(json->_dkjson_str) + 6 + strlen(key) + strlen(value))
    {
        char *reallocation = (char *) realloc(json->_dkjson_str, json->_dkjson_capacity * 2);
        if (reallocation == NULL)
        {
            return STATUS_ERR;
        }
        json->_dkjson_str = reallocation;
        json->_dkjson_capacity <<= 1;
    }

    if (json->_dkjson_count > 0)
    {
        strcat(json->_dkjson_str, ",");
    }
    strcat(json->_dkjson_str, "\"");
    strcat(json->_dkjson_str, key);
    strcat(json->_dkjson_str, "\":\"");
    strcat(json->_dkjson_str, value);
    strcat(json->_dkjson_str, "\"");
    json->_dkjson_count++;

    return STATUS_OK;
}

Status dkjson_put_int(dkJSON *json, char key[], int value)
{
    if (json == NULL)
    {
        return STATUS_ERR;
    }

    char value_str[16];
    sprintf(value_str, "%d", value);

    // ...,"key":value_str -- strlen(former) + 6 bytes + strlen(key) + strlen(value_str)
    while ((long long unsigned int) (json->_dkjson_capacity - 1) <
            strlen(json->_dkjson_str) + 4 + strlen(key) + strlen(value_str))
    {
        char *reallocation = (char *) realloc(json->_dkjson_str, json->_dkjson_capacity * 2);
        if (reallocation == NULL)
        {
            return STATUS_ERR;
        }
        json->_dkjson_str = reallocation;
        json->_dkjson_capacity <<= 1;
    }

    if (json->_dkjson_count > 0)
    {
        strcat(json->_dkjson_str, ",");
    }
    strcat(json->_dkjson_str, "\"");
    strcat(json->_dkjson_str, key);
    strcat(json->_dkjson_str, "\":");
    strcat(json->_dkjson_str, value_str);
    json->_dkjson_count++;

    return STATUS_OK;
}

Status dkjson_put_short(dkJSON *json, char key[], short value)
{
    return dkjson_put_int(json, key, (int) value);
}

Status dkjson_put_long(dkJSON *json, char key[], long long value)
{
    if (json == NULL)
    {
        return STATUS_ERR;
    }

    char value_str[64];
    sprintf(value_str, "%I64d", value);

    // ...,"key":value_str -- strlen(former) + 6 bytes + strlen(key) + strlen(value_str)
    while ((long long unsigned int) (json->_dkjson_capacity - 1) <
            strlen(json->_dkjson_str) + 4 + strlen(key) + strlen(value_str))
    {
        char *reallocation = (char *) realloc(json->_dkjson_str, json->_dkjson_capacity * 2);
        if (reallocation == NULL)
        {
            return STATUS_ERR;
        }
        json->_dkjson_str = reallocation;
        json->_dkjson_capacity <<= 1;
    }

    if (json->_dkjson_count > 0)
    {
        strcat(json->_dkjson_str, ",");
    }
    strcat(json->_dkjson_str, "\"");
    strcat(json->_dkjson_str, key);
    strcat(json->_dkjson_str, "\":");
    strcat(json->_dkjson_str, value_str);
    json->_dkjson_count++;

    return STATUS_OK;    
}

Status dkjson_put_float(dkJSON *json, char key[], float value)
{
    if (json == NULL)
    {
        return STATUS_ERR;
    }

    char value_str[64];
    sprintf(value_str, "%f", value);

    // ...,"key":value_str -- strlen(former) + 6 bytes + strlen(key) + strlen(value_str)
    while ((long long unsigned int) (json->_dkjson_capacity - 1) <
            strlen(json->_dkjson_str) + 4 + strlen(key) + strlen(value_str))
    {
        char *reallocation = (char *) realloc(json->_dkjson_str, json->_dkjson_capacity * 2);
        if (reallocation == NULL)
        {
            return STATUS_ERR;
        }
        json->_dkjson_str = reallocation;
        json->_dkjson_capacity <<= 1;
    }

    if (json->_dkjson_count > 0)
    {
        strcat(json->_dkjson_str, ",");
    }
    strcat(json->_dkjson_str, "\"");
    strcat(json->_dkjson_str, key);
    strcat(json->_dkjson_str, "\":");
    strcat(json->_dkjson_str, value_str);
    json->_dkjson_count++;

    return STATUS_OK;
}

Status dkjson_put_double(dkJSON *json, char key[], double value)
{
    if (json == NULL)
    {
        return STATUS_ERR;
    }

    char value_str[64];
    sprintf(value_str, "%lf", value);

    // ...,"key":value_str -- strlen(former) + 6 bytes + strlen(key) + strlen(value_str)
    while ((long long unsigned int) (json->_dkjson_capacity - 1) <
            strlen(json->_dkjson_str) + 4 + strlen(key) + strlen(value_str))
    {
        char *reallocation = (char *) realloc(json->_dkjson_str, json->_dkjson_capacity * 2);
        if (reallocation == NULL)
        {
            return STATUS_ERR;
        }
        json->_dkjson_str = reallocation;
        json->_dkjson_capacity <<= 1;
    }

    if (json->_dkjson_count > 0)
    {
        strcat(json->_dkjson_str, ",");
    }
    strcat(json->_dkjson_str, "\"");
    strcat(json->_dkjson_str, key);
    strcat(json->_dkjson_str, "\":");
    strcat(json->_dkjson_str, value_str);
    json->_dkjson_count++;

    return STATUS_OK;
}