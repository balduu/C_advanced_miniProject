
/* Thư viện getch.h lấy trên mạng 
  Source : https://hntho.wordpress.com/2010/11/23/ham-getch-trong-c-ubuntu/
  *******   https://hntho.wordpress.com/    *******
  slogan: "Một quyết định có thể đúng, có thể sai, nhưng một quyết định sai lầm 
         là không quyết định gì cả"
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>
int getch( void )
{
char ch;
int fd = fileno(stdin);
struct termio old_tty, new_tty;
ioctl(fd, TCGETA, &old_tty);
new_tty = old_tty;
new_tty.c_lflag &= ~(ICANON | ECHO | ISIG);
ioctl(fd, TCSETA, &new_tty);
fread(&ch, 1, sizeof(ch), stdin);
ioctl(fd, TCSETA, &old_tty);

return ch;
}
