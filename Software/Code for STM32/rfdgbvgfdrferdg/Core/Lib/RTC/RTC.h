/*
 * RTC.h
 *
 *  Created on: Dec 11, 2024
 *      Author: Lenovo
 */

#ifndef LIB_RTC_RTC_H_
#define LIB_RTC_RTC_H_

#include "stm32h7xx_hal.h"
#include "../Inc/main.h"

char rtc_gDate[10], rtc_gWeekDay[3], rtc_gHour[2], rtc_gMin[2], rtc_gSec[2];
uint8_t rtc_sHour, rtc_sMin, rtc_sSec, rtc_sYear, rtc_sMonth, rtc_sDate, rtc_sWeekDay, rtc_sDone, rtc_sMode, rtc_sFlag;
char rtc_sHour_buff[3], rtc_sMin_buff[3], rtc_sYear_buff[5], rtc_sMonth_buff[3], rtc_sDate_buff[3], rtc_sWeekDay_buff[4];
char weather_temp[5], weather_humidity[4], weather_wind_speed[10], weather_wind_degree[3];
char weather_icon_id[4];
char weather_des[50];
char weather_des_tmp[50];
char weather_date[11];

RTC_DateTypeDef gDate = {0};
RTC_TimeTypeDef gTime = {0};

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};

RTC_TimeTypeDef sTime_pre = {0};
RTC_DateTypeDef sDate_pre = {0};

uint16_t game_snake_score = 0;
char game_snake_score_buff[15];
uint16_t game_snake_random_x;
uint16_t game_snake_random_y;
uint16_t game_snake_position[100][2] = {{12, 16}, {12, 17}, {12, 18}};
uint16_t game_snake_apple_position[2];
uint16_t game_snake_element = 3;
uint32_t game_snake_direction = 1;
uint32_t game_snake_speed = 200;
uint8_t game_snake_flag = 0;
uint8_t game_snake_rst_flag = 0;
uint8_t game_snake_out_flag = 0;

void RTC_setTime(RTC_HandleTypeDef *hrtc, uint8_t hour, uint8_t min, uint8_t sec, uint8_t year, uint8_t month, uint8_t date, uint8_t weekDay) {
	sTime.Hours = hour;
	sTime.Minutes = min;
	sTime.Seconds = sec;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sDate.Year = year;
	sDate.Month = month;
	sDate.Date = date;
	sDate.WeekDay = weekDay;

	if (HAL_RTC_SetTime(hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}

	if (HAL_RTC_SetDate(hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}
}

void RTC_getTime(RTC_HandleTypeDef *hrtc, char *hour, char *min, char *sec, char *date, char *weekDay) {;
	HAL_RTC_GetTime(hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &gDate, RTC_FORMAT_BIN);

	sprintf((char*) hour, "%02d", gTime.Hours);
	sprintf((char*) min, "%02d", gTime.Minutes);
	sprintf((char*) sec, "%02d", gTime.Seconds);
	sprintf((char*) date, "%02d/%02d/%2d", gDate.Date, gDate.Month, 2000 + gDate.Year);
	sprintf((char*) weekDay, "%s", (gDate.WeekDay == 1) ? "Mon" : (gDate.WeekDay == 2) ? "Tue" : (gDate.WeekDay == 3) ? "Wed" : (gDate.WeekDay == 4) ? "Thu" : (gDate.WeekDay == 5) ? "Fri" : (gDate.WeekDay == 6) ? "Sat" : "Sun");
}

void RTC_displayTime(uint8_t flag) {
	ST7789_WriteStringMedium(24, 84, rtc_gHour, FontMorgan_32x72, WHITE, BLACK);
	ST7789_WriteStringMedium(92, 84, rtc_gMin, FontMorgan_32x72, 0x176f, BLACK);
	ST7789_WriteString(159, 112, rtc_gSec, FontMorgan_16x36, WHITE, BLACK);
	ST7789_WriteString(22, 50, rtc_gDate, Font_11x18, WHITE, BLACK);
	ST7789_WriteString(22, 25, rtc_gWeekDay, Font_11x18, WHITE, BLACK);
	ST7789_WriteString(177, 172, sht_temp_buff, Font_11x18, WHITE, BLACK);
	ST7789_WriteString(177, 212, sht_hum_buff, Font_11x18, WHITE, BLACK);

	if (flag == 0) {
		ST7789_DrawImageComp(22, 156, 32, 32, lcd_thermometer, 838, BLACK, 1);
		ST7789_DrawImageComp(22, 196, 32, 32, lcd_humidity, 476, BLACK, 1);
	}
	if ((sht_prev_temp != sht_temp) || (flag == 0)) {
		ST7789_Fill(52, 174, 152, 186, BLACK);
		ST7789_DrawSlider(52, 174, 100, 12, WHITE, RED, sht_temp);
	}
	if ((sht_prev_humidity != sht_humidity) || (flag == 0)) {
		ST7789_Fill(52, 214, 152, 226, BLACK);
		ST7789_DrawSlider(52, 214, 100, 12, WHITE, CYAN, sht_humidity);
	}
}

void WEATHER_display_current() {
	uint8_t wind_degree;
	memset(weather_temp, '\0', sizeof(weather_temp));
	memset(weather_humidity, '\0', sizeof(weather_humidity));
	memset(weather_wind_speed, '\0', sizeof(weather_wind_speed));
	memset(weather_wind_degree, '\0', sizeof(weather_wind_degree));
	memset(weather_des, '\0', sizeof(weather_des));
	memset(weather_icon_id, '\0', sizeof(weather_icon_id));
	memset(weather_des_tmp, '\0', sizeof(weather_des_tmp));

	strcpy(weather_des, strtok(weather_current[0], "\""));
	strcpy(weather_icon_id, strtok(weather_current[1], "\""));
	strncpy(weather_temp, weather_current[2], 3);
	strncpy(weather_humidity, weather_current[3], 3);
	strncpy(weather_wind_speed, weather_current[4], 3);
	wind_degree = atoi(strncpy(weather_wind_degree, weather_current[5], 3));

	strcpy(weather_wind_degree, "");
	if ((wind_degree >= 0 && wind_degree < 22) || (wind_degree >= 337 && wind_degree < 360)) {
		strcpy(weather_wind_degree, "N");
	}
	else if ((wind_degree >= 22 && wind_degree < 67)) {
		strcpy(weather_wind_degree, "NE");
	}
	else if (wind_degree >= 67 && wind_degree < 112) {
		strcpy(weather_wind_degree, "E");
	}
	else if (wind_degree >= 112 && wind_degree < 157) {
		strcpy(weather_wind_degree, "SE");
	}
	else if (wind_degree >= 157 && wind_degree < 202) {
		strcpy(weather_wind_degree, "S");
	}
	else if (wind_degree >= 202 && wind_degree < 247) {
		strcpy(weather_wind_degree, "SW");
	}
	else if (wind_degree >= 247 && wind_degree < 299) {
		strcpy(weather_wind_degree, "W");
	}
	else if (wind_degree >= 299 && wind_degree < 337) {
		strcpy(weather_wind_degree, "NW");
	}

	if (strcmp(weather_icon_id, "01d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 128, lcd_01d, lcd_01d_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "01n") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 128, lcd_01n, lcd_01n_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "02d") == 0) {
		ST7789_DrawImageComp(50, 15, 129, 86, lcd_02d, lcd_02d_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "02n") == 0) {
		ST7789_DrawImageComp(50, 15, 127, 87, lcd_02n, lcd_02n_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "03n") == 0 || strcmp(weather_icon_id, "03d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 82, lcd_03dn, lcd_03dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "04n") == 0 || strcmp(weather_icon_id, "04d") == 0) {
		ST7789_DrawImageComp(50, 15, 139, 88, lcd_04dn, lcd_04dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "09n") == 0 || strcmp(weather_icon_id, "09d") == 0) {
		ST7789_DrawImageComp(50, 15, 114, 103, lcd_09dn, lcd_09dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "10d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 124, lcd_10d, lcd_10d_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "10n") == 0) {
		ST7789_DrawImageComp(50, 15, 108, 105, lcd_10n, lcd_10n_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "11n") == 0 || strcmp(weather_icon_id, "11d") == 0) {
		ST7789_DrawImageComp(50, 15, 132, 111, lcd_11dn, lcd_11dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "50n") == 0 || strcmp(weather_icon_id, "50d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 128, lcd_50dn, lcd_50dn_size, BLACK, 1);
	}

	sprintf((char*) weather_des_tmp, "It's %s", weather_des);
	ST7789_WriteString(36, 155, weather_des_tmp, Font_11x18, WHITE, BLACK);

	ST7789_DrawImageComp(18, 200, 11, 25, lcd_thermometer_small, lcd_thermometer_small_size, BLACK, 1);
	sprintf((char*) weather_temp, "%s%cC", weather_temp, 0x7F);
	ST7789_WriteString(32, 208, weather_temp, Font_11x18, WHITE, BLACK);

	ST7789_DrawImageComp(80, 201, 16, 24, lcd_humidity_small, lcd_humidity_small_size, BLACK, 1);
	sprintf((char*) weather_humidity, "%s%%", weather_humidity);
	ST7789_WriteString(100, 208, weather_humidity, Font_11x18, WHITE, BLACK);

	ST7789_DrawImageComp(140, 210, 16, 16, lcd_wind, lcd_wind_size, BLACK, 1);
	sprintf((char*) weather_wind_speed, "%sm/s%s", weather_wind_speed, weather_wind_degree);
	ST7789_WriteString(160, 208, weather_wind_speed, Font_11x18, WHITE, BLACK);

	ST7789_WriteString(200, 30, "Nxt", Font_11x18, WHITE, BLACK);
}

void WEATHER_display_forecast(uint8_t day) {
	memset(weather_temp, '\0', sizeof(weather_temp));
	memset(weather_humidity, '\0', sizeof(weather_humidity));
	memset(weather_wind_degree, '\0', sizeof(weather_wind_degree));
	memset(weather_icon_id, '\0', sizeof(weather_icon_id));
	memset(weather_date, '\0', sizeof(weather_date));

	day *= 5;
	strcpy(weather_date, weather_forecast[day]);
	strcpy(weather_icon_id, strtok(weather_forecast[day+1], "\""));
	strncpy(weather_temp, weather_forecast[day+2], 3);
	strncpy(weather_humidity, weather_forecast[day+3], 3);
	strncpy(weather_wind_speed, weather_forecast[day+4], 3);

	if (strcmp(weather_icon_id, "01d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 128, lcd_01d, lcd_01d_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "01n") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 128, lcd_01n, lcd_01n_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "02d") == 0) {
		ST7789_DrawImageComp(50, 15, 129, 86, lcd_02d, lcd_02d_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "02n") == 0) {
		ST7789_DrawImageComp(50, 15, 127, 87, lcd_02n, lcd_02n_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "03n") == 0 || strcmp(weather_icon_id, "03d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 82, lcd_03dn, lcd_03dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "04n") == 0 || strcmp(weather_icon_id, "04d") == 0) {
		ST7789_DrawImageComp(50, 15, 139, 88, lcd_04dn, lcd_04dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "09n") == 0 || strcmp(weather_icon_id, "09d") == 0) {
		ST7789_DrawImageComp(50, 15, 114, 103, lcd_09dn, lcd_09dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "10d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 124, lcd_10d, lcd_10d_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "10n") == 0) {
		ST7789_DrawImageComp(50, 15, 108, 105, lcd_10n, lcd_10n_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "11n") == 0 || strcmp(weather_icon_id, "11d") == 0) {
		ST7789_DrawImageComp(50, 15, 132, 111, lcd_11dn, lcd_11dn_size, BLACK, 1);
	}
	else if (strcmp(weather_icon_id, "50n") == 0 || strcmp(weather_icon_id, "50d") == 0) {
		ST7789_DrawImageComp(50, 15, 128, 128, lcd_50dn, lcd_50dn_size, BLACK, 1);
	}

	ST7789_WriteString(60, 155, weather_date, Font_11x18, WHITE, BLACK);

	ST7789_DrawImageComp(18, 200, 11, 25, lcd_thermometer_small, lcd_thermometer_small_size, BLACK, 1);
	sprintf((char*) weather_temp, "%s%cC", weather_temp, 0x7F);
	ST7789_WriteString(32, 208, weather_temp, Font_11x18, WHITE, BLACK);

	ST7789_DrawImageComp(80, 201, 16, 24, lcd_humidity_small, lcd_humidity_small_size, BLACK, 1);
	sprintf((char*) weather_humidity, "%s%%", weather_humidity);
	ST7789_WriteString(100, 208, weather_humidity, Font_11x18, WHITE, BLACK);

	ST7789_DrawImageComp(140, 210, 16, 16, lcd_wind, lcd_wind_size, BLACK, 1);
	sprintf((char*) weather_wind_speed, "%sm/s", weather_wind_speed);
	ST7789_WriteString(160, 208, weather_wind_speed, Font_11x18, WHITE, BLACK);

	if (day != 30) {
		ST7789_WriteString(200, 5, "Nxt", Font_11x18, WHITE, BLACK);
	}
	ST7789_WriteString(5, 5, "Prv", Font_11x18, WHITE, BLACK);
}

void WEATHER_display() {
	if (weather_rtc_icon_flag == 0) {
		ST7789_Fill_Color(BLACK);
		WEATHER_display_current();
		weather_rtc_icon_flag = 1;
	}
	if ((adxl_Y >= 17) && (weather_day != -1)) {
		weather_day--;
		weather_day_icon_flag = 0;
	}

	if ((adxl_Y <= -15) && (weather_day != 6)) {
		weather_day++;
		weather_day_icon_flag = 0;
	}

	if (weather_day == -1) {
		if (weather_day_icon_flag == 0) {
			ST7789_Fill_Color(BLACK);
			WEATHER_display_current();
			weather_day_icon_flag = 1;
		}
	}
	else {
		if (weather_day_icon_flag == 0) {
			ST7789_Fill_Color(BLACK);
			WEATHER_display_forecast(weather_day);
			weather_day_icon_flag = 1;
		}
	}
}

void GAME_snake_check_and_delay(uint32_t x) {
	for (int i = 0; i < x; i++) {
		osDelay(5);
		if ((adxl_X > -12) && game_snake_direction != 3) {
			game_snake_direction = 1;
		}
		else if ((adxl_X < -27) && game_snake_direction != 1) {
			game_snake_direction = 3;
		}
		else if ((adxl_Y > 6) && game_snake_direction != 2) {
			game_snake_direction = 4;
		}
		else if ((adxl_Y < -6) && game_snake_direction != 4) {
			game_snake_direction = 2;
		}
	}
}

void GAME_snake_rst() {
	game_snake_direction = 1;
	game_snake_score = 0;
	game_snake_speed = 200;
	game_snake_element = 3;

	for (int i = 0; i < 3; i++) {
		game_snake_position[i][0] = 12;
		game_snake_position[i][1] = 16 + i;
	}
}

void GAME_snake_gameover() {
	ST7789_Fill_Color(BLACK);
	ST7789_WriteString(48, 20, "GAME OVER", Font_16x28, RED, BLACK);

	ST7789_WriteString(10, 100, game_snake_score_buff, Font_16x28, WHITE, BLACK);
	
	ST7789_WriteString(10, 150, ">Front tilt to play<", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(15, 190, ">Back tilt to exit<", Font_11x18, WHITE, BLACK);

	while (1) {
		osDelay(370);
		if (((adxl_X - adxl_prevX) >= 4) && (adxl_X >= -20) && (adxl_prevX >= -20)) {
			game_snake_flag = 1;
			break;
		}
		if (((adxl_X - adxl_prevX) >= 4) && (adxl_X <= -20) && (adxl_prevX <= -20)) {
			glb_state = MENU;
			game_snake_out_flag = 1;
			break;
		}
	}
}

void GAME_snake_draw_score() {
	memset(game_snake_score_buff, '\0', sizeof(game_snake_score_buff));
	sprintf(game_snake_score_buff, "Score: %0d", game_snake_score - 1);
	ST7789_WriteString(5, 7, game_snake_score_buff, Font_11x18, 0x03e0, 0x03e0);

	memset(game_snake_score_buff, '\0', sizeof(game_snake_score_buff));
	sprintf(game_snake_score_buff, "Score: %0d", game_snake_score);
	ST7789_WriteString(5, 7, game_snake_score_buff, Font_11x18, WHITE, 0x03e0);
}

void GAME_snake_append_square() {
	game_snake_position[game_snake_element][0] = game_snake_position[game_snake_element - 1][0];
	game_snake_position[game_snake_element][1] = game_snake_position[game_snake_element - 1][1];

	game_snake_element++;
}

void GAME_snake_check_apple() { 
  if (game_snake_position[0][0] == game_snake_apple_position[0] && game_snake_position[1][1] == game_snake_apple_position[1]) {
    game_snake_score += 1;
    GAME_snake_draw_score();
    GAME_snake_append_square();
    GAME_snake_spawn_apple();

    if (300 - game_snake_score * 10 < 80) {
		game_snake_speed = 50;                             
    } 
	else {
		game_snake_speed = 200 - game_snake_score * 10;
    }
  }
}

void GAME_snake_check_collision() {
	for (int i = 2; i < game_snake_element; i++) {
		if ((game_snake_position[0][0] == game_snake_position[i][0]) && (game_snake_position[0][1] == game_snake_position[i][1])) {
			GAME_snake_gameover();
		}
	}	
}

void GAME_snake_step() {
	int last = game_snake_element - 1;
	GAME_snake_draw_quadrat(game_snake_position[last][0], game_snake_position[last][1], 0x03e0);
	for (int i = last; i > 0; i--) {
		game_snake_position[i][0] = game_snake_position[i - 1][0];
		game_snake_position[i][1] = game_snake_position[i - 1][1];
	}
	GAME_snake_check_apple();
	GAME_snake_check_collision();
}

void GAME_snake_check_direction() {
	while (1) {
		GAME_snake_check_and_delay(0);
		if (game_snake_direction == 1) {     	//Up
			if (game_snake_position[0][1] == 3) {
				GAME_snake_gameover();
			}
			GAME_snake_step();
			game_snake_position[0][1] -= 1;
		}
		else if (game_snake_direction == 2) {    //Right
			if (game_snake_position[0][0] == 22) {
				GAME_snake_gameover();
			}
			GAME_snake_step();
			game_snake_position[0][0] += 1;
		}
		else if (game_snake_direction == 3) {    //Down
			if (game_snake_position[0][1] == 20) {
				GAME_snake_gameover();
			}
			GAME_snake_step();
			game_snake_position[0][1] += 1;
		}
		else if (game_snake_direction == 4) {  	//Left
			if (game_snake_position[0][0] == 1) {
				GAME_snake_gameover();
			}
			GAME_snake_step();
			game_snake_position[0][0] -= 1;
		}

		if (game_snake_out_flag == 1) {
			game_snake_out_flag = 0;
			break;
		}

		if (game_snake_flag == 1) {
			game_snake_flag = 0;
			game_snake_rst_flag = 1;
			break;
		}

		GAME_snake_draw_quadrat(game_snake_position[0][0], game_snake_position[0][1], BLACK);
		GAME_snake_check_and_delay(game_snake_speed);
	}
}

void GAME_snake_draw_quadrat(uint16_t x_pos, uint16_t y_pos, uint16_t color) {
	for (int i = 0; i < 9; i++) {
    	for (int j = 0; j < 9; j++) {
			ST7789_DrawPixel(x_pos * 10 + i, y_pos * 10 + j, color);
		}
	}
}

void GAME_snake_spawn_apple() {
	game_snake_random_x = random() % 22;
	game_snake_random_y = random() % 20;

	if (game_snake_random_x == 0) {
		game_snake_random_x = 1;
	}

	if (game_snake_random_y < 4) {
		game_snake_random_y = 4;
	}

	int numofelement = sizeof(game_snake_position) / sizeof (game_snake_position[0]);

	for (int i = 0; i < numofelement / 4; i++) { 
		if (game_snake_position[i][0] == game_snake_random_x && game_snake_position[i][1] == game_snake_random_y) {
			GAME_snake_spawn_apple();
			exit(0);
		}
	}

	game_snake_apple_position[0] = game_snake_random_x;
	game_snake_apple_position[1] = game_snake_random_y;
	GAME_snake_draw_quadrat(game_snake_random_x, game_snake_random_y, RED); 
}

void GAME_snake_startScreen() {
	ST7789_Fill_Color(0x03e0);
	ST7789_WriteStringMedium(40, 30, "SNAKE", FontMorgan_32x72, WHITE, 0x03e0);
	ST7789_WriteStringMedium(52, 95, "GAME", FontMorgan_32x72, WHITE, 0x03e0);
	ST7789_WriteString(10, 170, ">Front tilt to play<", Font_11x18, 0xC618, 0x03e0);
	// ST7789_WriteString(20, 200, "Highest score: ", Font_11x18, 0xC618, 0x03e0);

	osDelay(2000);
	while ((adxl_X - adxl_prevX) < 6);
}

void GAME_snake_gamePlay() {
	ST7789_Fill_Color(0x03e0);
	ST7789_DrawRectangle(9, 28, 230, 208, BLACK);

	memset(game_snake_score_buff, '\0', sizeof(game_snake_score_buff));
	sprintf(game_snake_score_buff, "Score: %0d", game_snake_score);
	ST7789_WriteString(5, 7, game_snake_score_buff, Font_11x18, WHITE, 0x03e0);
	GAME_snake_spawn_apple();

	for (int i = 0; i < game_snake_element; i++) {
		GAME_snake_draw_quadrat(game_snake_position[i][0], game_snake_position[i][1], BLACK);
    }

	GAME_snake_check_direction();
}

void GAME_snake_loop() {
	GAME_snake_rst();
	GAME_snake_startScreen();
    GAME_snake_gamePlay();
	if (game_snake_rst_flag == 1) {
		game_snake_rst_flag = 0;
		GAME_snake_loop();
	}
}
#endif /* LIB_RTC_RTC_H_ */
