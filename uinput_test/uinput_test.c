#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/uinput.h>
#include <linux/input.h>

static struct uinput_user_dev uinput_dev;
static int uinput_fd;
 
int creat_user_uinput(void);
int report_key(unsigned int type, unsigned int keycode, unsigned int value);

/*only mapping 0~127 bit7 is means with shift*/
//0 mean on mapping
#define WITH_SHIFT 0x80
const unsigned char ascii_to_scan_code_table[]= {

/* ASCII:     0[C] */ 0,
/* ASCII:     1[C] */ 0,
/* ASCII:     2[C] */ 0,
/* ASCII:     3[C] */ 0,
/* ASCII:     4[C] */ 0,
/* ASCII:     5[C] */ 0,
/* ASCII:     6[C] */ 0,
/* ASCII:     7[C] */ 0,
/* ASCII:     8[C] */ 0,
/* ASCII:     9[C] */ 0,
/* ASCII:    10[C] */ 0,
/* ASCII:    11[C] */ 0,
/* ASCII:    12[C] */ 0,
/* ASCII:    13[C] */ 0,
/* ASCII:    14[C] */ 0,
/* ASCII:    15[C] */ 0,
/* ASCII:    16[C] */ 0,
/* ASCII:    17[C] */ 0,
/* ASCII:    18[C] */ 0,
/* ASCII:    19[C] */ 0,
/* ASCII:    20[C] */ 0,
/* ASCII:    21[C] */ 0,
/* ASCII:    22[C] */ 0,
/* ASCII:    23[C] */ 0,
/* ASCII:    24[C] */ 0,
/* ASCII:    25[C] */ 0,
/* ASCII:    26[C] */ 0,
/* ASCII:    27[C] */ 0,
/* ASCII:    28[C] */ 0,
/* ASCII:    29[C] */ 0,
/* ASCII:    30[C] */ 0,
/* ASCII:    31[C] */ 0,
/* ASCII:    32( ) */ KEY_SPACE,
/* ASCII:    33(!) */ KEY_1|WITH_SHIFT,
/* ASCII:    34(") */ KEY_APOSTROPHE|WITH_SHIFT,
/* ASCII:    35(#) */ KEY_3|WITH_SHIFT,
/* ASCII:    36($) */ KEY_4|WITH_SHIFT,
/* ASCII:    37(%) */ KEY_5|WITH_SHIFT,
/* ASCII:    38(&) */ KEY_7|WITH_SHIFT,
/* ASCII:    39(') */ KEY_APOSTROPHE,
/* ASCII:    40(() */ KEY_9|WITH_SHIFT,
/* ASCII:    41()) */ KEY_0|WITH_SHIFT,
/* ASCII:    42(*) */ KEY_8|WITH_SHIFT,
/* ASCII:    43(+) */ KEY_EQUAL|WITH_SHIFT,
/* ASCII:    44(,) */ KEY_COMMA,
/* ASCII:    45(-) */ KEY_MINUS,
/* ASCII:    46(.) */ KEY_DOT,
/* ASCII:    47(/) */ KEY_SLASH,
/* ASCII:    48(0) */ KEY_0,
/* ASCII:    49(1) */ KEY_1,
/* ASCII:    50(2) */ KEY_2,
/* ASCII:    51(3) */ KEY_3,
/* ASCII:    52(4) */ KEY_4,
/* ASCII:    53(5) */ KEY_5,
/* ASCII:    54(6) */ KEY_6,
/* ASCII:    55(7) */ KEY_7,
/* ASCII:    56(8) */ KEY_8,
/* ASCII:    57(9) */ KEY_9,
/* ASCII:    58(:) */ KEY_SEMICOLON|WITH_SHIFT,
/* ASCII:    59(;) */ KEY_SEMICOLON,
/* ASCII:    60(<) */ KEY_COMMA|WITH_SHIFT,
/* ASCII:    61(=) */ KEY_EQUAL,
/* ASCII:    62(>) */ KEY_DOT|WITH_SHIFT,
/* ASCII:    63(?) */ KEY_SLASH|WITH_SHIFT,
/* ASCII:    64(@) */ KEY_2|WITH_SHIFT,
/* ASCII:    65(A) */ KEY_A|WITH_SHIFT,
/* ASCII:    66(B) */ KEY_B|WITH_SHIFT,
/* ASCII:    67(C) */ KEY_C|WITH_SHIFT,
/* ASCII:    68(D) */ KEY_D|WITH_SHIFT,
/* ASCII:    69(E) */ KEY_E|WITH_SHIFT,
/* ASCII:    70(F) */ KEY_F|WITH_SHIFT,
/* ASCII:    71(G) */ KEY_G|WITH_SHIFT,
/* ASCII:    72(H) */ KEY_H|WITH_SHIFT,
/* ASCII:    73(I) */ KEY_I|WITH_SHIFT,
/* ASCII:    74(J) */ KEY_J|WITH_SHIFT,
/* ASCII:    75(K) */ KEY_K|WITH_SHIFT,
/* ASCII:    76(L) */ KEY_L|WITH_SHIFT,
/* ASCII:    77(M) */ KEY_M|WITH_SHIFT,
/* ASCII:    78(N) */ KEY_N|WITH_SHIFT,
/* ASCII:    79(O) */ KEY_O|WITH_SHIFT,
/* ASCII:    80(P) */ KEY_P|WITH_SHIFT,
/* ASCII:    81(Q) */ KEY_Q|WITH_SHIFT,
/* ASCII:    82(R) */ KEY_R|WITH_SHIFT,
/* ASCII:    83(S) */ KEY_S|WITH_SHIFT,
/* ASCII:    84(T) */ KEY_T|WITH_SHIFT,
/* ASCII:    85(U) */ KEY_U|WITH_SHIFT,
/* ASCII:    86(V) */ KEY_V|WITH_SHIFT,
/* ASCII:    87(W) */ KEY_W|WITH_SHIFT,
/* ASCII:    88(X) */ KEY_X|WITH_SHIFT,
/* ASCII:    89(Y) */ KEY_Y|WITH_SHIFT,
/* ASCII:    90(Z) */ KEY_Z|WITH_SHIFT,
/* ASCII:    91([) */ KEY_LEFTBRACE,
/* ASCII:    92(\) */ KEY_BACKSLASH,
/* ASCII:    93(]) */ KEY_RIGHTBRACE,
/* ASCII:    94(^) */ KEY_6|WITH_SHIFT,
/* ASCII:    95(_) */ KEY_MINUS|WITH_SHIFT,
/* ASCII:    96(`) */ KEY_GRAVE,
/* ASCII:    97(a) */ KEY_A,
/* ASCII:    98(b) */ KEY_B,
/* ASCII:    99(c) */ KEY_C,
/* ASCII:   100(d) */ KEY_D,
/* ASCII:   101(e) */ KEY_E,
/* ASCII:   102(f) */ KEY_F,
/* ASCII:   103(g) */ KEY_G,
/* ASCII:   104(h) */ KEY_H,
/* ASCII:   105(i) */ KEY_I,
/* ASCII:   106(j) */ KEY_J,
/* ASCII:   107(k) */ KEY_K,
/* ASCII:   108(l) */ KEY_L,
/* ASCII:   109(m) */ KEY_M,
/* ASCII:   110(n) */ KEY_N,
/* ASCII:   111(o) */ KEY_O,
/* ASCII:   112(p) */ KEY_P,
/* ASCII:   113(q) */ KEY_Q,
/* ASCII:   114(r) */ KEY_R,
/* ASCII:   115(s) */ KEY_S,
/* ASCII:   116(t) */ KEY_T,
/* ASCII:   117(u) */ KEY_U,
/* ASCII:   118(v) */ KEY_V,
/* ASCII:   119(w) */ KEY_W,
/* ASCII:   120(x) */ KEY_X,
/* ASCII:   121(y) */ KEY_Y,
/* ASCII:   122(z) */ KEY_Z,
/* ASCII:   123({) */ KEY_LEFTBRACE|WITH_SHIFT,
/* ASCII:   124(|) */ KEY_BACKSLASH|WITH_SHIFT,
/* ASCII:   125(}) */ KEY_RIGHTBRACE|WITH_SHIFT,
/* ASCII:   126(~) */ KEY_GRAVE|WITH_SHIFT,
/* ASCII:   127[C] */ 0,

};

//-b KEY_BACKSPACE
//-e KEY_ENTER
//-s $input string
 
int main(int argc, char *argv[])
{
	
	int opt;
	int bflag,eflag,sflag;
	int count=0;
    bflag = 0;
    eflag = 0;
	sflag = 0;
    while ((opt = getopt(argc, argv, "esb:")) != -1) {
        switch (opt) {
            case 'b':
                bflag = 1;
				count = atoi(optarg);
                break;
			case 'e':
                eflag = 1;
                break;
			case 's':
                sflag = 1;
                break;				
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-s string] [-b count] [-e] \n",
                        argv[0]);
                return;
        }
    }
	
	printf("bflag=%d; ebflag=%d; optind=%d\n", bflag, eflag, optind);

    if (optind >= argc) {
        //fprintf(stderr, "Expected argument after options\n");
        //return;
    }

    //printf("name argument = %s\n", argv[optind]);
	
	int ret = 0;
	ret = creat_user_uinput();
	if(ret < 0){
		printf("%s:%d\n", __func__, __LINE__);
		return -1;//error process.
	}
	
	sleep(1);
	if(bflag){
		//printf("KEY_BACKSPACE");
		//report_key(EV_KEY, KEY_A, 1);// Report BUTTON A CLICK - PRESS event
		//report_key(EV_KEY, KEY_A, 0);// Report BUTTON A CLICK - RELEASE event
		//sleep(5);
		if(count>0){
			int i;
			for(i=0;i<count;i++){
		report_key(EV_KEY, KEY_BACKSPACE, 1);// Report BUTTON A CLICK - PRESS event
		report_key(EV_KEY, KEY_BACKSPACE, 0);// Report BUTTON A CLICK - RELEASE event
			}
		}else{
			report_key(EV_KEY, KEY_BACKSPACE, 1);// Report BUTTON A CLICK - PRESS event
		    report_key(EV_KEY, KEY_BACKSPACE, 0);// Report BUTTON A CLICK - RELEASE event
		}
		//sleep(5);
	}else if(eflag){
		//printf("KEY_ENTER");
		report_key(EV_KEY, KEY_ENTER, 1);// Report BUTTON A CLICK - PRESS event
		report_key(EV_KEY, KEY_ENTER, 0);// Report BUTTON A CLICK - RELEASE event		
	}else if(sflag){
		//char test_str[]={"abc!@#"};
		char *test_str=argv[optind];
		int len=strlen(test_str);
		int i=0;
		int scancode=0;
		for(i=0;i<len;i++){
			scancode=ascii_to_scan_code_table[test_str[i]];
			//printf("[%d]",test_str[i]);
			if(scancode){
				if(scancode&0x80){
					report_key(EV_KEY, KEY_LEFTSHIFT, 1);// Report BUTTON A CLICK - PRESS event
					report_key(EV_KEY, scancode&(~0x80), 1);// Report BUTTON A CLICK - PRESS event
					report_key(EV_KEY, scancode&(~0x80), 0);// Report BUTTON A CLICK - RELEASE event
					report_key(EV_KEY, KEY_LEFTSHIFT, 0);// Report BUTTON A CLICK - RELEASE event
				}else{
					report_key(EV_KEY, scancode, 1);// Report BUTTON A CLICK - PRESS event
					report_key(EV_KEY, scancode, 0);// Report BUTTON A CLICK - RELEASE event
				}
			}
		}
	}
	sleep(1);
	close(uinput_fd);
	return 0;
}
 
 
int creat_user_uinput(void)
{
	int i;
	int ret = 0;
 
	uinput_fd = open("/dev/uinput", O_RDWR | O_NDELAY);
	if(uinput_fd < 0){
		printf("%s:%d\n", __func__, __LINE__);
		return -1;//error process.
	}
	
	//to set uinput dev
	memset(&uinput_dev, 0, sizeof(struct uinput_user_dev));
	snprintf(uinput_dev.name, UINPUT_MAX_NAME_SIZE, "uinput-custom-dev");
	uinput_dev.id.version = 1;
	uinput_dev.id.bustype = BUS_VIRTUAL;
	
	ioctl(uinput_fd, UI_SET_EVBIT, EV_SYN);
	ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);
	ioctl(uinput_fd, UI_SET_EVBIT, EV_MSC);
	
	for(i = 0; i < 256; i++){
		ioctl(uinput_fd, UI_SET_KEYBIT, i);
	}
	
	ret = write(uinput_fd, &uinput_dev, sizeof(struct uinput_user_dev));
	if(ret < 0){
		printf("%s:%d\n", __func__, __LINE__);
		return ret;//error process.
	}
	
	ret = ioctl(uinput_fd, UI_DEV_CREATE);
	if(ret < 0){
		printf("%s:%d\n", __func__, __LINE__);
		close(uinput_fd);
		return ret;//error process.
	}
}
 
int report_key(unsigned int type, unsigned int keycode, unsigned int value)
{
	struct input_event key_event;
	int ret;
	
	memset(&key_event, 0, sizeof(struct input_event));
	
	gettimeofday(&key_event.time, NULL);
	key_event.type = type;
	key_event.code = keycode;
	key_event.value = value;
	ret = write(uinput_fd, &key_event, sizeof(struct input_event));
	if(ret < 0){
		printf("%s:%d\n", __func__, __LINE__);
		return ret;//error process.
	}
	
	gettimeofday(&key_event.time, NULL);
	key_event.type = EV_SYN;
	key_event.code = SYN_REPORT;
	key_event.value = 0;//event status sync
	ret = write(uinput_fd, &key_event, sizeof(struct input_event));
	if(ret < 0){
		printf("%s:%d\n", __func__, __LINE__);
		return ret;//error process.
	}
	
	return 0;
}