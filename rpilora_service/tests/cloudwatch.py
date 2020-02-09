import boto3
from .. import loratocloudwatch

cloudwatch = boto3.client('cloudwatch')

readings = [
    {"P": 0, "R": 2, "M": 3, "W": 4},
    {"P": 1, "R": 2, "M": 3, "W": 4},
    {"P": 2, "R": 2, "M": 3, "W": 4},
]

loratocloudwatch.log_watering_events(cloudwatch, readings)
