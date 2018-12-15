
/*******************************
 * 
 * @author Mr Dk.
 * @version 2018.12.15, Nanjing
 * 
 * *****************************/

#ifndef _DK_JSON_
#define _DK_JSON_

typedef int Status;

#define STATUS_OK 1
#define STATUS_ERR 0
#define STR_INIT_SIZE 64

typedef struct dkJSON
{
    char *_dkjson_str;
    int _dkjson_capacity;
    int _dkjson_count;

} dkJSON;

Status dkjson_init(dkJSON *json);
void dkjson_destroy(dkJSON *json);

Status dkjson_put_string(dkJSON *json, char key[], char value[]);
Status dkjson_put_int(dkJSON *json, char key[], int value);
Status dkjson_put_short(dkJSON *json, char key[], short value);
Status dkjson_put_long(dkJSON *json, char key[], long long value);
Status dkjson_put_float(dkJSON *json, char key[], float value);
Status dkjson_put_double(dkJSON *json, char key[], double value);

void dkjson_generate(dkJSON *json, char res[]);

#endif