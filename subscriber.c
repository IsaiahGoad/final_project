#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ssd1306.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include <linux_i2c.h>
#include <bmp280_i2c.h>

void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    char msg[200] = {0};
    ssd1306_init(0);
    ssd1306_oled_onoff(1);
    ssd1306_oled_default_config(64, 128);

    if (message->payloadlen)
    {
        cJSON *root = cJSON_Parse(message->payload);
        if (root)
        {
            const cJSON *task = cJSON_GetObjectItemCaseSensitive(root, "task");
            if (cJSON_IsString(task) && (task->valuestring != NULL))
            {
                struct bmp280_i2c result = read_temp_pressure();
                printf("task: %s\n", task->valuestring);

                if (strcmp(task->valuestring, "get_temperature") == 0)
                {
                    ssd1306_oled_clear_screen();
                    snprintf(msg, sizeof(msg), "Temp: %.2f C", result.temperature);
                    ssd1306_oled_write_string(0, msg);
                }

                else if (strcmp(task->valuestring, "get_pressure") == 0)
                {
                    ssd1306_oled_clear_screen();
                    snprintf(msg, sizeof(msg), "Pres: %.3f kPa", result.pressure);
                    ssd1306_oled_write_string(0, msg);
                }

                else if (strcmp(task->valuestring, "get_temperature_pressure") == 0)
                {
                    ssd1306_oled_clear_screen();
                    snprintf(msg, sizeof(msg), "T: %.2fC P: %.3fkPa", result.temperature, result.pressure);
                    ssd1306_oled_write_string(0, msg);

                    // BONUS 1: Publish to "taskingcomplete"
                    cJSON *response = cJSON_CreateObject();
                    cJSON_AddNumberToObject(response, "temp", result.temperature);
                    cJSON_AddNumberToObject(response, "pressure", result.pressure);

                    char *json_out = cJSON_PrintUnformatted(response);
                    mosquitto_publish(mosq, NULL, "taskingcomplete", strlen(json_out), json_out, 0, false);

                    free(json_out);
                    cJSON_Delete(response);
                    // END BONUS 1
                }
            }

            const cJSON *int_msg = cJSON_GetObjectItemCaseSensitive(root, "int_msg");
            if (cJSON_IsNumber(int_msg))
            {
                printf("Number: %d\n", int_msg->valueint);
                ssd1306_oled_clear_screen();
                snprintf(msg, sizeof(msg), "%d", int_msg->valueint);
                ssd1306_oled_write_string(0, msg);
                sprintf(msg, "%d", int_msg->valueint);
                        ssd1306_oled_write_string(0, msg);
            }

            const cJSON *print_msg = cJSON_GetObjectItemCaseSensitive(root, "print_msg");
            if (cJSON_IsString(print_msg) && (print_msg->valuestring != NULL))
            {
                ssd1306_oled_clear_screen();
                strncpy(msg, print_msg->valuestring, sizeof(msg));
                ssd1306_oled_write_string(0, msg);
            }

            cJSON_Delete(root);
        }
        else
        {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        }
    }
    else
    {
        printf("%s (null)\n", message->topic);
    }
}

int main(int argc, char *argv[])
{
    struct mosquitto *mosq;

    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto runtime instance with a random client ID
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        fprintf(stderr, "Could not create Mosquitto instance\n");
        exit(-1);
    }

    // Assign the message callback
    mosquitto_message_callback_set(mosq, message_callback);

    // Connect to an MQTT broker
    if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Could not connect to broker\n");
        exit(-1);
    }

    // Subscribe to the topic
    mosquitto_subscribe(mosq, NULL, "test/topic", 0);

    // Start the loop
    mosquitto_loop_start(mosq);

    printf("Press Enter to quit...\n");
    getchar();

    // Cleanup
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
