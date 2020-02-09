#include <Arduino.h>
#include <SoftwareSerial.h>

#include <Watering.h>
#include <Pauser.h>
#include <FunctionalPauser.h>
#include <Percentage.h>
#include <FunctionalRangePercentInputReader.h>
#include <PercentInputConvertedSensorReader.h>
#include <PotentiometerControlPanel.h>
#include <FunctionalPumpMotor.h>

#define TEST_MODE                         false
#define VERBOSE_MODE                      false
#define PUMP_TEST_DURATION_SECONDS        5
#define PRINT_SEPARATOR                   "####################################"
#define PRINT_SUBSEPARA                   "------------------------------------"

#define PLANT_COUNT                       3

// There is one plant with no watering setting potentiometer and this plant
// will be irrigated at 100% from others. Set the plant Id for this plant.
#define TOP_WATER_PLANT_ID                0

#define POT_WRITE_PIN                     4

// Adjust to lowest and highest values retrieved from sensor.
// Having minimum greater than maximum is not an error.
#define SENSOR_MIN                        146
#define SENSOR_MAX                        20

// Adjust to lowest and highest values retrieved from potentiometer.
// Having minimum greater than maximum is not an error.
// That inverted and now the minimum is at left side and maximum at right side
// of the potentiometer.
#define POT_MIN                           420
#define POT_MAX                           0

// Adjust to maximum seconds duration of watering
#define WATERING_MAX_SECONDS              60

// Writing signal durations in milliseconds
#define SENSOR_DURATION                   100
#define POT_DURATION                      100

// Execution interval
#define WATERING_INTERVAL_MINUTES         (4 * 60)
#define LOOP_INTERVAL_MINUTES             5

// General infrastructure delay interval in milliseconds
#define WAIT_INTERVAL                     100

// Lora
#define LORA_RX_PIN                     2
#define LORA_TX_PIN                     3

SoftwareSerial loraSerial(LORA_RX_PIN, LORA_TX_PIN);


struct PlantPinSet {
  int sensorWritePin;
  int sensorReadPin;
  int moisturePotPin;
  int wateringPotPin;
  int pumpPin;
};

// Lowest helpers ##############################################################

void print(const char *content) {
  if (true == VERBOSE_MODE) {
    Serial.print(content);
  }
}

void println(const char *content) {
  if (true == VERBOSE_MODE) {
    Serial.println(content);
  }
}

void print(int content) {
  if (true == VERBOSE_MODE) {
    Serial.print(content);
  }
}

void print(unsigned long content) {
  if (true == VERBOSE_MODE) {
    Serial.print(content);
  }
}

void println(unsigned long content) {
  if (true == VERBOSE_MODE) {
    Serial.println(content);
  }
}

void println(long content) {
  if (true == VERBOSE_MODE) {
    Serial.println(content);
  }
}

void println(int content) {
  if (true == VERBOSE_MODE) {
    Serial.println(content);
  }
}

unsigned long minutesToMillis(long minutes) {
  return minutes * 60 * 1000;
}

// Globals #####################################################################

boolean starting = true;

unsigned long now = 0;

const PlantPinSet plantPins[3] = {
    {9, A2, A7, 99, 6},
    {10, A1, A6, A4, 7},
    {11, A0, A5, A3, 8}
};

Percentage *percentService;

SensorReader *sensors[3];
ControlPanel *panels[3];
PumpMotor *pumps[3];
Watering *useCases[3];

Pauser *pauser;

int getSensorWritePin(const unsigned short plantId) {
  return plantPins[plantId].sensorWritePin;
}

int getSensorReadPin(const unsigned short plantId) {
  return plantPins[plantId].sensorReadPin;
}

int getMoisturePotPin(const unsigned short plantId) {
  return plantPins[plantId].moisturePotPin;
}

int getWateringPotPin(const unsigned short plantId) {
  return plantPins[plantId].wateringPotPin;
}

int getPumpPin(const unsigned short plantId) {
  return plantPins[plantId].pumpPin;
}

int readPinSignal(int duration, int writePin, int readPin) {
  int value;
  digitalWrite(writePin, HIGH);
  delay(duration);
  value = analogRead(readPin);
  digitalWrite(writePin, LOW);
  delay(WAIT_INTERVAL);
  print("Reading signal for pin ");
  print(readPin);
  print(" returned ");
  println(value);
  return value;
}

// Injected functions ##########################################################

long readSensor(long plantId) {
  print("Reading sensor for plant ID ");
  println(plantId);
  int readingPin = getSensorReadPin(plantId);
  return (long) readPinSignal(
      SENSOR_DURATION,
      getSensorWritePin(plantId),
      readingPin
  );
}

long readMoisture(long plantId) {
  print("Reading moisture setting for plant ID ");
  println(plantId);
  int readingPin = getMoisturePotPin(plantId);
  return (long) readPinSignal(POT_DURATION, POT_WRITE_PIN, readingPin);
}

long readWatering(long plantId) {
  print("Reading watering setting for plant ID ");
  println(plantId);
  int readingPin = getWateringPotPin(plantId);
  return (long) readPinSignal(POT_DURATION, POT_WRITE_PIN, readingPin);
}

long forceMaxWatering(long plantId) {
  print("Forcing maximum watering setting for plant ID ");
  println(plantId);
  return POT_MAX;
}

void startMotor(long plantId) {
  int pumpPin = getPumpPin(plantId);
  print("Starting motor for plant ID ");
  println(plantId);
  digitalWrite(pumpPin, LOW);
}

void stopMotor(long plantId) {
  print("Stopping motor for plant ID ");
  println(plantId);
  int pumpPin = getPumpPin(plantId);
  digitalWrite(pumpPin, HIGH);
}

// Preparing ###################################################################

SensorReader *buildSensor(int sensorIndex) {
  PercentInputReader *inputReader = new FunctionalRangePercentInputReader(
      percentService,
      readSensor,
      SENSOR_MIN,
      SENSOR_MAX,
      sensorIndex
  );
  return new PercentInputConvertedSensorReader(inputReader);
}

ControlPanel *buildPanel(
    int sensorIndex,
    long readWatering_(long)) {
  PercentInputReader *moisturePot = new FunctionalRangePercentInputReader(
      percentService,
      readMoisture,
      POT_MIN,
      POT_MAX,
      sensorIndex
  );
  PercentInputReader *wateringPot = new FunctionalRangePercentInputReader(
      percentService,
      readWatering_,
      POT_MIN,
      POT_MAX,
      sensorIndex
  );
  return new PotentiometerControlPanel(
      moisturePot,
      wateringPot,
      WATERING_MAX_SECONDS
  );
}

void initPlants() {
  for (int plantIndex = 0; plantIndex < PLANT_COUNT; plantIndex++) {
    sensors[plantIndex] = buildSensor(plantIndex);
    if (plantIndex == TOP_WATER_PLANT_ID) {
      panels[plantIndex] = buildPanel(plantIndex, forceMaxWatering);
    } else {
      panels[plantIndex] = buildPanel(plantIndex, readWatering);
    }
    pumps[plantIndex] = new FunctionalPumpMotor(
        startMotor,
        stopMotor,
        plantIndex
    );
    useCases[plantIndex] = new Watering(
        sensors[plantIndex],
        panels[plantIndex],
        pumps[plantIndex],
        pauser
    );
  }
}

void initSystem() {
  pinMode(POT_WRITE_PIN, OUTPUT);
  loraSerial.begin(9600);

  for (int plantIndex = 0; plantIndex < PLANT_COUNT; plantIndex++) {
    pinMode(getSensorReadPin(plantIndex), INPUT);
    pinMode(getMoisturePotPin(plantIndex), INPUT);
    if (plantIndex != TOP_WATER_PLANT_ID) {
      pinMode(getWateringPotPin(plantIndex), INPUT);
    }
    pinMode(getPumpPin(plantIndex), OUTPUT);
    stopMotor(plantIndex);
  }
  println(PRINT_SEPARATOR);
}

// Main ########################################################################

void testPlantInputs(int plantIndex) {
  int sensorPercent = sensors[plantIndex]->percentRead();
  int moistureSettingPercent = panels[plantIndex]->getMinimumMoistureSetting();
  int wateringSettingPercent =
      (int) panels[plantIndex]->getWaterAmountSetting();
  print("Watering invoke for plant Id ");
  println(plantIndex);
  println(PRINT_SUBSEPARA);
  print("Sensor read ");
  print(sensorPercent);
  println("%");
  print("Moisture setting is ");
  print(moistureSettingPercent);
  println("%");
  println(PRINT_SUBSEPARA);
  print("Watering setting is ");
  print(wateringSettingPercent);
  println(" seconds");
}

void testPlantPump(int plantIndex) {
  print("Starting pump for plant Id ");
  println(plantIndex);
  startMotor(plantIndex);
  delay(PUMP_TEST_DURATION_SECONDS * 1000);
  stopMotor(plantIndex);
  print("Stopped pump for plant Id ");
  println(plantIndex);
}

void logPlant(int plantIndex) {
  int sensorPercent = sensors[plantIndex]->percentRead();
  int moistureSettingPercent = panels[plantIndex]->getMinimumMoistureSetting();
  int wateringSettingPercent =
      (int) panels[plantIndex]->getWaterAmountSetting();
  char event[40];
  sprintf(
      event,
      R"({"P":%d,"R":%d,"M":%d,"W":%d})",
      plantIndex + 1,
      sensorPercent,
      moistureSettingPercent,
      wateringSettingPercent
  );
  print("Sending to Lora Serial: ");
  println(event);
  loraSerial.println(event);
}

void invokeWatering() {
  for (auto &useCase : useCases) {
    unsigned short watered = useCase->invoke();
    print("RESULT ");
    print((int) watered);
    println(" seconds watered.");
    println("");
    println(PRINT_SEPARATOR);
  }
}

void invokeTesting() {
  for (int plantIndex = 0; plantIndex < PLANT_COUNT; plantIndex++) {
    testPlantInputs(plantIndex);
    println(PRINT_SUBSEPARA);
    testPlantPump(plantIndex);
    println(PRINT_SEPARATOR);
  }
}

void invokeLogging() {
  for (int plantIndex = 0; plantIndex < PLANT_COUNT; plantIndex++) {
    logPlant(plantIndex);
  }
}

void wateringHandler() {
  if (true == starting) {
    starting = false;
    invokeWatering();
  }
  print("millis() = ");
  println(millis());
  print("now = ");
  println(now);
  print("WATERING_INTERVAL_MINUTES millis. = ");
  println(minutesToMillis(WATERING_INTERVAL_MINUTES));
  println("");
  if (millis() > now + minutesToMillis(WATERING_INTERVAL_MINUTES)) {
    print("Interval of ");
    print(minutesToMillis(WATERING_INTERVAL_MINUTES) / 1000);
    print(" seconds triggered after ");
    print((unsigned long) (millis() / 1000));
    println(" seconds.");
    now = millis();
    invokeWatering();
  }
}

void setup() {
  Serial.begin(9600);
  initSystem();
  pauser = new FunctionalPauser(delay);
  percentService = new Percentage();
  initPlants();
  invokeTesting();
}

void loop() {
  invokeLogging();
  if (false == TEST_MODE) {
    wateringHandler();
  }
  delay(minutesToMillis(LOOP_INTERVAL_MINUTES));
}