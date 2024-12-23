#!/bin/bash

# Ensure srv1 is running on core 0 at the start
if ! docker ps --format '{{.Names}}' | grep -wq srv1; then
    echo "Starting srv1 on core 0..."
    docker run --name srv1 --rm -d --cpuset-cpus=0 vladikstuk/vladikdonk
else
    echo "srv1 is already running."
fi

srv1_timer=0
srv2_timer=0
srv3_idle_timer=0
srv2_idle_timer=0

while true; do
    # Check if srv1 is running
     if docker ps --format '{{.Names}}' | grep -wq srv1; then
        cpu_usage_srv1=$(docker stats --no-stream --format "{{.CPUPerc}}" srv1 | tr -d '%')
        
        if (( $(echo "$cpu_usage_srv1 > 90" | bc -l) )); then
            # If CPU load > 90%, start the timer for srv1
            if [ $srv1_timer -eq 0 ]; then
                srv1_timer=$(date +%s)
            fi
        else
            # Reset the timer if load is below 90%
            srv1_timer=0
        fi

        # If srv1 load > 90% for 2 minutes (120 seconds), launch srv2
        if [ $srv1_timer -ne 0 ] && (( $(date +%s) - srv1_timer >= 120 )); then
            echo "srv1 has been under high CPU load for 2 minutes. Launching srv2..."
            if ! docker ps --format '{{.Names}}' | grep -wq srv2; then
                docker run --name srv2 --rm -d vladikstuk/vladikdonk
            fi
            srv1_timer=0  # Reset timer after action
        fi
    fi

    # Check if srv2 is running
    if docker ps --format '{{.Names}}' | grep -wq srv2; then
        cpu_usage_srv2=$(docker stats --no-stream --format "{{.CPUPerc}}" srv2 | tr -d '%')

        if (( $(echo "$cpu_usage_srv2 > 90" | bc -l) )); then
            # If CPU load > 90%, start the timer for srv2
            if [ $srv2_timer -eq 0 ]; then
                srv2_timer=$(date +%s)
            fi
        else
            # Reset the timer if load is below 90%
            srv2_timer=0
        fi

        if (( $(echo "$cpu_usage_srv2 < 1" | bc -l) )); then
            # If CPU load < 1%, start the idle timer for srv2
            if [ $srv2_idle_timer -eq 0 ]; then
                srv2_idle_timer=$(date +%s)
            fi
        else
            # Reset idle timer if load is > 1%
            srv2_idle_timer=0
        fi

        # If srv2 load > 90% for 2 minutes (120 seconds), launch srv3
        if [ $srv2_timer -ne 0 ] && (( $(date +%s) - srv2_timer >= 120 )); then
            echo "srv2 has been under high CPU load for 2 minutes. Launching srv3..."
            if ! docker ps --format '{{.Names}}' | grep -wq srv3; then
                docker run --name srv3 --rm -d vladikstuk/vladikdonk
            fi
            srv2_timer=0  # Reset timer after action
        fi
    fi

    # Check if srv3 is running
    if docker ps --format '{{.Names}}' | grep -wq srv3; then
        cpu_usage_srv3=$(docker stats --no-stream --format "{{.CPUPerc}}" srv3 | tr -d '%')
        
        if (( $(echo "$cpu_usage_srv3 < 1" | bc -l) )); then
            # If CPU load < 1%, start the idle timer for srv3
            if [ $srv3_idle_timer -eq 0 ]; then
                srv3_idle_timer=$(date +%s)
            fi
        else
            # Reset idle timer if load is > 1%
            srv3_idle_timer=0
        fi

        # If srv3 has been idle (<1% load) for 2 minutes (120 seconds), shut it down
        if [ $srv3_idle_timer -ne 0 ] && (( $(date +%s) - srv3_idle_timer >= 120 )); then
            echo "srv3 has been idle for 2 minutes. Shutting down srv3..."
            docker kill srv3
            docker wait srv3
            srv3_idle_timer=0  # Reset timer after action
        fi
    fi

    # Check if srv2 has been idle for 120 seconds, then shut it down
    if [ $srv2_idle_timer -ne 0 ] && (( $(date +%s) - srv2_idle_timer >= 120 )); then
        echo "srv2 has been idle for 2 minutes. Shutting down srv2..."
        docker kill srv2
        docker wait srv2
        srv2_idle_timer=0  # Reset timer after action
    fi    

    # Debug output - remove or adjust as necessary
    if [ $srv1_timer -ne 0 ]; then
    	echo "srv1_busy: $(($(date +%s)-srv1_timer))"
    else
    	echo "srv1_busy: $srv1_timer"
    fi
    if [ $srv2_timer -ne 0 ]; then
    	echo "srv2_busy: $(($(date +%s)-srv2_timer))"
    else
    	echo "srv2_busy: $srv2_timer"
    fi
    if [ $srv2_idle_timer -ne 0 ]; then
    	echo "srv2_idle: $(($(date +%s)-srv2_idle_timer))"
    else
    	echo "srv2_idle: $srv2_idle_timer"
    fi
    if [ $srv3_idle_timer -ne 0 ]; then
    	echo "srv3_idle: $(($(date +%s)-srv3_idle_timer))"
    else
    	echo "srv3_idle: $srv3_idle_timer"
    fi
done




