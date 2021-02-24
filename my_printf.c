# include "stdio.h"
# include "stdarg.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <inttypes.h>


int ans_cnt;

void my_putchar(char c) {
  write(1, &c, 1);
  ans_cnt++;
}
char *result_lenght(){
  return malloc(100);
}
//Some idea was taken from goolge_itoa but some places modifed by me
char* my_itoa(long long x,char *result , int base){
    char* ptr = result, *ptr1 = result, tmp_char;
     int x2 = x;
    while(x){
        *ptr++ = "0123456789abcdef"[x % (base) * (x < 0? -1: 1)];
        x /= base;
    }
	// Apply negative sign
	if (x2 < 0) *ptr++ = '-';
    if (x2 == 0) *ptr++ = '0';

	*ptr-- = '\0';

    //Reverse string by swapping two pointers
	while(ptr1 < ptr) {    
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
    }
	return result;
}
// Updated: fixed for NULL strings
void print(char* s){
    if (s == NULL){
        s = "(null)";
    }
    while(*s){
        my_putchar(*s);
        *s++;
    }
}

char hex_digit(int v) {
    if (v >= 0 && v < 10)
        return '0' + v;
    else
        return 'a' + v - 10; // <-- Here
}

void print_address_hex(void* p0) {
    int i;
    uintptr_t p = (uintptr_t)p0;
    print("0x");
    for(i = (sizeof(p) << 3) - 20; i>=0; i -= 4) {
        my_putchar(hex_digit((p >> i) & 0xf));
    }
}

int my_printf(char * restrict fmt, ...){
    ans_cnt = 0;
    va_list ap;
    int d;
    char c, *p, *s;
    va_start(ap, fmt);
    
    while (*fmt){

        if(*fmt == '%'){
            *fmt++;
        
            switch(*fmt) {
                case 's':                       /* строка */
                    s = va_arg(ap, char *);
                    print(s);
                    break;
        
                case 'd':
                case 'u':                       
                    d = va_arg(ap, int);
                    char *result = result_lenght();
                    my_itoa(d, result, 10);
                    print(result);
                    free(result);
                    break;
        
                case 'c':                       
                    c = (char) va_arg(ap, int);
                    my_putchar(c);
                    break;
                
                case 'o':
                    d = va_arg(ap, int);
                    char *result2 = result_lenght();
                    my_itoa(d, result2, 8);
                    print(result2);
                    free(result2);
                    break;
                
                case 'x':
                    d = va_arg(ap, int);
                    char *result3 = result_lenght();
                    my_itoa(d, result3, 16);
                    print(result3);
                    free(result3);
                    break;
                case '%': break;
                
                case 'p':;
                        void *f = va_arg(ap, void *);
                        print_address_hex(f);
                        break;
                }

            } else my_putchar(*fmt);
        
        *fmt++;
        }
        va_end(ap);
        return ans_cnt;
}
