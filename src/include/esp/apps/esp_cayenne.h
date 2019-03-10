/**
 * \file            esp_cayenne.h
 * \brief           MQTT client for Cayenne
 */

/*
 * Copyright (c) 2018 Tilen Majerle
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of ESP-AT library.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 */
#ifndef ESP_HDR_APP_CAYENNE_H
#define ESP_HDR_APP_CAYENNE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp/esp.h"
#include "esp/apps/esp_mqtt_client_api.h"

/**
 * \ingroup         ESP_APPS
 * \defgroup        ESP_APP_CAYENNE MQTT client Cayenne
 * \brief           MQTT client for Cayenne
 * \{
 */

/**
 * \brief           Cayenne API version in string
 */
#ifndef ESP_CAYENNE_API_VERSION
#define ESP_CAYENNE_API_VERSION                 "v1"
#endif
                                                
 /**
 * \brief           Cayenne host server
 */
#ifndef ESP_CAYENNE_HOST
#define ESP_CAYENNE_HOST                        "mqtt.mydevices.com"
#endif

/**
 * \brief           Cayenne port number
 */
#ifndef ESP_CAYENNE_PORT
#define ESP_CAYENNE_PORT                        1883
#endif

#define ESP_CAYENNE_NO_CHANNEL                  0xFFFE
#define ESP_CAYENNE_ALL_CHANNELS                0xFFFF

/**
 * \brief           List of possible cayenne topics
 */
typedef enum {
    ESP_CAYENNE_TOPIC_DATA,                     /*!< Data topic */
    ESP_CAYENNE_TOPIC_COMMAND,                  /*!< Command topic */
    ESP_CAYENNE_TOPIC_CONFIG,
    ESP_CAYENNE_TOPIC_RESPONSE,
    ESP_CAYENNE_TOPIC_SYS_MODEL,
    ESP_CAYENNE_TOPIC_SYS_VERSION,
    ESP_CAYENNE_TOPIC_SYS_CPU_MODEL,
    ESP_CAYENNE_TOPIC_SYS_CPU_SPEED,
    ESP_CAYENNE_TOPIC_DIGITAL,
    ESP_CAYENNE_TOPIC_DIGITAL_COMMAND,
    ESP_CAYENNE_TOPIC_DIGITAL_CONFIG,
    ESP_CAYENNE_TOPIC_ANALOG,
    ESP_CAYENNE_TOPIC_ANALOG_COMMAND,
    ESP_CAYENNE_TOPIC_ANALOG_CONFIG,
    ESP_CAYENNE_TOPIC_END,                      /*!< Last entry */
} esp_cayenne_topic_t;

/**
 * \brief           Cayenne response types
 */
typedef enum {
    ESP_CAYENNE_RESP_OK,
    ESP_CAYENNE_RESP_ERROR,
} esp_cayenne_resp_t;

/**
 * \brief           Key/Value pair structure
 */
typedef struct {
    const char* key;                            /*!< Key string */
    const char* value;                          /*!< Value string */
} esp_cayenne_key_value_t;

/**
 * \brief           Cayenne message
 */
typedef struct {
    esp_cayenne_topic_t topic;                  /*!< Message topic */
    uint16_t channel;                           /*!< Message channel, optional, based on topic type */
    const char* seq;                            /*!< Sequence string on command */
    esp_cayenne_key_value_t values[2];          /*!< Key/Value pair of values */
    size_t values_count;                        /*!< Count of valid pairs in values member */
} esp_cayenne_msg_t;

/**
 * \brief           Cayenne handle
 */
typedef struct {
    esp_mqtt_client_api_p api_c;                /*!< MQTT API client */
    const esp_mqtt_client_info_t* info_c;       /*!< MQTT Client info structure */

    esp_cayenne_msg_t msg;

    esp_sys_thread_t thread;
    esp_sys_sem_t sem;
} esp_cayenne_t;

espr_t      esp_cayenne_create(esp_cayenne_t* c, const esp_mqtt_client_info_t* client_info);
espr_t      esp_cayenne_subscribe(esp_cayenne_t* c, esp_cayenne_topic_t topic, uint16_t channel);
espr_t      esp_cayenne_publish_data(esp_cayenne_t* c, esp_cayenne_topic_t topic, uint16_t channel, const char* type, const char* unit, const char* data);
espr_t      esp_cayenne_publish_float(esp_cayenne_t* c, esp_cayenne_topic_t topic, uint16_t channel, const char* type, const char* unit, float f);

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* ESP_HDR_APP_CAYENNE_H */