#pragma once


/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Include cmsis_os.h头文件 */
#include "cmsis_os.h"

#include "user_math.h"

/* Exported constants --------------------------------------------------------*/
#define DR16_OK			(0)
#define DR16_ERR_NULL	(-1)

#define DR16_SIGNAL_RAW_REDY	(1u<<7)
#define DR16_SIGNAL_DATA_REDY	(1u<<8)

#define DR16_CH_VALUE_MIN			(364u)
#define DR16_CH_VALUE_MID			(1024u)
#define DR16_CH_VALUE_MAX			(1684u)

#define DR16_RX_BUF_LENGTH 36u

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
	DR16_SW_ERR = 0,
	DR16_SW_UP = 1,
	DR16_SW_MID = 3,
	DR16_SW_DOWN = 2,
} DR16_SwitchPos_t;

typedef enum {
	DR16_KEY_W = 0,
	DR16_KEY_S,
	DR16_KEY_A,
	DR16_KEY_D,
	DR16_KEY_Q,
	DR16_KEY_E,
	DR16_KEY_SHIFT,
	DR16_KEY_CTRL,
} DR16_KeyValue_t;

typedef struct {
	osThreadId_t thread_alert;

	uint8_t raw[DR16_RX_BUF_LENGTH];
	
	struct {
		struct {
			float32_t ch_l_x;
			float32_t ch_l_y;
			float32_t ch_r_x;
			float32_t ch_r_y;
			
			float32_t ch_res;
			
			DR16_SwitchPos_t sw_l;
			DR16_SwitchPos_t sw_r;
		} rc;
		
		struct {
			int16_t x;
			int16_t y;
			int16_t z;
			bool l_click;
			bool r_click;
		} mouse;
		
		uint16_t key;
		uint16_t res;
	} data;
} DR16_t;

/* Exported functions prototypes ---------------------------------------------*/
int8_t DR16_Init(DR16_t *dr16, osThreadId_t thread_alert);
DR16_t *DR16_GetDevice(void);
int8_t DR16_Restart(void);

int8_t DR16_StartReceiving(DR16_t *dr16);
int8_t DR16_Parse(DR16_t *dr16);
bool DR16_DataCorrupted(DR16_t *dr16);

bool DR16_KeyPressed(const DR16_t *dr16, DR16_KeyValue_t key);
