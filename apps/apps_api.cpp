#include "hanastd.hpp"
#include "apps_api.hpp"
#include "graphics.hpp"
#include "task.hpp"
#include "dwm.hpp"
using namespace hanastd;

STDOUT::STDOUT(char *buffer, uint32_t *cbuffer){
	this->buffer=buffer;
	this->cbuffer=cbuffer;
	this->offset=0;
}

int STDOUT::printf(uint32_t color,const char *format, ...){
	char buf[128];
	int i;
	va_list ap;

	va_start(ap, format);
	i = vsprintf(buf, format, ap);
	va_end(ap);
	append(buf,color);
	return i;
}

void STDOUT::append(char* str, uint32_t color){
	int len=strlen(str);
	for(int i=0;i<len;i++){
		buffer[offset+i]=str[i];
		cbuffer[offset+i]=color;
	}
	offset+=len-1;
	buffer[offset]=0;
}

extern SHEETCTRL *shtctl;

SHEET *init_window(int width, int height, char *title){
	auto sht=shtctl->allocsheet(width,height);
	sht->graphics->init_window(title);
	sht->slide((shtctl->xsize-width)/2,(shtctl->ysize-height)/2);
	dwm_addtop(sht,task_now());
	return sht;
}

void close_window(SHEET *sht){
	dwm_removewindow(sht);
}