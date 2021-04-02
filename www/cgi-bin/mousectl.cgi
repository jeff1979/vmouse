#!/bin/sh
#echo "$QUERY_STRING" 1>&2
query_string() {
	echo "$QUERY_STRING" | grep -oE "(^|[?&])$1=[^&]+" | sed "s/%20/ /g" | cut -f 2 -d "="
}
cmd=$(query_string cmd)
#echo "$cmd" 1>&2
if [ -z "$cmd" ]; then
    exit 0
fi
mouse_cmd=`echo "$cmd" | sed -e 's/,/ /g'`
#echo "$mouse_cmd" 1>&2
echo "$mouse_cmd" > /sys/devices/platform/virmouse/vmevent
echo "OK"
