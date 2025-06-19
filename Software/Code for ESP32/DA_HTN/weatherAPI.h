const char *ssid = "hihi";
const char *password = "Bocutenhat";
// const char *ssid = ":(";
// const char *password = "datdat11330";

const char* format = "%d/%m/%Y";

String apiKey = ""; // Enter your API here

const int num_of_city = 12;
String cities_name[num_of_city] = { "Ha Giang Town", "Yen Bai Town", "Hanoi Capital", "Hai Phong City", "Nghe An Town", "Hue Town", "Quang Ngai Town", "Khanh Hoa City", "Da Lat City", "Ho Chi Minh City", "Long An Town", "Ca Mau Town" };
uint32_t cities_id[num_of_city] = { 1581030, 1559978, 1581130, 1581298, 1559969, 1580240, 1568769, 1579634, 1584071, 1566083, 1575788, 1905678 };

String forecastWeatherCall = "http://api.openweathermap.org/data/2.5/forecast/daily?id=";
String currentWeatherCall = "http://api.openweathermap.org/data/2.5/weather?id=";
String dailyWeatherCall = "http://api.openweathermap.org/data/2.5/weather?lat=10.847216247461693&lon=106.78197469839604";

String jsonBufferCurrent;
String jsonBufferForecast;
String jsonBufferDaily;

typedef struct {
  String weather_des;
  String icon_id;
  uint8_t temperature;
  uint8_t humidity;
  uint8_t wind_speed;
  uint8_t wind_degree;
} current_data_to_stm_t;

typedef struct {
  String date;
  String icon_id;
  uint8_t temperature;
  uint8_t humidity;
  uint8_t wind_speed;
} forecast_data_to_stm_t;

current_data_to_stm_t current_data_to_stm;
forecast_data_to_stm_t forecast_data_to_stm[7];
String daily_data_to_stm;

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  delay(500);
  http.begin(client, serverName);

  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}

String DateTime(time_t time, const char* format) {
  char buffer[90];
  struct tm* timeinfo = localtime(&time);
  strftime(buffer, sizeof(buffer), format, timeinfo);
  return buffer;
}

void getDailyWeather() {
  String serverPathDaily = dailyWeatherCall + "&appid=" + apiKey + "&units=metric";
  Serial.println("==================================================================");
  Serial.println(serverPathDaily);

  jsonBufferDaily = httpGETRequest(serverPathDaily.c_str());
  Serial.println(jsonBufferDaily);

  JSONVar myObjectDaily = JSON.parse(jsonBufferDaily);

  if (JSON.typeof(myObjectDaily) == "undefined") {
    Serial.println("Parsing daily weather input failed");
    return;
  }

  Serial.println("*************************************");
  Serial.println("Daily weather");
  Serial.print("Icon ID: ");
  Serial.println((const char*) myObjectDaily["weather"][0]["icon"]);

  daily_data_to_stm = JSON.stringify(myObjectDaily["weather"][0]["icon"]);

  Serial.println("*************************************");
  Serial.println("Data to STM32");
  Serial.println(daily_data_to_stm);
}

void getWeather(int index) {
  char cityID_buff[10];
  itoa(cities_id[index], cityID_buff, 10);
  String cityID(cityID_buff);
  String serverPathCurrent = currentWeatherCall + cityID + "&appid=" + apiKey + "&units=metric";
  String serverPathForecast = forecastWeatherCall + cityID + "&cnt=8&appid=" + apiKey + "&units=metric";

  Serial.println("==================================================================");
  Serial.println(serverPathCurrent);
  Serial.println(serverPathForecast);

  jsonBufferCurrent = httpGETRequest(serverPathCurrent.c_str());
  jsonBufferForecast = httpGETRequest(serverPathForecast.c_str());
  Serial.println(jsonBufferCurrent);
  Serial.println(jsonBufferForecast);

  JSONVar myObjectCurrent = JSON.parse(jsonBufferCurrent);
  JSONVar myObjectForecast = JSON.parse(jsonBufferForecast);

  if (JSON.typeof(myObjectCurrent) == "undefined") {
    Serial.println("Parsing current weather input failed for " + cities_name[index]);
    return;
  }

  if (JSON.typeof(myObjectForecast) == "undefined") {
    Serial.println("Parsing forecast weather input failed for " + cities_name[index]);
    return;
  }

  Serial.println("City name: " + cities_name[index]);
  Serial.println("*************************************");
  Serial.println("Current weather");
  Serial.print("Weather ID: ");
  Serial.println((const char*) myObjectCurrent["weather"][0]["description"]);
  Serial.print("Icon ID: ");
  Serial.println((const char*) myObjectCurrent["weather"][0]["icon"]);
  Serial.print("Temperature: ");
  Serial.println((int) myObjectCurrent["main"]["temp"]);
  Serial.print("Humidity: ");
  Serial.println((int) myObjectCurrent["main"]["humidity"]);
  Serial.print("Wind Speed: ");
  Serial.println((int) myObjectCurrent["wind"]["speed"]);
  Serial.print("Wind Degree: ");
  Serial.println((int) myObjectCurrent["wind"]["deg"]);

  current_data_to_stm.weather_des = JSON.stringify(myObjectCurrent["weather"][0]["description"]);
  current_data_to_stm.icon_id = JSON.stringify(myObjectCurrent["weather"][0]["icon"]);
  current_data_to_stm.temperature = (int) myObjectCurrent["main"]["temp"];
  current_data_to_stm.humidity = (int) myObjectCurrent["main"]["humidity"];
  current_data_to_stm.wind_speed = (int) myObjectCurrent["wind"]["speed"];
  current_data_to_stm.wind_degree = (int) myObjectCurrent["wind"]["deg"];

  Serial.println("*************************************");
  Serial.println("Data to STM32");
  Serial.println(current_data_to_stm.weather_des);
  Serial.println(current_data_to_stm.icon_id);
  Serial.println(current_data_to_stm.temperature);
  Serial.println(current_data_to_stm.humidity);
  Serial.println(current_data_to_stm.wind_speed);
  Serial.println(current_data_to_stm.wind_degree);

  Serial.println("*************************************");
  Serial.println("Forecast weather");

  JSONVar forecastList = myObjectForecast["list"];
  for (int j = 0; j < forecastList.length(); j++) {
    Serial.print("Day ");
    Serial.println(j + 1);
    Serial.print("Timestamp: ");
    Serial.println((int) forecastList[j]["dt"]);
    Serial.print("Icon: ");
    Serial.println((const char*) forecastList[j]["weather"][0]["icon"]);
    Serial.print("Temperature: ");
    Serial.println(((int) forecastList[j]["temp"]["min"] + (int) forecastList[j]["temp"]["max"]) / 2);
    Serial.print("Humidity: ");
    Serial.println((int) forecastList[j]["humidity"]);
    Serial.print("Wind Speed: ");
    Serial.println((int) forecastList[j]["speed"]);
    Serial.println("-------------------");
    
    if (j != 0) {
      forecast_data_to_stm[j - 1].date = DateTime((uint32_t) forecastList[j]["dt"], format);
      forecast_data_to_stm[j - 1].icon_id = JSON.stringify(forecastList[j]["weather"][0]["icon"]);
      forecast_data_to_stm[j - 1].temperature = ((int) forecastList[j]["temp"]["min"] + (int) forecastList[j]["temp"]["max"]) / 2;
      forecast_data_to_stm[j - 1].humidity = (int) forecastList[j]["humidity"];
      forecast_data_to_stm[j - 1].wind_speed = (int) forecastList[j]["speed"];
      Serial.println("*************************************");
      Serial.println("Data to STM32");
      Serial.println(forecast_data_to_stm[j - 1].date);
      Serial.println(forecast_data_to_stm[j - 1].icon_id);
      Serial.println(forecast_data_to_stm[j - 1].temperature);
      Serial.println(forecast_data_to_stm[j - 1].humidity);
      Serial.println(forecast_data_to_stm[j - 1].wind_speed);
    }
  }
}