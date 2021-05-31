#!/bin/sh
# parse query string
echo "$QUERY_STRING" 1>&2
query_string() {
	echo "$QUERY_STRING" | grep -oE "(^|[?&])$1=[^&]+" | sed "s/%20/ /g" | cut -f 2 -d "="
}
type=$(query_string type)
echo "$type" 1>&2
if [ -z "$type" ]; then
    cgi_message="Invalid argument"
    exit 22 # EINVAL
fi
#echo "$data" 1>&2

if [ $type = 1 ]; then
	data=$(query_string data)
	cmd="uinput_test -s $data"
	echo "$cmd" 1>&2
	eval $cmd
fi

if [ $type = 2 ]; then
	data=$(query_string data)
	cmd="uinput_test -b $data"
	echo "$cmd" 1>&2
	eval $cmd
fi

if [ $type = 3 ]; then
	data=$(query_string data)
	cmd="uinput_test -e"
	echo "$cmd" 1>&2
	eval $cmd
fi

echo "OK"
