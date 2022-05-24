//https://en.wikipedia.org/wiki/ANSI_escape_code
//https://en.wikipedia.org/wiki/ANSI_escape_code#CSIsection
//CSI : Control Sequence Introducer : ESC [ <= ESC is \27 or \033 or \x1b

//defining commands to set and reset foreground and background colors
#define SET_COLOR(bold,color) printf("\033[%d;%dm",bold,color); //color can be from 30-37
#define SET_COLOR_RGB(R,G,B) printf("\033[38;2;%d;%d;%dm",R,G,B);

#define SET_COLOR_BACKG(bold,color) printf("\033[%d;%dm",bold,color); //color can be from 40-47
#define SET_COLOR_RGB_BACKG(R,G,B) printf("\033[48;2;%d;%d;%dm",R,G,B);

#define RESET_COLOR printf("\033[0m");

//defining colors to use
#define COLOR_SNAKE_BODY SET_COLOR_RGB(0,100,200)
#define COLOR_SNAKE_BODY_BACKG SET_COLOR_RGB_BACKG(100,0,0)
#define COLOR_SNAKE_HEAD SET_COLOR_RGB(200,0,0)
#define COLOR_SNAKE_HEAD_BACKG SET_COLOR_RGB_BACKG(0,0,100)
#define COLOR_FIELD_BACKG SET_COLOR_RGB_BACKG(100,200,100)
#define COLOR_EGG SET_COLOR_RGB(255,0,0)
#define COLOR_EGG_BACKG SET_COLOR_RGB_BACKG(0,0,100)
#define COLOR_OUTER_BACKG SET_COLOR_RGB_BACKG(50,50,100)