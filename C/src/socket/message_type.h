/**
 * Protocol
 *
 * +------+--------+--------------+-----+
 * | type | length | ... data ... | END |
 * +------+--------+--------------+-----+
 *
 * type:   utin8_t message_type_t
 * length: utin8_t
 * data:  *uint8_t
 */

#include <stdint.h>

const char end_message = '\0';
enum message_type_t {
	request=1, 
	response=2, 
	error=4, 
	arg4=8, 
	arg5=16,
	arg6=32, 
	arg7=64, 
	arg8=128
};
typedef struct {
	enum message_type_t type;
	uint8_t length;
	uint8_t *data;
} message_t;

message_t message(uint8_t type, uint8_t length, uint8_t *data) {
	message_t item = {.type = type, .length = length, .data = data};
	return item;
}
