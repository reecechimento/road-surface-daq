/*******************************************************************************
 * @file	environment.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Encapsulate environmental sensor data:
 *      - temperature
 *      - humidity
 *      - pressure
 * Print environmental data in csv format:
 *      "temperature,humidity,pressure"
*******************************************************************************/

#pragma once
// TODO: file header here

#include "Arduino.h"

class Environment
{
        public:
                Environment();
                ~Environment();
                char *to_string();
                void  set_environment(float temperature,
                        float humidity,
                        float pressure
                );
                void  set_temperature(float temperature);
                void  set_humidity(float humidity);
                void  set_pressure(float pressure);
                float get_temperature();
                float get_humidity();
                float get_pressure();
        protected:
                float *_temperature{(float*)malloc(sizeof(float))};
                float *_humidity   {(float*)malloc(sizeof(float))};
                float *_pressure   {(float*)malloc(sizeof(float))};
};
