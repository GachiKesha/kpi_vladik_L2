#!/bin/bash

while true; do
	echo "Sending a request to 127.0.0.1:80/compute" 
	curl -i 127.0.0.1:80/compute &
	sleep $((RANDOM % 6 + 10))
done

wait
