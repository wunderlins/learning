enum message_type_t {request, response, error};

typedef struct {
	enum message_type_t msgtype;
} message_t;
