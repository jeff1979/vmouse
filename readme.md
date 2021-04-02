# linux 虛擬滑鼠及搭配使用的網頁

## setup

insmod virmouse.ko

./busybox httpd -h ./www -p 80 -c /tmp/vmouse/httpd.conf -vf

open url: http://${ip}/mousepad.html

## ref

https://stackoverflow.com/questions/7790725/javascript-track-mouse-position

https://developer.mozilla.org/zh-TW/docs/Web/API/XMLHttpRequest/Using_XMLHttpRequest

https://fred-zone.blogspot.com/2010/01/mouse-linux-kernel-driver.html

https://www.itread01.com/content/1542937575.html
