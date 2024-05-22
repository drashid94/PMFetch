/*Error Definitions across modules*/

/* Motor */
#define ERROR_MOTOR_BASE 0x0
#define ERROR_MOTOR_GPIO_CHIP_OPEN ERROR_MOTOR_BASE + 0x1
#define ERROR_MOTOR_GPIO_CLAIM_OUT ERROR_MOTOR_BASE + 0x2

/* Grid */
#define ERROR_GRID_BASE ERROR_MOTOR_BASE + 0x80
#define ERROR_GRID_...