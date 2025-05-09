#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <mosquitto.h>
#include <cjson/cJSON.h>

void publish_message(struct mosquitto *mosq, const char *topic, const char *message)
{
    int ret = mosquitto_publish(mosq, NULL, topic, strlen(message), message, 0, false);
    if (ret != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Error publishing message: %s\n", mosquitto_strerror(ret));
    }
}

int main(int argc, char *argv[])
{
    struct mosquitto *mosq;
    char *topic = "test/topic";

    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto runtime instance with a random client ID
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        fprintf(stderr, "Could not create Mosquitto instance\n");
        exit(-1);
    }

    // Connect to an MQTT broker
    if (mosquitto_connect(mosq, "192.168.2.176", 1883, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Could not connect to broker\n");
        exit(-1);
    }

    int num_tasks = 6;

    for (int i = 0; i < num_tasks; i++)
    {
        // Prepare the JSON message
        cJSON *root = cJSON_CreateObject();
        const char *json_string;

        // Tasks
        if (i == 0)
        {
            cJSON_AddStringToObject(root, "task", "get_temperature");
        }
        else if (i == 1)
        {
            cJSON_AddStringToObject(root, "task", "get_pressure");
        }
        else if (i == 2)
        {
            cJSON_AddStringToObject(root, "task", "get_temperature_pressure");
        }
        else if (i == 3)
        {
            cJSON_AddStringToObject(root, "print_msg", "hello world");
        }
        else if (i == 4)
        {
            cJSON_AddStringToObject(root, "morse_msg", "hello world");
        }
        else
        {
            cJSON_AddNumberToObject(root, "int_msg", 12);
        }

        json_string = cJSON_Print(root);

        // Publish the message
        publish_message(mosq, topic, json_string);

        // Cleanup
        free((void *)json_string);
        cJSON_Delete(root);

        sleep(5);
    }

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
