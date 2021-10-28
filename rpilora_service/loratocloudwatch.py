#!/usr/bin/env python3
import json
from json import JSONDecodeError
from pprint import pprint

import serial
from time import sleep
import boto3
import sys

CLOUDWATCH_NAMESPACE = 'WATERING_OFFICE/POC'
PLANT_DIMENSION_NAME = 'Plant'
TECH_DIMENSION_NAME = 'Technical'
PLANT_DIMENSION_VALUE_PREFIX = 'plant-'

WATERING_EVENT_PLANT_FIELD = "P"
WATERING_EVENT_READING_FIELD = "R"
WATERING_EVENT_MOISTURE_FIELD = "M"
WATERING_EVENT_WATERING_FIELD = "W"

ARDUINO_NEWLINE_TOKEN = "\r\n"


def log(
        boto_client,
        namespace,
        metric_name,
        record_value,
        dimension_name=None,
        dimension_value=None
):
    metric_item = {
        'MetricName': metric_name,
        'Unit': 'None',
        'Value': record_value
    }
    if dimension_name and dimension_value:
        metric_item['Dimensions'] = [
            {
                'Name': dimension_name,
                'Value': dimension_value
            }
        ]
    boto_client.put_metric_data(
        MetricData=[metric_item],
        Namespace=namespace
    )


def log_technical_error(event):
    print(event, file=sys.stderr)


def log_reading(client, plant_id, value):
    log(
        client,
        CLOUDWATCH_NAMESPACE,
        'reading',
        value,
        PLANT_DIMENSION_NAME,
        "{0}{1}".format(PLANT_DIMENSION_VALUE_PREFIX, plant_id)
    )


def log_moisture_setting(client, plant_id, value):
    log(
        client,
        CLOUDWATCH_NAMESPACE,
        'moisture-setting',
        value,
        PLANT_DIMENSION_NAME,
        "{0}{1}".format(PLANT_DIMENSION_VALUE_PREFIX, plant_id)
    )


def log_watering_setting(client, plant_id, value):
    log(
        client,
        CLOUDWATCH_NAMESPACE,
        'watering-setting',
        value,
        PLANT_DIMENSION_NAME,
        "{0}{1}".format(PLANT_DIMENSION_VALUE_PREFIX, plant_id)
    )


def raw_to_json(raw_content, eol_chars):
    content = raw_content.decode("utf-8")
    content = content.strip(ARDUINO_NEWLINE_TOKEN)
    content = content.replace(eol_chars, ", ")
    json_content = '[{0}]'.format(content)
    return json.loads(json_content)


def log_watering_events(client, watering_events):
    for watering_event in watering_events:
        if WATERING_EVENT_PLANT_FIELD in watering_event:
            plant_id = watering_event[WATERING_EVENT_PLANT_FIELD]
        else:
            print("No Plant ID in the following watering event")
            pprint(watering_event)
            continue
        if WATERING_EVENT_READING_FIELD in watering_event:
            log_reading(
                client,
                plant_id,
                watering_event[WATERING_EVENT_READING_FIELD]
            )
        if WATERING_EVENT_MOISTURE_FIELD in watering_event:
            log_moisture_setting(
                client,
                plant_id,
                watering_event[WATERING_EVENT_MOISTURE_FIELD]
            )
        if WATERING_EVENT_WATERING_FIELD in watering_event:
            log_watering_setting(
                client,
                plant_id,
                watering_event[WATERING_EVENT_WATERING_FIELD]
            )


if __name__ == '__main__':
    if 3 > len(sys.argv):
        raise ValueError("Port name and baud rate are required")

    PORT_NAME = sys.argv[1]
    BAUD_RATE = sys.argv[2]

    # Create CloudWatch client
    cloudwatch = boto3.client('cloudwatch')

    ser = serial.Serial(PORT_NAME, BAUD_RATE)

    while True:
        received_data = ser.read()
        sleep(0.03)
        data_left = ser.inWaiting()
        received_data += ser.read(data_left)
        try:
            events = raw_to_json(received_data, ARDUINO_NEWLINE_TOKEN)
        except JSONDecodeError as json_exc:
            log_technical_error(
                "{0}. Content as {1}".format(
                    json_exc,
                    received_data.decode("utf-8")
                )
            )
            continue
        except UnicodeDecodeError as decode_error:
            log_technical_error(
                "{0}. Decoding error".format(
                    decode_error,
                )
            )
            continue

        log_watering_events(cloudwatch, events)
        print(received_data)
